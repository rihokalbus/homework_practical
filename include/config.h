#ifndef CONFIG_H
#define CONFIG_H

#include <netinet/in.h>

// Socket timeout in milliseconds
#define SOCKET_TIMEOUT 3001

// addresses
#define POWERPACK_ADDR INADDR_LOOPBACK
#define POWERPACK_PORT 8001

#define COOLING_ADDR INADDR_LOOPBACK
#define COOLING_PORT 8002

// Drive monitor's idle time in milliseconds
#define MONITOR_SLEEP 1300

#endif //CONFIG_H
