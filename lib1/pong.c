#include "pong.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <bits/socket.h>

#include "../include/config.h"
#include "strutil.h"
#include "ping_pong_size.h"
#include "udp_sock.h"

static void comm_error(const int n, char *mod_name, char *fun_name) {
    char szLog[LOG_MAX_Z];

    if (n < 0) {
        if (is_timeout()) {
            bool bWaiting = strncmp(fun_name, "recvfrom", strlen("recvfrom")) == 0;
            log_format(
                szLog, LOG_MAX, (bWaiting)? INFO : ERROR,  mod_name, "%s %s",
                fun_name, bWaiting? "waiting": "timed out");
        } else {
            log_format(szLog, LOG_MAX, ERROR, mod_name, "%s failed", fun_name);
            perror(szLog); // print out with error description and return
            return;
        }
    } else if (n == 0) {
        log_format(szLog, LOG_MAX, INFO, mod_name, "%s - disconnected", fun_name);
    } else { // n > 0
        log_format(
            szLog, LOG_MAX, ERROR,mod_name, "%s - partial data (%d bytes processed)", fun_name, n
            );
    }
    printf("%s\n", szLog);
}

void *pongThread(void *pArgs) {
    MONITOR_ARG *pA = pArgs;
    int *pResult = malloc(sizeof(int));
    char szLog[LOG_MAX_Z];

    *pResult = EXIT_SUCCESS;

    char buffer[BUFSIZE_Z];
    struct sockaddr_in cltAddr;
    socklen_t len;

    bzero(&cltAddr, sizeof(cltAddr));

    const int iSockID = create_server_v4_socket(pA->addr, pA->iPort, SOCKET_TIMEOUT);

    if (iSockID == -1) {
        perror("create_socket failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cltAddr);

    const size_t pongLen = strlen(PONG);

    do {
        int n = recvfrom(
            iSockID, (char *)buffer, sizeof(buffer) - 1, MSG_WAITALL, (struct sockaddr *) &cltAddr, &len
            );
        if (n <= 0) {
            comm_error(n, pA->szModuleName, "recvfrom");
            continue;
        }
        // Remove trailing newline from buffer
        if (buffer[n - 1] == '\n')
            n--;

        buffer[n] = '\0';

        if(strncmp(buffer, PING, strlen(PING)) == 0)
            log_format(szLog, sizeof(szLog) - 1, INFO, pA->szModuleName, "%s", buffer);
        else
            log_format(szLog, sizeof(szLog) - 1, ERROR, pA->szModuleName, "Unknown request: %s", buffer);
        printf("%s\n", szLog);

        n = sendto(
            iSockID, PONG, pongLen, MSG_CONFIRM, (const struct sockaddr *) &cltAddr, len
          );
        if (n != pongLen) {
            comm_error(n, pA->szModuleName, "sendto");
        }
    } while (*pA->pUp);

    close(iSockID);

    return pResult;
}