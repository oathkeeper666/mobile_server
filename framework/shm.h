#ifndef _SHM_H
#define _SHM_H

#include "core.h"

typedef struct shm_t {
	void 	*addr;
	size_t 	size;
	char 	name[FILENAME_LEN];
} shm_t;

shm_t * shm_create(const char *name, size_t size);

void shm_free(shm_t *m);

#endif /* _SHM_H */
