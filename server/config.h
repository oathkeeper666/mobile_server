#ifndef _CONFIG_H
#define _CONFIG_H

#include "core.h"
#include "module.h"
#include "cJSON.h"

#define MAX_MODULE_NUM 10

typedef struct srv_conf_t {
	uint_t server_id;
	char log_path[FILENAME_LEN];
	char lua_path[FILENAME_LEN];
	char sock_path[FILENAME_LEN];
	uint_t port;
	module_t *modules[MAX_MODULE_NUM];
} srv_conf_t;

srv_conf_t * load_srv_cfg(const char *filepath);

void free_srv_config(srv_conf_t *config);

void print_config(srv_conf_t *config);

#endif /* _CONFIG_H */
