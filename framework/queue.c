#include "queue.h"
#include "palloc.h"

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

queue_t * queue_push(queue_t *h, size_t size)
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
	
	return new;	
}

void queue_destroy(queue_t *h)
{
	queue_t *last, *q;
	
	if (NULL == h) { return; }

	last = queue_last(h);	

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

queue_t * queue_middle(queue_t *q)
{
	queue_t *middle, *next;
	
	middle = queue_head(q);
	
	if (middle == queue_last(q)) {
		return middle;
	}
	
	next = queue_head(q);

	for ( ;; ) {	
		next = queue_next(next);
		if (next == queue_last(q)) {
			return middle;
		}
		
		middle = queue_next(middle);
		next = queue_next(next);

		if (next == queue_last(q)) {
			return middle;
		}		
	}	
}
