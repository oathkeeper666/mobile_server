#include "list.h"

list_t *list_create(uint_t n, size_t size)
{
	list_t *list;
	
	list = MALLOC(sizeof(list_t));
	if (NULL == list) { 
		return NULL; 
	}
	list->node.elts = CALLOC(n, size);
	if (NULL == list->node.elts) {
		return NULL;
	}	
	list->size = size;
	list->last = &list->node;	
	list->nalloc = n;
	list->node.nelts = 0;
	list->node.next = NULL;

	return list;
}

void * list_push(list_t *list)
{
	list_node_t *last;
	void *elt;

	if (NULL == list) {
		return NULL;
	}
	
	last = list->last;		
	if (last->nelts == list->nalloc) {
		/* the last node is full */
		last = MALLOC(sizeof(list_node_t));
		if (NULL == last) {
			return NULL;
		}
		last->elts = CALLOC(list->nalloc, list->size);
		if (NULL == last->elts) {
			return NULL;
		}
		last->nelts = 0;
		last->next = NULL;
		list->last->next = last;
		list->last = last;
	}
	elt = last->elts + list->size * last->nelts;
	last->nelts++;

	return elt;
}

void list_destroy(list_t *list)
{
	list_node_t *node, *temp;

	if (list) {
		node = list->node.next;
		while (node) {
			temp = node;
			node = node->next;
			FREE(temp->elts);
			FREE(temp);
		}	
		FREE(list->node.elts);
		FREE(list);
	}	
}
