#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "strutil.h"
#include <threads.h>
#include <unistd.h>

#include "../include/config.h"
#include "udp_sock.h"
#include "ping.h"

#include <pthread.h>

#include "ping_pong_size.h"

static void comm_error(const int n, char *mod_name, char *fun_name) {
    char szLog[LOG_MAX_Z];

    if (n < 0) {
        if (is_timeout()) {
            log_format(szLog, sizeof(szLog) - 1, ERROR, mod_name, "%s timed out", fun_name);
        } else {
            log_format(szLog, sizeof(szLog) - 1, ERROR, mod_name, "%s failed", fun_name);
            perror(szLog); // print out with error description and return
            return;
        }
    } else if (n == 0) {
        log_format(szLog, sizeof(szLog) - 1, ERROR, mod_name, "%s - disconnected", fun_name);
    } else { // n > 0
        log_format(
            szLog, sizeof(szLog) - 1,
            ERROR, mod_name, "%s - partial data (%d bytes processed)", fun_name, n
            );
    }
    printf("%s\n", szLog);
}

#define TV_NSEC_MAX 1000000000

// Set next alarm time for TIMER_ABSTIME, keeps tv_nsec under 1 second
static void next_deadline(struct timespec *pdst) {
    pdst->tv_nsec += MONITOR_SLEEP * 1000000; // to nanoseconds
    while (pdst->tv_nsec >= TV_NSEC_MAX) {
        pdst->tv_nsec -= TV_NSEC_MAX;
        pdst->tv_sec++;
    }
}

void *pingThread(void *pArgs) {
    MONITOR_ARG *pA = pArgs;
    int *pResult = malloc(sizeof(int));
    char szLog[LOG_MAX_Z];
    char buffer[BUFSIZE_Z];
    struct sockaddr_in srvAddr;
    const socklen_t srvAddrSize = sizeof(srvAddr);

    const int iSockFd = create_socket(SOCKET_TIMEOUT);
    if (iSockFd == -1) {
        log_format(szLog, sizeof(szLog) - 1, ERROR, pA->szModuleName, "create_socket failed");
        perror(szLog);
        *pResult = EXIT_FAILURE;
        pthread_exit(pResult);
    }
    *pResult = EXIT_SUCCESS;

    bzero(&srvAddr, sizeof(srvAddr));
    set_addr_v4(&srvAddr, pA->addr, pA->iPort);

    socklen_t len;
    const size_t pingLen = strlen(PING);
    bool first_cycle = true;
    struct timespec sleep_to;

    do {
        // do not woit on the first cycle
        if (first_cycle) {
            first_cycle = false;
        } else {
            int rc = clock_gettime(CLOCK_MONOTONIC, &sleep_to);
            if (rc < 0) {
                perror("clock_gettime failed");
                *pResult = EXIT_FAILURE;
                close(iSockFd);
                return pResult;
            }
            next_deadline(&sleep_to);
            // Possible thread exit point
            rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &sleep_to, NULL);
            if (rc == EINTR) {
                // interrupted by the signal, wrap it up
                close(iSockFd);
                return pResult;
            } else if (rc != 0) {
                perror("nanosleep failed");
            }
        }

        int n = sendto(
            iSockFd, PING, pingLen, MSG_CONFIRM, (const struct sockaddr *) &srvAddr, srvAddrSize
            );
        if (n != pingLen) {
            comm_error(n, pA->szModuleName, "sendto");
            continue;
        }

        n = recvfrom(iSockFd, (char *)buffer, sizeof(buffer) - 1, MSG_WAITALL, (struct sockaddr *) &srvAddr, &len);
        if (n <= 0) {
            comm_error(n, pA->szModuleName, "recvfrom");
            continue;
        }
        buffer[n] = '\0';
        // Remove trailing newline from buffer
        if (buffer[n - 1] == '\n')
            n--;

        buffer[n] = '\0';

        if(strncmp(buffer, PONG, strlen(PONG)) == 0)
            log_format(szLog, sizeof(szLog) - 1, INFO, pA->szModuleName, "%s", buffer);
        else
            log_format(
                szLog, sizeof(szLog) - 1, ERROR, pA->szModuleName, "Unknown response: %s", buffer
                );
        printf("%s\n", szLog);
    } while( *pA->pUp );

    close(iSockFd);
    return pResult;
}
