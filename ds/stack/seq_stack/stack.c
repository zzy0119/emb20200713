#include <stdlib.h>
#include <string.h>
#include "stack.h"

// 初始化栈
stack_t *stack_init(int size, int nmembs)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (NULL == s)
		return NULL;
	s->base = calloc(nmembs, size);
	if (NULL == s->base) {
		free(s);
		return NULL;
	}
	s->top = s->base;
	s->size = size;
	s->nmembs = nmembs;

	return s;
}

// 入栈
int push(stack_t *s, const void *data)
{
	if (full(s))
		return -1;
	memcpy(s->top, data, s->size);
	s->top = (char *)s->top + s->size;

	return 0;
}

// 出栈
int pop(stack_t *s, void *data)
{
	if (empty(s))
		return -1;
	s->top = (char *)s->top - s->size;
	memcpy(data, s->top, s->size);

	return 0;
}

// 栈是否空
int empty(const stack_t *s)
{
	return s->base == s->top;
}

// 栈是否满
int full(const stack_t *s)
{
	return ((char *)s->top-(char *)s->base) / s->size == s->nmembs;
}

// 销毁
void destroy(stack_t *s)
{
	free(s->base);
	free(s);
}

