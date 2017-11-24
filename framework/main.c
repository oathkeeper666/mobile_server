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
	/*Stu *s;		
	array_t *a;

	a = array_create(3, sizeof(Stu));
	if (NULL == a) {
		printf("array create failed.");
		exit(1);	
	}

	s = (Stu *)array_push(a);
	printf("s1 = %p\n", s);	
	s = (Stu *)array_push(a);
	printf("s2 = %p\n", s);	
	s = (Stu *)array_push(a);
	printf("s3 = %p\n", s);	
	s = (Stu *)array_push(a);
	printf("s4 = %p\n", s);	

	printf("a->size = %d, a->nalloc = %d, a->nelts = %d\n", a->size, a->nalloc, a->nelts);
	array_push_n(a, 10);
	printf("a->size = %d, a->nalloc = %d, a->nelts = %d\n", a->size, a->nalloc, a->nelts);

	array_destroy(a);*/

	
	list_t * list;
	Stu *stu;

	list = list_create(2, sizeof(Stu));
	if (NULL == list) {
		printf("list create failed.");
		exit(1);
	}
	
	stu = (Stu *)list_push(list);
	printf("stu1 = %p\n", stu);
	
	stu = (Stu *)list_push(list);
	printf("stu2 = %p\n", stu);

	stu = (Stu *)list_push(list);
	printf("stu3 = %p\n", stu);

	stu = (Stu *)list_push(list);
	printf("stu4 = %p\n", stu);

	stu = (Stu *)list_push(list);
	printf("stu5 = %p\n", stu);
	
	list_destroy(list);

	memory_statistic();

	return 0;
}
