#include "array.h"
#include <string.h>

array_t *array_create(uint_t n, size_t size)
{
	array_t *a;

	a = MALLOC(sizeof(array_t));
	if (NULL == a) {
		return NULL;
	}
	a->elts = CALLOC(n, size);
	if (NULL == a->elts) {
		return NULL;
	}
	a->nelts = 0;
	a->nalloc = n;
	a->size = size;
		
	return a;
}

void array_destroy(array_t *a)
{
	if (a) {
		FREE(a->elts);
		FREE(a);
	} 
}

void *array_push(array_t *a)
{
	void *elts, *p;

	if (NULL == a) { return NULL; }
	
	if (a->nelts == a->nalloc) {	
		/* the array is full */
		p =  CALLOC(2 * a->nalloc, a->size);
		if (NULL == p) {
			return NULL;
		}
		memcpy(p, a->elts, a->nalloc * a->size);
		FREE(a->elts);
		a->elts = p;
		a->nalloc *= 2;
	}
	elts = a->elts + a->size * a->nelts;
	a->nelts++;	

	return elts;
}

void *array_push_n(array_t *a, uint_t n)
{
	uint_t nalloc;
	void *p, *elts;

	if (NULL == a) { return NULL; }

	if (a->nelts + n > a->nalloc) {
		/* the array is full */
		nalloc = 2 * MAX(n, a->nalloc);
		p = CALLOC(nalloc, a->size);
		if (NULL == p) {
			return NULL;
		}
		memcpy(p, a->elts, a->nelts * a->size);
		FREE(a->elts);
		a->elts = p;
		a->nalloc = nalloc;
	}	
	elts = a->elts + a->size * a->nelts;
	a->nelts += n;
	
	return elts;	
}
