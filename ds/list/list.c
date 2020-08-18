#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

lhead_t *lhead_init(int size)
{
	lhead_t *me;

	me = malloc(sizeof(lhead_t));
	if (NULL == me)
		return NULL;
	me->head.data = NULL;
	me->head.next = &me->head;
	me->size = size;

	return me;
}

/*
 插入
 */
int lhead_insert(lhead_t *h, const void *data, way_t way)
{
	struct node_st *new = NULL;
	struct node_st *cur = NULL;

	// 结点开辟存储空间
	new = malloc(sizeof(*new));
	if (NULL == new)
		return -1;
	// 结点的数据域开辟存储空间
	new->data = calloc(1, h->size);
	if (NULL == new->data) {
		free(new);
		return -1;
	}
	// 拷贝数据
	memcpy(new->data, data, h->size);

	// 插入链表中
	switch (way) {
		case HEAD:
			// 头插
			new->next = h->head.next;
			h->head.next = new;
			break;
		case TAIL:
			// 尾插
			for (cur = h->head.next; cur->next != &h->head; cur = cur->next)
				;
			new->next = &h->head;
			cur->next = new;
			break;
		default :
			free(new->data);
			free(new);
			return -1;
	}

	return 0;
}

#if 0
/*
 删除
 */
int lhead_delete(lhead_t *h, const void *key, cmp_t cmp);
#endif

/*
 遍历
 */
void lhead_traval(const lhead_t *h, pri_t pri)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		pri(cur->data);
	}
}

/*
 销毁 
 */
void lhead_destroy(lhead_t *h)
{
	struct node_st *del;	

	del = h->head.next;
	while (del != &h->head) {
		h->head.next = del->next;	
		del->next = NULL;
		free(del->data);	
		free(del);
		del = h->head.next;
	}
	free(h);
}


