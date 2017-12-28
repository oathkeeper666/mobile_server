#include "config.h"
#include "palloc.h"

static void foreach_json(const cJSON *obj, srv_conf_t *config);
static void parse_modules(const cJSON *obj, module_t **modules);
static void parse_object(const cJSON *obj, srv_conf_t *config);
static void parse_array(const cJSON *obj, srv_conf_t *config);

srv_conf_t * load_srv_cfg(const char *filepath)
{
	cJSON *obj;
	FILE *file;
	char str[4096];
	srv_conf_t *config;

	if (NULL == filepath) {
		filepath = "../conf/conf.json";
	}

	file = fopen(filepath, "r");
	if (NULL == file) {
		fprintf(stderr, "open %s failed.\n", filepath);
		return NULL;
	}

	memset(str, 0, sizeof(str));
	fread(str, sizeof(str), 1, file);

	obj = cJSON_Parse(str);
	if (NULL == obj) {
		fprintf(stderr, "parse json str error: %s\n", cJSON_GetErrorPtr());
		return NULL;
	}

	config = (srv_conf_t *) MALLOC(sizeof(srv_conf_t));
	memset(config, 0, sizeof(srv_conf_t));
	foreach_json(obj, config);

	fclose(file);
	cJSON_Delete(obj);

	return config;
}

void free_srv_config(srv_conf_t *config)
{
	uint_t i = 0;

	if (config) {
		for ( ; i < MAX_MODULE_NUM; i++) {
			if (config->modules[i]) {
				FREE(config->modules[i]);
				config->modules[i] = NULL;
			}
		}
		FREE(config);
	}
}

static void foreach_json(const cJSON *obj, srv_conf_t *config)
{
	cJSON *p;

	cJSON_ArrayForEach(p, obj) {
		if (p->type & cJSON_Array) {
			parse_array(p, config);
		} else if (p->type & cJSON_Object) {
			parse_object(p, config);
		} else if (p->type & cJSON_String) {
			if (0 == strncmp(p->string, "logPath", 32)) {
				strncpy(config->log_path, p->valuestring, FILENAME_LEN);
			} else if (0 == strncmp(p->string, "luaPath", 32)) {
				strncpy(config->lua_path, p->valuestring, FILENAME_LEN);
			} else if (0 == strncmp(p->string, "sockPath", 32)) {
				strncpy(config->sock_path, p->valuestring, FILENAME_LEN);
			}
		} else if (p->type & cJSON_Number) {
			if (0 == strncmp(p->string, "serverId", 32)) {
				config->server_id = (uint_t) p->valuedouble;
			} else if (0 == strncmp(p->string, "port", 32)) {
				config->port = (uint_t) p->valuedouble;
			}
		}
	}
}

static void parse_array(const cJSON *obj, srv_conf_t *config) 
{
	if (0 == strncmp(obj->string, "modules", 32)) {
		parse_modules(obj, config->modules);
	}
}

static void parse_modules(const cJSON *obj, module_t **modules)
{
	uint_t i;
	cJSON *p, *pp;
	module_t *m;

	i = 0;
	cJSON_ArrayForEach(p, obj) {
		if (p->type & cJSON_Object && i < MAX_MODULE_NUM) {
			m = (module_t *) MALLOC(sizeof(module_t));
			memset(m, 0, sizeof(module_t));
			cJSON_ArrayForEach(pp, p) {
				if (0 == strncmp(pp->string, "id", 32) && pp->type & cJSON_Number) {
					m->id = (uint_t) pp->valuedouble;
				} else if (0 == strncmp(pp->string, "name", 32) && pp->type & cJSON_String) {
					strncpy(m->name, pp->valuestring, FILENAME_LEN);
				} else if (0 == strncmp(pp->string, "min", 32) && pp->type & cJSON_Number) {
					m->min = (uint_t) pp->valuedouble;
				} else if (0 == strncmp(pp->string, "max", 32) && pp->type & cJSON_Number) {
					m->max = (uint_t) pp->valuedouble;
				} else if (0 == strncmp(pp->string, "sock", 32) && pp->type & cJSON_String) {
					strncpy(m->sock, pp->valuestring, FILENAME_LEN);
				}
			}
			modules[i++] = m;
		}
	}
}

static void parse_object(const cJSON *obj, srv_conf_t *config)
{

}

void print_config(srv_conf_t *config)
{
	uint_t i;
	module_t *m;

	if (config) {
		printf("{\n");
		printf("	\"serverId\": %u,\n", config->server_id);
		printf("	\"logPath\": %s,\n", config->log_path);
		printf("	\"luaPath\": %s,\n", config->lua_path);
		printf("	\"sockPath\": %s,\n", config->sock_path);
		printf("	\"port\": %d,\n", config->port);
		printf("	\"modules\": [\n");
		for (i = 0; i < MAX_MODULE_NUM; i++) {
			if (config->modules[i]) {
				m = config->modules[i];
				printf("		{\n");
				printf("			\"id\": %d,\n", m->id);
				printf("			\"name\": %s,\n", m->name);
				printf("			\"min\": %d,\n", m->min);
				printf("			\"max\": %d,\n", m->max);
				printf("			\"sock\": %s,\n", m->sock);
				printf("		}\n");
			}
		}
		printf("	]\n");
		printf("}\n");
	}
}
