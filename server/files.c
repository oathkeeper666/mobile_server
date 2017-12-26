#include "files.h"

int_t create_pid_file(pid_t pid)
{
	int_t fd;
	char buf[32];
	uint_t len;

	fd = open("../conf/config.pid", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (-1 == fd) {
		return INVALID_FD;
	}
	snprintf(buf, 32, "%d", pid);	
	len = strlen(buf) + 1;

	if (write(fd, buf, len) < len) {
		close(fd);
		return INVALID_FD;	
	}
		
	return fd;
}

pid_t master_pid()
{
	int_t fd;
	char buf[32];
	int_t n;
	
	memset(buf, 0, sizeof(buf));

	fd = open("../conf/config.pid", O_RDONLY);
	if (-1 == fd) {
		return INVALID_PID;
	}
	n = read( fd, buf, sizeof(buf) );
	if (-1 == n) {
		return INVALID_PID;
	}
	
	close(fd);
	
	return atoi(buf);
}
