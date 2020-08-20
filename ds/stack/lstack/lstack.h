#ifndef __LSTACK_H
#define __LSTACK_H

#include "llist.h"

// 定义链栈类型
typedef llisthead_t lstack_t;

// 初始化链栈
int lstack_init(int size, lstack_t **s);

// 入栈
int lstack_push(lstack_t *s, const void *data);

// 出栈
int lstack_pop(lstack_t *s, void *data);

// 栈空
int lstack_empty(const lstack_t *s);

// 销毁
void lstack_destroy(lstack_t *s);

#endif

