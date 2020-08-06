#include <stdio.h>

int main(void)
{
	int m = 10, n = 20;

	// 变参函数	函数的入栈顺序是至右向左
	printf("hello world %d %d\n", m, m++); // a=m++, b=m

	return 0;
}

