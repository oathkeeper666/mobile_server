#ifndef _CONFIG_H
#define _CONFIG_H

#include "core.h"
#include "mxml.h"

typedef struct srv_cfg_s srv_cfg_t;
struct srv_cfg_s
{
	FILE *		file;
	mxml_node_t * 	tree;
};

srv_cfg_t * load_srv_cfg(const char * filepath);

void free_src_cfg();

int_t get_server_id();

int_t get_version();

/* vary arguments end with NULL */
const char * get_srv_cfg_text(const char * elem, ...);

const char * get_srv_cfg_attr(const char * name, const char * elem, ...);

#endif /* _CONFIG_H */
