#include <stdio.h>

#include "llist.h"

static void show(const void *data)
{
	const char *d = data;
	putchar(*d);
}

static int cmp_ch(const void *data, const void *key)
{
	const char *d = data;
	const char *k = key;
	return *d - *k;
}

int main(void)
{
	char str[] = "good morningu";	
	llisthead_t *head = NULL;
	char delch = 'u';

	llisthead_init(sizeof(char), &head);

	for (int i = 0; str[i]; i++) {
		llist_insert(head, str+i, INSERT_TAIL);
	}
	llist_traval(head, show);
	printf("\n");

	printf("**************删除****************\n");
	llist_delete(head, &delch, cmp_ch);	
	llist_traval(head, show);
	printf("\n");

	llist_destroy(head);

	return 0;
}

