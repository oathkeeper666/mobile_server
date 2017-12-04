#include "palloc.h"

static unsigned long g_malloc_count = 0;
static unsigned long g_realloc_count = 0;
static unsigned long g_calloc_count = 0; 
static unsigned long g_free_count = 0;

void *_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (p) {
		g_malloc_count++;
	}
	return p;
}

void _free(void *ptr)
{
	g_free_count++;
	free(ptr);	
}

void *_realloc(void *ptr, size_t size)
{
	void *p;

	p = realloc(ptr, size);
	if (p) {
		g_realloc_count++;
	}

	return p;
}

void *_calloc(size_t n, size_t size)
{
	void *p;

	p = calloc(n, size);
	if (p) {
		g_calloc_count++;
	}

	return p;
}

void memory_statistic()
{
	printf("malloc count is %ld, realloc count is %ld, calloc count is %ld, free count is %ld.\n", 
		g_malloc_count, g_realloc_count, g_calloc_count, g_free_count);	
}
