#include <pthread.h>
#include <signal.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/signum-generic.h>

#include "../include/config.h"
#include "../lib1/strutil.h"
#include "../lib1/ping_pong_def.h"
#include "../lib1/pong.h"

char szModule[] = "Powerpack";

volatile __sig_atomic_t up = 1;

static void sig(int __sig) {
    up = 0;
}

int main(void) {
    void *pRes;

    if (signal(SIGINT, sig) == SIG_ERR) {
        perror("signal handler not set");
        return EXIT_FAILURE;
    }

    MONITOR_ARG pong = {.addr = POWERPACK_ADDR, .iPort = POWERPACK_PORT, .pUp = (__sig_atomic_t*)&up };
    if (pthread_create(&pong.tid, NULL, pongThread, &pong)) {
        perror("pthread_create failed");
        return EXIT_FAILURE;
    }

    // TODO some powerpack functionality

    if (pthread_join(pong.tid, &pRes)) {
            perror("pthread_join failed");
    }
    free(pRes);

    return EXIT_SUCCESS;
}
