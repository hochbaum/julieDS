#ifndef JULIEDS_LOG_H
#define JULIEDS_LOG_H

enum log_level { LL_INFO, LL_WARN, LL_ERR, LL_DEBUG };

void jlog(enum log_level level, char *fmt, ...);

#endif //JULIEDS_LOG_H