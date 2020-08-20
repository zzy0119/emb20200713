#include <stdio.h>

#include "lstack.h"

int main(void)
{
	int pop;
	lstack_t *s = NULL;

	lstack_init(sizeof(int), &s);

	for (int i = 1; i < 10; i++) {
		lstack_push(s, &i);
	}

	while (!lstack_empty(s)) {
		lstack_pop(s, &pop);
		printf("%d\n", pop);
	}

	lstack_destroy(s);

	return 0;
}

