#include "queue.h"

queue_t * queue_create(size_t size)
{
	queue_t *q;
	
	q = MALLOC(sizeof(queue_t));
	if (NULL == q) {
		return NULL;
	}
	q->data = MALLOC(size);
	if (NULL == q->data) {
		return NULL;
	}
	
	queue_init(q);
	
	return q;	
}

void * queue_push(queue_t *h, size_t size)
{
	queue_t *new;
	
	if (NULL == h) { return NULL; }	
		
	new = MALLOC(sizeof(queue_t));
	if (NULL == new) {
		return NULL;
	}
	new->data = MALLOC(size);
	if (NULL == new->data) {
		return NULL;
	}

	queue_insert_tail(h, new);
	
	return new->data;	
}

void queue_destroy(queue_t *h)
{
	queue_t *last, *q;
	
	if (NULL == h) { return; }

	last = queue_last(h)		

	while (h != last) {
		q = h;
		h = h->next;
		q->next = NULL;
		q->prev = NULL;
		FREE(q->data);
		FREE(q);
	}
	last->next = NULL;
	last->prev = NULL;
	FREE(last->data);
	FREE(last);
}
