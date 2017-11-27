#include "core.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Stu
{
	int num;
	int num2;
} Stu;

int main()
{
	buf_t *b;
	char buffer[100] = "wubang";
	char line[100] = { '\0' };
	
	b = buf_create(1);
	if (NULL == b) {
		printf("buffer create failed.\n");
		exit(1);
	}
	
	size_t n1 = buf_read_size(b);	
	size_t n2 = buf_write_size(b);
	
	printf("n1 = %d, n2 = %d\n", n1, n2);
	buf_write(b, buffer, 6);
	buf_write(b, buffer, 6);
	size_t n3 = buf_read(b, line, 100);
	buf_write(b, buffer, 6);
	size_t n4 = buf_write_size(b);	

	printf("n3= %d, n4 = %d\n", n3, n4);
	printf("read line is %s\n", line);

	memory_statistic();
}
