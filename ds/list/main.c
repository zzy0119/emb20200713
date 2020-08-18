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
	int update = 100;
	int key = 7;
	int *ret;

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

	printf("**************修改****************\n");
	list_update(head, &key, cmp, &update);
	list_traval(head, show);
	printf("***********第一个结点****************\n");
	ret = (int *)list_firstnode(head);
	if (ret != NULL)	
		printf("%d\n", *ret);
	ret = (int *)list_lastnode(head);
	if (ret != NULL)
		printf("%d\n", *ret);

	printf("************转置*************\n");
	list_reverse(head);
	list_traval(head, show);

	list_destroy(head);

	return 0;
}

