#ifndef _MODULE_H
#define _MODULE_H

#include "core.h"

typedef struct module_t {
	uint_t id;
	char name[FILENAME_LEN];
	uint_t min;
	uint_t max;
	char sock[FILENAME_LEN];
} module_t;

#endif /* _MODULE_H */