#include <stdio.h>
#include "list.h"

static void show(const void *data)
{
	const int *d = data;
	printf("%d\n", *d);
}

static int cmp(const void *key, const void *data)
{
	const int *k = key;
	const int *d = data;

	return *k - *d;
}

int main(void)
{
	int data[] = {3,2,1,6,7,9,8,4,5};
	list_t *head = NULL;
	int del_n = 2;

	head = list_init(sizeof(int));
	if (NULL == head)
		return -1;

	for (int i = 0; i < sizeof(data) / sizeof(*data); i++) {
		list_insert(head, data+i, TAIL);	
	}
	list_traval(head, show);

	printf("************删除***********\n");
	list_delete(head, &del_n, cmp);
	list_traval(head, show);
	printf("************删除***********\n");
	del_n = 3;
	list_delete(head, &del_n, cmp);
	list_traval(head, show);
	printf("************删除***********\n");
	del_n = 5;
	list_delete(head, &del_n, cmp);
	list_traval(head, show);

	list_destroy(head);

	return 0;
}

