#include <stdio.h>

#include "lqueue.h"

int main(void)
{
	lqueue_t *q;
	int n;

	lqueue_init(sizeof(int), &q);

	for (int i = 1; i < 10; i++) {
		lqueue_enq(q, &i);
	}

	while (!lqueue_empty(q)) {
		lqueue_deq(q, &n);
		printf("%d\n", n);
	}

	lqueue_destroy(q);

	return 0;
}

