#include "config.h"

int main()
{
	load_srv_cfg("../conf/lksg.xml");

	int_t id = get_server_id();
	
	printf("server id is %d\n", id);

	return 0;
}
