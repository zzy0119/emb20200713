#include <stdlib.h>
#include <string.h>

#include "seq.h"

int seq_init(int size, seq_t **s)
{
	seq_t *me = NULL;

	me = malloc(sizeof(seq_t));
	if (NULL == me)
		return -1;
	me->size = size;
	me->nmemb = 0;
	me->ptr = NULL;
	*s = me;

	return 0;
}

int seq_add(seq_t *s, const void *data)
{
	void *new;
	// s->ptr 首地址
	new = realloc(s->ptr, (s->nmemb+1)*s->size);
	if (NULL == new)
		return -1;
	s->ptr = new;
	memcpy((char *)s->ptr+s->nmemb*s->size, data, s->size);
	s->nmemb ++;

	return 0;
}

int seq_del(seq_t *s, const void *key, cmp_t cmp)
{
	int i;
	char *start;
	// 找
	for (i = 0; i < s->nmemb; i++) {
		if (cmp((char *)s->ptr+i*s->size, key) == 0)
			break;
	}
	if (i == s->nmemb) {
		// 没有要删除的元素
		return -1;
	}

	// 删	
	start = (char *)s->ptr;
	memcpy(start+i*s->size, start+(i+1)*s->size, (s->nmemb-(i+1))*s->size);
	s->nmemb--;
	start = realloc(s->ptr, s->nmemb*s->size);
	if (NULL == start)
		return -1;
	s->ptr = start;

	return 0;
}

void seq_traval(const seq_t *s, pri_t pri)
{
	int i;

	for (i = 0; i < s->nmemb; i++) {
		pri((char *)s->ptr+i*s->size);	
	}
}


