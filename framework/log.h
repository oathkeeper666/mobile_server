#ifndef _LOG_H
#define _LOG_H

#include "core.h"

#define LOG_DEBUG             0
#define LOG_INFO              1
#define LOG_NOTICE            2
#define LOG_WARN              3
#define LOG_ERR               4
#define LOG_CRIT              5
#define LOG_ALERT             6
#define LOG_EMERG             7
#define LOG_STDERR            8

typedef struct logger {
	char name[FILENAME_LEN];
	FILE *file;
	uint_t level;
	time_t time;
} logger;

logger * log_open(const char *name, uint_t level);

void log_set_level(logger *log, uint_t level);

void log_write(logger *log, uint_t level, const char *fmt, ...);

void log_close(logger *log);

void log_flush(logger *log);

#endif /* _LOG_H */
