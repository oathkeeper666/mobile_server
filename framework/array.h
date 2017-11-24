#ifndef _ARRAY_H
#define _ARRAY_H

#include "config.h"
#include "core.h"

typedef struct array_t {
	void		*elts;
	uint_t		nelts;
	uint_t		nalloc;
	size_t		size;
} array_t;

array_t *array_create(uint_t n, size_t size);
void array_destroy(array_t *a);

void *array_push(array_t *a);
void *array_push_n(array_t *a, uint_t n);

#endif /* _ARRAY_H */
