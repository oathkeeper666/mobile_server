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

static mxml_node_t * child_node(mxml_node_t *parent, const char * elem) 
{
	mxml_node_t *child;
	const char * e;

	child = mxmlGetFirstChild(parent);
	for (; child; child = mxmlGetNextSibling(child)) {
		e = mxmlGetElement(child);
		if (e && strcmp(e, elem) == 0) {
			return child;
		}
	}

	return child;
}

static mxml_node_t * find_node(const char * elem, va_list args) 
{
	const char *key;
	mxml_node_t *node;

	if (NULL == config || NULL == config->tree) {
		return NULL;
	}

	node = child_node(config->tree, elem);
	key = va_arg(args, const char *);
	
	while (node && key) {
		node = child_node(node, key);
		key = va_arg(args, const char *);
	}

	return node;
}

const char * get_srv_cfg_text(const char * elem, ...)
{
	va_list va;
	mxml_node_t *node;
	const char *text;

	va_start(va, elem);
	node = find_node(elem, va);
	va_end(va);

	if (node) {
		text = mxmlGetText(node, 0);
	}
	else {
		text = NULL;
	}
	
	return text;
}

const char * get_srv_cfg_attr(const char * name, const char * elem, ...)
{	
	va_list va;
	mxml_node_t *node;
	const char *text;

	va_start(va, elem);
	node = find_node(elem, va);
	va_end(va);

	if (node) {
		text = mxmlElementGetAttr(node, name);
	}
	else {
		text = NULL;
	}
	
	return text;
}
