#ifndef _BUF_H
#define _BUF_H

#include "core.h"
#include "config.h"

typedef struct buf_t {
	void 	*buf;
	size_t 	size;
	uint_t 	rpos;
	uint_t	wpos;
} buf_t;

buf_t * buf_create(size_t size);

size_t buf_write_size(buf_t *b);

size_t buf_read_size(buf_t *b);

size_t buf_read(buf_t *b, void *c, size_t size);

size_t buf_write(buf_t *b, void *c, size_t size);

void buf_destroy(buf_t *b);

#endif /* _BUF_H */
