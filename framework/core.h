#ifndef _CORE_H
#define _CORE_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

#define mobile_version 111
#define MOBILE_VERSION "1.1.1"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) >= 0 ? (a) : -(a))

typedef unsigned 	uint_t;
typedef unsigned long	ulong_t;
typedef int		int_t;
typedef long 		long_t;

#define FILENAME_LEN 256
#define TIME_LEN 256

#define TRUE 1
#define FALSE 0

#define RET_OK 0
#define RET_ERROR -1

#endif /* _CORE_H */
