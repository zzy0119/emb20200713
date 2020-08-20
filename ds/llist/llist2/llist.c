#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "llist.h"

int llisthead_init(int size, llisthead_t **h)
{
	*h = malloc(sizeof(llisthead_t));
	if (NULL == *h)
		return -1;
	(*h)->head.prev = (*h)->head.next = &(*h)->head;
	(*h)->size = size;

	return 0;
}

static void insert(struct node_st *new, struct node_st *p, struct node_st *n)
{
	new->next = n;
	new->prev = p;
	p->next = new;
	n->prev = new;
}

int llist_insert(llisthead_t *h, const void *data, insert_way_t way)
{
	struct node_st *new = NULL;

	if (!(way == INSERT_HEAD || way == INSERT_TAIL))
		return -1;

	new = malloc(sizeof(struct node_st)+h->size);
	if (NULL == new)
		return -1;
	memcpy(new->data, data, h->size);
	switch (way) {
		case INSERT_HEAD:
			insert(new, &h->head, h->head.next);
			break;
		case INSERT_TAIL:
			insert(new, h->head.prev, &h->head);	
			break;
		default:
			break;
	}
	
	return 0;
}

static void delete(struct node_st *del)
{
	del->prev->next = del->next;
	del->next->prev = del->prev;	
	free(del);
}

int llist_delete(llisthead_t *h, const void *key, cmp_t *cmp)
{
	struct node_st *cur;	

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		if (!cmp(cur->data, key)) {
			delete(cur);	
			return 0;
		}
	}
	return -1;
}

void llist_traval(const llisthead_t *h, pri_t pri)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next)
		pri(cur->data);
}

void llist_destroy(llisthead_t *h)
{
	while (h->head.next != &h->head) {
		delete(h->head.next);	
	}	
	free(h);
}

void *llist_pop(const llisthead_t *h)
{
	if (h->head.next == &h->head && h->head.prev == &h->head)
		return NULL;
	return (h->head.next)->data;
}

void *llist_last(const llisthead_t *h)
{
	if (h->head.next == &h->head && h->head.prev == &h->head)
		return NULL;
	return (h->head.prev)->data;
}

int llist_all_membs(const llisthead_t *h)
{
	struct node_st *cur;
	int n = 0;

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		n ++;
	}

	return n;
}

int llist_fetch(llisthead_t *h, const void *key, cmp_t *cmp, void *data)
{
	struct node_st *cur;	

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		if (!cmp(cur->data, key)) {
			memcpy(data, cur->data, h->size);
			delete(cur);
			return 0;
		}
	}

	return -1;
}

int llist_empty(const llisthead_t *h)
{
	return h->head.next == &h->head && h->head.prev == &h->head;
}




