#include <stdlib.h>
#include <string.h>

#include "queue.h"

queue_t *queue_init(int size, int nmembs)
{
	queue_t *q;

	q = malloc(sizeof(queue_t));
	if (NULL == q)
		return NULL;
	q->base = calloc(nmembs, size);
	if (NULL == q->base) {
		free(q);
		return NULL;
	}
	q->front = q->tail = 0;
	q->size = size;
	q->nmembs = nmembs;

	return q;
}

int queue_empty(const queue_t *t)
{
	return t->front == t->tail;
}

int queue_full(const queue_t *t)
{
	return (t->tail+1) % t->nmembs == t->front;
}

int enq(queue_t *t, const void *data)
{
	if (queue_full(t))
		return -1;
	memcpy((char *)t->base+t->tail*t->size, data, t->size);
	t->tail = (t->tail+1) % t->nmembs;
	
	return 0;
}

int deq(queue_t *t, void *data)
{
	if (queue_empty(t))
		return -1;
	memcpy(data, (char *)t->base + t->front*t->size, t->size);
	t->front = (t->front+1) % t->nmembs;

	return 0;
}

void queue_destroy(queue_t *t)
{
	free(t->base);
	free(t);
}





