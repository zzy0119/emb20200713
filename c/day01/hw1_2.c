#include <stdio.h>

#define START	100
#define END		1000

int isDivisible(int n);
int isFlower(int n);

int main(void)
{
#if 0
	for (int i = START; i <= END; i++) {
		if (isDivisible(i)) {
			printf("%d可以同时被3和5整除\n", i);
		}
	}
#endif

	// 统计100~1000之间的所有水仙花
	for (int i = START; i < END; i ++) {
		if (isFlower(i))
			printf("%d是一个水仙花数\n", i);
	}

	return 0;
}

/*
@n: 待判断的数值
return: 0否 1是
 */
int isDivisible(int n)
{
	return n % 3 == 0 && n % 5 == 0;
}

/*
 判断给定的数值是否是水仙花数
 */
int isFlower(int n)
{
	int s = 0, save = n;
	int t;

	while (n > 0) {
		t = n % 10;// 取出最低位
		s += t * t *t;
		n /= 10; // n = n / 10;
	}
	return s == save;
}






