#ifndef _QUEUE_H
#define _QUEUE_H

#include "core.h"

typedef struct queue_s queue_t;

struct queue_s {
	queue_t *prev;
	void 	*data;
	queue_t *next;
};

#define queue_init(q)		\
	(q)->prev = (q);	\
	(q)->next = (q);

#define queue_empty(q) 		\
	(q) == (q)->prev;

#define queue_insert_head(h, x) \
	(x)->next = (h)->next; 	\
	(x)->prev = (h); 	\
	(h)->next->prev = (x); 	\
	(h)->next = (x);
	
#define queue_insert_tail(h, x)	\
	(x)->prev = (h)->prev;	\
	(x)->next = (h);	\
	(h)->prev->next = (x);	\
	(h)->prev = (x);	\

#define queue_head(h)		\
	(h)->next

#define queue_last(h)		\
	(h)->prev

#define queue_sentinel(h)	\
	(h)

#define queue_next(q)		\
	(q)->next 

#define queue_prev(q)		\
	(q)->prev

#define queue_remove(x)			\
	(x)->next->prev = (x)->prev;	\
	(x)->prev->next = (x)->next;	\
	(x)->next = NULL;		\
	(x)->prev = NULL;

queue_t * queue_create(size_t size);

queue_t * queue_push(queue_t *q, size_t size);

void queue_destroy(queue_t *q);

queue_t * queue_middle(queue_t *q);

#endif /* _QUEUE_H */
