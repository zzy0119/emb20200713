#include <stdio.h>
#include "lstack.h"

// 初始化链栈
int lstack_init(int size, lstack_t **s)
{
	return llisthead_init(size, s);
}

// 入栈
int lstack_push(lstack_t *s, const void *data)
{
	return llist_insert(s, data, INSERT_HEAD);
}

static int fun(const void *data, const void *key)
{
	return 0;
}

// 出栈
int lstack_pop(lstack_t *s, void *data)
{
	return llist_fetch(s, NULL, fun, data);
}

// 栈空
int lstack_empty(const lstack_t *s)
{
	return llist_empty(s);
}

// 销毁
void lstack_destroy(lstack_t *s)
{
	llist_destroy(s);
}

