#include "log/log.h"

#include <stdarg.h>
#include <stdio.h>

static char *get_prefix(enum log_level level) {
    switch (level) {
        case LL_INFO:
            return "INFO";
        case LL_WARN:
            return "WARNING";
        case LL_ERR:
            return "CRITICAL";
        case LL_DEBUG:
            return "DEBUG";
        default:
            return "";
    }
}

void jlog(enum log_level level, char *fmt, ...) {
#ifndef DEBUG
    if (level == LL_DEBUG) {
        return;
    }
#endif
    va_list argp;
    va_start(argp, fmt);
    FILE *os = level == LL_ERR ? stderr : stdout;
    fprintf(os, "%s: ", get_prefix(level));
    vfprintf(os, fmt, argp);
    va_end(argp);
}