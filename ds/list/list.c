#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

list_t *list_init(int size)
{
	list_t *me;

	me = malloc(sizeof(list_t));
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
int list_insert(list_t *h, const void *data, way_t way)
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

/*
 删除
 */
int list_delete(list_t *h, const void *key, cmp_t cmp)
{
	struct node_st *prev, *cur;

	for (prev = &h->head, cur=prev->next; cur != &h->head; prev=cur, cur=cur->next) {
		if (!cmp(key, cur->data)) {
			break;
		}
	}
	if (cur == &h->head)
		return -1;
	prev->next = cur->next;
	cur->next = NULL;
	free(cur->data);
	free(cur);

	return 0;
}

/*
 遍历
 */
void list_traval(const list_t *h, pri_t pri)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		pri(cur->data);
	}
}

/*
 销毁 
 */
void list_destroy(list_t *h)
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


