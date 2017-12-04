#include "config.h"
#include "palloc.h"

static srv_cfg_t *config = NULL;

srv_cfg_t * load_srv_cfg(const char * filepath)
{
	FILE *file;
	mxml_node_t *tree;

	if (config) {
		return config;
	}

	file = fopen(filepath, "r");
	if (NULL == file) {
		return NULL;
	}

	tree = mxmlLoadFile(NULL, file, MXML_TEXT_CALLBACK);
	if (NULL == tree) {
		fclose(file);
		return NULL;
	}

	config = MALLOC(sizeof(srv_cfg_t));
	if (NULL == config) {
		fclose(file);
		mxmlDelete(tree);
		return NULL;
	}

	memset(config, 0, sizeof(srv_cfg_t));

	config->file = file;
	config->tree = tree;

	return config;
}

void free_src_cfg()
{
	if (config) {
		if (config->file) fclose(config->file);
		if (config->tree) mxmlDelete(config->tree);

		FREE(config);
		config = NULL;
	}
}

int_t get_server_id()
{
	if (NULL == config || NULL == config->tree) {
		return -1;
	}

	return (uint_t)atoi(mxmlElementGetAttr(config->tree, "id"));
}

int_t get_version()
{
	if (NULL == config || NULL == config->tree) {
		return -1;
	}

	return (uint_t)atoi(mxmlElementGetAttr(config->tree, "version"));
}
