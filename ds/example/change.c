#include <stdio.h>
#include <stdlib.h>
#include <stack.h> // 路径已加入配置文件~/.bashrc

int main(int argc, char *argv[])
{
	stack_t *s;
	int n, t;

	if (argc < 2)
		return 1;

	s = stack_init(sizeof(int), 64);
	if (NULL == s)
		return -1;
	
	n = atoi(argv[1]);
	while (n) {
		t = n % 2;
		push(s, &t);
		n /= 2;
	}

	while (!empty(s)) {
		pop(s, &t);
		printf("%d", t);
	}
	printf("\n");
	destroy(s);

	return 0;
}

