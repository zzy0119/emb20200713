#include <stdio.h>

// 参数2的n次方 不能超过最大字节个数的元素
// #pragma pack(2)

struct test_st {
	char ch;
	int n;
}__attribute__((packed)); // 使得结构体单字节对齐

struct test2_st {
	char ch;
	long n;
};

int main(void)
{
	struct test2_st test;
	/*
	 &test.n--->p
	 &((strcut test2_st *)0)->n // n的偏移量
	 */

	printf("%ld\n", sizeof(struct test_st));
	printf("%ld\n", sizeof(struct test2_st));

	printf("%d\n", (int)(&((struct test2_st *)0)->n));


	return 0;
}
