#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

#include "../include/config.h"
#include "../lib1/strutil.h"
#include "../lib1/pong.h"

const char szModule[] = "Cooling";

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

    MONITOR_ARG pong = {.addr = COOLING_ADDR, .iPort = COOLING_PORT, .pUp = (__sig_atomic_t*)&up };
    if (pthread_create(&pong.tid, NULL, pongThread, &pong)) {
        perror("pthread_create failed");
        return EXIT_FAILURE;
    }

    // TODO some cooling functionality

    if (pthread_join(pong.tid, &pRes)) {
        perror("pthread_join failed");
    }
    free(pRes);

    return EXIT_SUCCESS;
}
