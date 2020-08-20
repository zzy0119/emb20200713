#include <stdio.h>

#include "stack.h"

#define NAMESIZE 32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

int main(void)
{
	struct stu_st stu;
	stack_t *s;

	s = stack_init(sizeof(struct stu_st), 10);
	// if error

	for (int i = 0; i < 15; i++) {
		stu.id = i+1;
		snprintf(stu.name, NAMESIZE, "小白%d", i+1);
		if (push(s, &stu) == -1) {
			printf("入栈失败\n");
		}
	}

	while (!empty(s)) {
		pop(s, &stu);
		printf("%d %s 出栈\n", stu.id, stu.name);
	}

	destroy(s);
	
	return 0;
}

