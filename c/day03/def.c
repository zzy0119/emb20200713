#include <stdio.h>

// 宏
#define NUM	100

// 宏函数
#define SQUARE(x)	(x)*(x)

#define SWAP2NUM(x, y)	\
		do{\
			int t;\
			t = x;\
			x = y;\
			y = t;\
		}while(0)

#define DEBUG
#undef	DEBUG

int main(void)
{
#if 0
	for (int i = 0; i < NUM; i++) {
		printf("i:%d\n", i);
	}
#endif
	int n = 5;
	int res;
	int a = 10, b = 20;

	res = SQUARE(n+2); // n+2*n+2
	printf("res:%d\n", res);

#ifdef DEBUG
	printf("debug.....\n");
#endif

	SWAP2NUM(a, b);
	printf("a:%d, b:%d\n", a, b);

	return 0;
}

