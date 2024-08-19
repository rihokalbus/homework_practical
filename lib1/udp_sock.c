#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "udp_sock.h"

int create_socket(int socket_timeout) {
    struct timeval tv;

    tv.tv_sec = socket_timeout / 1000;
    tv.tv_usec = socket_timeout % 1000;  // Microseconds

    const int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
        return -1;

    int rc = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    if (rc == -1) {
        return -1;
    }
    rc = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));
    if (rc == -1) {
        return -1;
    }

    return sockfd;
}

int create_server_v4_socket(const in_addr_t addr, const int port, const int socket_timeout) {
    struct sockaddr_in sockAddr;
    const socklen_t len = sizeof(sockAddr);

    const int sockfd = create_socket(socket_timeout);

    if (sockfd == -1)
        return -1;

    bzero(&sockAddr, len);

    set_addr_v4(&sockAddr, addr, port);

    if (bind(sockfd, (const struct sockaddr *)&sockAddr, len) < 0)
        return  -1;

    return sockfd;
}

struct sockaddr_in *set_addr_v4(struct sockaddr_in *psock_addr, in_addr_t addr, int port) {
    psock_addr->sin_family = AF_INET;
    psock_addr->sin_addr.s_addr = htonl(addr);
    psock_addr->sin_port = htons(port);

    return psock_addr;
}