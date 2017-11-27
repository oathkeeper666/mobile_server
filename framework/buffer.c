#include "buffer.h"
#include <string.h>

#define ALIGN(n) (((n) + 3) & ~3)

buf_t * buf_create(size_t size)
{
	buf_t *buffer;
	
	size = size > 64 ? size : 64;
	size = ALIGN(size);

	buffer = MALLOC(sizeof(buf_t));
	if (NULL == buffer) {
		return NULL;
	}

	buffer->buf = MALLOC(size);
	if (NULL == buffer->buf) {
		return NULL;
	}
	buffer->size = size;
	buffer->rpos = 0;
	buffer->wpos = 0;

	return buffer;
}

size_t buf_write_size(buf_t *b)
{
	if (NULL == b) return 0;

	if (b->wpos >= b->rpos) {
		return b->size - b->wpos + b->rpos;
	}
	else {
		return b->rpos - b->wpos;
	}
}

size_t buf_read_size(buf_t *b)
{
	if (NULL == b) return 0;

	if (b->rpos > b->wpos) {
		return b->size - b->rpos + b->wpos;
	}
	else {
		return b->wpos - b->rpos;
	}
}

size_t buf_write(buf_t *b, void *c, size_t size)
{
	size_t wcnt, remain, n;
	void *p;

	remain = buf_write_size(b);
	wcnt = MIN(remain, size);
	size = wcnt;

	if (0 == size) return 0;

	p = b->buf + b->wpos;
	if (b->wpos >= b->rpos) {
		n = MIN(b->size - b->wpos, wcnt);
		memcpy(p, c, n);
		b->wpos += n;
		wcnt -= n;
		if (wcnt > 0) {
			memcpy(b->buf, c + n, wcnt);
			b->wpos += wcnt;
		}
	}
	else {
		memcpy(p, c, wcnt);
		b->wpos += wcnt;	
	}

	return size;
}

size_t buf_read(buf_t *b, void *c, size_t size)
{
	size_t rcnt, remain, n;
	void *p;

	remain = buf_read_size(b);
	rcnt = MIN(remain, size);
	size = rcnt;

	if (0 == size) return 0;

	p = b->buf + b->rpos;
	if (b->wpos > b->rpos) {
		b->rpos += rcnt;
		memcpy(c, p, rcnt);
	} 
	else {
		n = b->size - b->rpos;
		memcpy(c, p, n);
		b->rpos += n;
		rcnt -= n;
		if (rcnt > 0) {
			memcpy(c + n, b->buf, rcnt);
			b->rpos += rcnt;
		}
	}

	return size;
}

void buf_destroy(buf_t *b)
{
	if (b) {
		FREE(b->buf);
		b->buf = NULL;
		FREE(b);
	}
}
