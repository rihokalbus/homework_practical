#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../include/config.h"
#include "../lib1/strutil.h"
#include "../lib1/ping.h"

static char szModuleName[] = "Drive";

volatile __sig_atomic_t up = 1;


static void sig(int __sig) {
    // Currently we are handling only SIGINT
    if (__sig == SIGINT) {
        up = 0;
    } else {
        raise(__sig);
    }
}


int main(void) {
    void *pRes;

    if (signal(SIGINT, sig) == SIG_ERR) {
        perror("signal handler not set");
        return EXIT_FAILURE;
    }

    // Prepare data for the ping threads
    MONITOR_ARG monitors[] = {
        {.szModuleName = "powerPack1",.addr = POWERPACK_ADDR, .iPort = POWERPACK_PORT, .pUp = (__sig_atomic_t*)&up },
        {.szModuleName = "cooling1",.addr = COOLING_ADDR, .iPort = COOLING_PORT, .pUp = (__sig_atomic_t*)&up },
    };
    const int iMaxThreads = sizeof(monitors) / sizeof(MONITOR_ARG);

    for (int i = 0; i < iMaxThreads; i++) {
        printf("Ping thread %s start: ", monitors[i].szModuleName);
        if (pthread_create(&monitors[i].tid, NULL, pingThread, &monitors[i])) {
            perror("pthread_create failed");
            return EXIT_FAILURE;
        }
        printf("OK\n");
    }
    // TODO some drive functionality maybe?

    for (int i = 0; i <  iMaxThreads; i++) {
        if (pthread_join(monitors[i].tid, &pRes)) {
            printf("Ping thread %s: ", monitors[i].szModuleName);
            perror("pthread_join failed");
        }
        free(pRes);
    }

    return EXIT_SUCCESS;
}
