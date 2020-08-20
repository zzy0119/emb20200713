#ifndef __LQUEUE_H
#define __LQUEUE_H

#include "/home/zzy/code20200713/emb20200713/ds/llist/llist2/llist.h"

typedef llisthead_t lqueue_t;

int lqueue_init(int size, lqueue_t **lq);

// 是否空
int lqueue_empty(const lqueue_t *lq);

// 入队
int lqueue_enq(lqueue_t *lq, const void *data);

// 出队
int lqueue_deq(lqueue_t *lq, void *data);

void lqueue_destroy(lqueue_t *lq);

#endif

