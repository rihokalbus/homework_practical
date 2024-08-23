#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../include/config.h"
#include "../lib1/strutil.h"
#include "../lib1/pong.h"

char szModule[] = "Powerpack";

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

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig;
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("signal handler not set");
        return EXIT_FAILURE;
    }

    MONITOR_ARG pong = {.addr = POWERPACK_ADDR, .iPort = POWERPACK_PORT, .pUp = (__sig_atomic_t*)&up };
    if (pthread_create(&pong.tid, NULL, pongThread, &pong)) {
        perror("pongThread: pthread_create failed");
        return EXIT_FAILURE;
    }

    // TODO some powerpack functionality

    if (pthread_join(pong.tid, &pRes)) {
            perror("pongThread: pthread_join failed");
    }
    free(pRes);

    return EXIT_SUCCESS;
}
