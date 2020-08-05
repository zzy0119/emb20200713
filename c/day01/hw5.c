#include <stdio.h>

int reverseNumber(int n);
int main(void)
{
	int num;
	
	printf("请输入一个整型数:");
	scanf("%d", &num);

	printf("%d的逆序数是%d\n", num, reverseNumber(num));

	return 0;
}

// 求出逆
int reverseNumber(int n)
{
	int res = 0;
	int flag = 1;

	if (n < 0) {
		flag = -1;
		n = -n;
	}
	
	while (n > 0) {
		res = res * 10 + n % 10;
		n /= 10;
	}

	return res * flag;
}

