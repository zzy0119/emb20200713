#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "list.h"

struct node_st {
	int score;
	struct list_head node;
};

int main(void)
{
	LIST_HEAD(head);
	struct node_st *data;
	struct list_head *pos;

	srand(getpid());
	for (int i = 0; i < 10; i++) {
		data = calloc(1, sizeof(struct node_st));
		// if error
		// data->score = rand() % 101;	
		data->score = 100 - i;
		list_add_tail(&data->node, &head);
	}

	// 遍历	
	list_for_each(pos, &head) {
		data = list_entry(pos, struct node_st, node);
		printf("%d ", data->score);
	}
	printf("\n");

	return 0;
}


