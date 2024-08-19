#include "strutil.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>

static char *get_loglevel(enum loglevel level) {
    assert(level == INFO || level == ERROR);
    return level == INFO? "INFO" : "ERROR";
}

int log_format(char *pdst, size_t dst_size, enum loglevel level, char *module, char *fmt, ...)
{
    int n = 0;
    va_list	ap;
    const locale_t loc = duplocale(uselocale(0));

    const time_t now = time(NULL);

    int i = strftime_l(pdst, dst_size, "%Y-%m-%d %H:%M:%S", localtime(&now), loc);
    dst_size -= i;
    n += i;
    assert(dst_size > 0);

    if (module != NULL && strlen(module) > 0) {
        i = snprintf(&pdst[n], dst_size, "|%s|%s|", get_loglevel(level), module);
    } else {
        i = snprintf(&pdst[n], dst_size, "|%s|", get_loglevel(level));
    }
    dst_size -= i;
    n += i;
    assert(dst_size > 0);

    va_start(ap, fmt);
    i = vsnprintf(&pdst[n], dst_size, fmt, ap);
    va_end(ap);

    return n + i;
}
