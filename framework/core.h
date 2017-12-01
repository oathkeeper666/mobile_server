#ifndef _CORE_H
#define _CORE_H

/*#include "palloc.h"
#include "array.h"
#include "list.h"
#include "queue.h"
#include "buffer.h"
#include "rbtree.h"
#include "log.h"
#include "times.h"
#include "shm.h"*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) >= 0 ? (a) : -(a))

typedef unsigned 	uint_t;
typedef unsigned long	ulong_t;
typedef int		int_t;
typedef long 		long_t;

#define FILENAME_LEN 256
#define TIME_LEN 256

#endif /* _CORE_H */
