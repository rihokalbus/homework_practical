#ifndef PING_PONG_DEF_H
#define PING_PONG_DEF_H

#include <stdbool.h>
#include <netinet/in.h>

#define MODULE_NAME_SIZE 64
#define MODULE_NAME_SIZE_Z MODULE_NAME_SIZE + 1

#define PING "Ping"
#define PONG "Pong"

// Structure used by ping and pong threads
typedef struct {
    pthread_t tid;  // for storing the treads id
    char szModuleName[MODULE_NAME_SIZE_Z];  // module name displayed in the log records
    in_addr_t addr; // socket bind address
    int iPort; // UDP port
    __sig_atomic_t *pUp; // Pointer to up/down flag. A non-zero destination value indicates that the system is up.
} MONITOR_ARG;

// common funcitons

// check if blocking socket is timed out
extern bool is_timeout();

#endif //PING_PONG_DEF_H
