#ifndef PONG_H
#define PONG_H

#include "ping_pong_def.h"

/*
 * pong thread
 *
 * Threads argument is pointer to the MONITOR_ARG structure.
 * On startup creates UDP listening port MONITOR_ARG.iPort. Responds to every receved message with "Pong".
 * Writes output to standard output, runs until MONITOR_ARG.pUp pointers destination value is nonzero.
 *
 * Input:
 *  pointer to the MONITOR_ARG structure
 *
 * Output:
 *  *int pointer to the threads retrunvalue. Threads host process is responsible for freeing allocated memory.
 *
 */
extern void *pongThread(void *pArgs);

#endif //PONG_H
