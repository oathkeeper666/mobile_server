#include "shm.h"
#include <sys/mman.h>
#include <string.h>

shm_t * shm_create(const char *name, size_t size)
{
	shm_t *m;

	m = MALLOC(sizeof(shm_t));
	if (NULL == m) {
		return NULL;
	}

	m->addr = mmap(NULL, size, PROT_READ|PROT_WRITE, 
		MAP_ANON|MAP_SHARED, -1, 0);
	if (m->addr == MAP_FAILED) {
		FREE(m);
		return NULL;
	}

	strncpy(m->name, name, FILENAME_LEN);
	m->name[FILENAME_LEN - 1] = '\0';
	m->size = size;

	return m;
}

void shm_free(shm_t *m)
{
	if (m) {
		munmap(m->addr, m->size);
		FREE(m);
	}
}
