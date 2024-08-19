#ifndef LIB1_LIBRARY_H
#define LIB1_LIBRARY_H

#include <netinet/in.h>

/*
 * Create Datagram socket
 *
 * Input:
 *  int socket_timeout: timeout in milliseconds, applies to send and receive operations
 *
 *  Output:
 *   int sockfd: created sockets file descripor, -1 on error
 */
extern int create_socket(int socket_timeout);

/*
 * Create UDP server socket and bind it to the port iPort
 *
 * Input:
 *  in_addr_t: IP address
 *  int port: Port number
 *  int socket_timeout: Timeout in milliseconds, applies to send and receive operations
 *
 *  Output:
 *   int sockfd: created sockets file descripor, -1 on error
 */
extern int create_server_v4_socket(in_addr_t addr, int iPort, int socket_timeout);

/*
 * Fill sockaddr_in structure with ipv4 addrss data
 *
 * Input:
 *  struct sockaddr_in *psock_addr: Pointer to a sockaddr_in structure
 *  in_addr_t addr: IP address
 *  int port: Port number
 *
 * Output:
 *  sockaddr_in psock_addr - returns psock_addr from the input
 */
extern struct sockaddr_in *set_addr_v4(struct sockaddr_in *psockAddr, in_addr_t addr, int iPort);

#endif //LIB1_LIBRARY_H
