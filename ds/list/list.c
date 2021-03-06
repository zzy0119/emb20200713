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

int list_update(list_t *h, const void *key, cmp_t cmp, const void *newdata)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		if (!cmp(key, cur->data))
			break;
	}
	if (cur == &h->head)
		return -1;
	memcpy(cur->data, newdata, h->size);

	return 0;
}


void *list_firstnode(const list_t *h)
{
	if (h->head.next == &h->head)
		return NULL;
	return (h->head.next)->data;
}

void *list_lastnode(const list_t *h)
{
	struct node_st *last;

	if (h->head.next == &h->head)
		return NULL;

	for (last = h->head.next; last->next != &h->head; last = last->next)
		;
	return last->data;
}

void list_reverse(list_t *h)
{
	struct node_st *cur, *next;

	if (h->head.next == &h->head)
		return;
	cur = (h->head.next)->next;// 第二个结点
	next = cur->next;
	// 是的原链表的第一个结点作为最后一个结点
	(h->head.next)->next = &h->head;
	while (cur != &h->head) {
		cur->next = h->head.next;
		h->head.next = cur; // 头插
		cur = next;
		next = next->next;
	}

}


