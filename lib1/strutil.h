#ifndef STRUTIL_H
#define STRUTIL_H
#include <stddef.h>

#ifndef __LOGLEVEL
#define __LOGLEVE
enum loglevel {INFO = 0, ERROR = 1};
#endif

/*
 * Formated strings for logging. Adds timestamp and module name.
 *
 * Input:
 *  char *pdst: destination buffer
 *  size_t dst_size: destination size in bytes
 *  enum loglevel: log level
 *  char *module: module name
 *  char *fmt: format definition
 *  ... : format arguments
 *
 * Output:
 *  int: size of formatted string
 *
 *  function can throw assertions when pdst size is not sufficient
 */
extern int log_format(char *pdst, size_t dst_size, enum loglevel level, char * module, char *fmt, ...);

#endif //STRUTIL_H
