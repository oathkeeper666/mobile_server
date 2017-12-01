#ifndef _PALLOC_H
#define _PALLOC_H_

#include "core.h"

void *_malloc(size_t size);
void _free(void *ptr);
void *_realloc(void *ptr, size_t size);
void *_calloc(size_t n, size_t size);

void memory_statistic();

#define MALLOC(size) _malloc(size)	
#define FREE(p) _free(p)
#define REALLOC(p, size) _realloc(p, size)
#define CALLOC(n, size) _calloc(n, size)

#endif	/* _PALLOC_H_ */
