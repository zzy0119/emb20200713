#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct {
	void *base;
	int front;// 队头下标
	int tail;// 队尾下标
	int size;
	int nmembs;
}queue_t;

queue_t *queue_init(int size, int nmembs);

int queue_empty(const queue_t *t);

int queue_full(const queue_t *t);

int enq(queue_t *t, const void *data);

int deq(queue_t *t, void *data);

void queue_destroy(queue_t *t);

#endif

