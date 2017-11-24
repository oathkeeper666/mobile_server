#ifndef _LIST_H
#define _LIST_H

#include "core.h"
#include "config.h"

typedef struct list_node_s list_node_t;

struct list_node_s
{
	void 		*elts;
	uint_t 		nelts;
	list_node_t	*next;
};

typedef struct list_t
{
	list_node_t	*last;	/*the last node of list*/
	size_t		size;	
	uint_t		nalloc;
	list_node_t	node;
} list_t;

list_t *list_create(uint_t n, size_t size);

void * list_push(list_t *list);

void list_destroy(list_t *list);

#endif /* _LIST_H */
