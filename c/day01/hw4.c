#include <stdio.h>

int isPrimer(int n);
int main(void)
{
	int cnt = 0;

	for (int i = 1; i <= 100; i++) {
		if (isPrimer(i))
			cnt ++;
	}
	printf("%d\n", cnt);

	return 0;
}

// 判断给定的变量是否是质数
int isPrimer(int n)
{
	if (n < 2)
		return 0;

	if (n == 2)
		return 1;

	for (int i = 2; i < n; i++)	{
		if (n % i == 0)
			return 0;
	}

	return 1;
}



