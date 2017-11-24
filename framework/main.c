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

#if 0	
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
#endif
	Stu *stu;
	queue_t *q, *node;
		
	q = queue_create(sizeof(Stu));
	if (NULL == q) {
		printf("queue_create failed.\n");
		exit(1);	
	}

	stu = (Stu *)queue_push(q, sizeof(Stu));
	stu->num = 1;
	stu->num2 = 2;
	stu = (Stu *)queue_push(q, sizeof(Stu));
	stu->num = 3;
	stu->num2 = 4;
	stu = (Stu *)queue_push(q, sizeof(Stu));
	stu->num = 5;
	stu->num2 = 6;
	stu = (Stu *)queue_push(q, sizeof(Stu));
	stu->num = 7;
	stu->num2 = 8;
	stu = (Stu *)queue_push(q, sizeof(Stu));
	stu->num = 9;
	stu->num2 = 10;
	
	for (node = q->next; node != queue_sentinel(q); node = node->next) {
		Stu * t = (Stu *)node->data;
		printf("num, num2: %d, %d\n", t->num, t->num2);
	}

	queue_destroy(q);	

	memory_statistic();
}
