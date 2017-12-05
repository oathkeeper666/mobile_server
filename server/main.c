#include "config.h"

int main()
{
	load_srv_cfg("../conf/lksg.xml");

	const char *text = get_srv_cfg_text("Database", "Account", "port", NULL);
	
	if (text) {
		printf("text is %s\n", text);
	}

	return 0;
}
