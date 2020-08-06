#include <stdio.h>

// 递归函数
// n的前n项和
int sumn(int n)
{
	if (n == 0)
		return 0;
	return n + sumn(n-1);
}

// 计算斐波那契数列的第n项 1 1 2 3 5 8 13 .....
int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib(n-1) + fib(n-2);
}

int main(void)
{
	printf("%d\n", sumn(10));
	printf("%d\n", sumn(100));

	for (int i = 1; i <= 20; i++)
		printf("%d ", fib(i));
	printf("\n");

	return 0;
}

