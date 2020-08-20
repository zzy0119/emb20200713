#include <stdio.h>

#include "queue.h"

int main(void)
{
	queue_t *q;
	int n;

	q = queue_init(sizeof(int), 10);

	for (int i = 0; i < 10; i++) {
		if (enq(q, &i) == -1) {
			printf("%d 入队失败\n", i);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (!queue_empty(q)) {
			deq(q, &n);
			printf("%d 出队\n", n);
		}
	}

	for (int i = 0; i < 5; i++) {
		if (enq(q, &i) == -1) {
			printf("%d 入队失败\n", i);
		}
	}

	queue_destroy(q);

	return 0;
}

