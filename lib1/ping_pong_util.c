#include <errno.h>
#include <stdbool.h>

bool is_timeout() {
    return errno == EAGAIN || errno == EWOULDBLOCK;
}

