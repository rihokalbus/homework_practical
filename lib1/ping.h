#ifndef MONITOR_H
#define MONITOR_H

#include "ping_pong_def.h"
#include "ping_pong_size.h"

/*
 * ping thread
 *
 * Threads argument is pointer to the MONITOR_ARG structure.
 * On startup starts sending "Ping" packets to MONITOR_ARG.addr:MONITOR_ARG.iPort.
 * On receiving "Pong" response writes response content with response time to standard output.
 * Reports all errors to standard output.
 * Runs until MONITOR_ARG.pUp pointers destination value is nonzero.
 *
 * Input:
 *  pointer to the MONITOR_ARG structure
 *
 * Output:
 *  *int pointer to the threads retrunvalue. Threads host process is responsible for freeing allocated memory.
 *
 */
extern void *pingThread(void *pArgs);

#endif //MONITOR_H
