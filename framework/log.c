#include "log.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>

#define STD_STREAM(f) ((f) == stdout || (f) == stdin || (f) == stderr)

#define SET_LEVEL(l, n) 		\
	if (n > LOG_STDERR) { 		\
		l->level = LOG_STDERR;	\
	} else if (n < LOG_DEBUG) { 	\
		l->level = LOG_DEBUG; 	\
	} else { 			\
		l->level = n;		\
	}

static FILE * open_file(time_t now, const char *name) 
{	
	char filename[FILENAME_LEN];
	FILE *file;
	struct tm t;
	uint_t n;

	if (isatty(STDOUT_FILENO)) {
		file = stdout;
	} else {
		localtime_r(&now, &t);
		strncpy(filename, name, FILENAME_LEN);
		n = strlen(name);
		sprintf(filename + n, "04%d02%d02%d_02%d", t.tm_year + 1900, 
			t.tm_mon + 1, t.tm_mday, t.tm_hour);


		file = fopen(filename, "a");
	}

	return file;
}

logger * log_open(const char *name, uint_t level)
{
	logger *log;
	FILE *file;
	time_t now;

	log = MALLOC(sizeof(logger));

	if (NULL == log) {
		return NULL;
	}

	now = time(0);

	strncpy(log->name, name, FILENAME_LEN - 1);
	log->name[FILENAME_LEN - 1] = '\0';
	
	SET_LEVEL(log, level);

	log->file = open_file(now, name);

	return log;
}

void log_set_level(logger *log, uint_t level)
{
	if (log) {
		SET_LEVEL(log, level);	
	}
}

static const char * level_desc[] = {
	"DEBUG",
	"INFO",
	"NOTICE",
	"WARN",
	"ERR",
	"CRIT",
	"ALERT",
	"EMERG",
	"STDERR"
};

static void writev(logger *log, uint_t level, const char *fmt, va_list args) 
{
	struct timeval time;
	FILE *file;
	struct tm t;
	
	if (NULL == log) return;

	if (level < log->level || level < LOG_DEBUG || level > LOG_STDERR) {
		return;
	}
	gettimeofday(&time, NULL);
	
	/* reopen */	
	if (time.tv_sec - log->time >= 60 * 60 || (STD_STREAM(log->file) && !isatty(STDOUT_FILENO))) {
		file = open_file(time.tv_sec, log->name);
		if (file) {
			if (log->file && !STD_STREAM(log->file)) {
				fclose(log->file);
			}
			log->file = file;
			log->time = time.tv_sec;
		}
	}

	localtime_r(&time.tv_sec, &t);
	fprintf(log->file, "[%02d-%02d-%02d %02d:%02d:%02d.%03u] ", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec, (uint_t)time.tv_usec / 1000);
	fprintf(log->file, "[%s] ", level_desc[level]);
	vfprintf(log->file, fmt, args);
	fprintf(log->file, "\n");
}

void log_write(logger *log, uint_t level, const char *fmt, ...)
{
	if (log) {
		va_list ap;
		va_start(ap, fmt);
		writev(log, level, fmt, ap);	
		va_end(ap);		
	}	
}

void log_close(logger *log)
{
	if (log) {
		if (log->file && !STD_STREAM(log->file)) {
			fclose(log->file);			
		}
		FREE(log);
	}
}

void log_flush(logger *log)
{
	if (log && log->file) {
		fflush(log->file);
	}
}
