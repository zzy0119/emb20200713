#include <stdio.h>

#include "lqueue.h"

int lqueue_init(int size, lqueue_t **lq)
{
	return llisthead_init(size, lq);
}

// 是否空
int lqueue_empty(const lqueue_t *lq)
{
	return llist_empty(lq);
}

// 入队
int lqueue_enq(lqueue_t *lq, const void *data)
{
	return llist_insert(lq, data, INSERT_TAIL);
}

static int always_cmp(const void *data, const void *key)
{
	return 0;
}

// 出队
int lqueue_deq(lqueue_t *lq, void *data)
{
	return llist_fetch(lq, NULL, always_cmp, data);
}

// 销毁
void lqueue_destroy(lqueue_t *lq)
{
	llist_destroy(lq);
}


