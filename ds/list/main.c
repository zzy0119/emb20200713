#include <stdio.h>
#include "list.h"

static void show(const void *data)
{
	const int *d = data;
	printf("%d\n", *d);
}

int main(void)
{
	int data[] = {3,2,1,6,7,9,8,4,5};
	lhead_t *head = NULL;

	head = lhead_init(sizeof(int));
	if (NULL == head)
		return -1;

	for (int i = 0; i < sizeof(data) / sizeof(*data); i++) {
		lhead_insert(head, data+i, TAIL);	
	}
	lhead_traval(head, show);

	lhead_destroy(head);

	return 0;
}

