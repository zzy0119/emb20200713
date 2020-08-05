#include <stdio.h>

/*
 修饰变量关键字
 	auto
	static
	const
	register
	volatile
 */

void test();
int main(void)
{
	int a; // auto int a;

	test();
	test();

	return 0;
}

void test()
{
	static int var = 1; // 局部静态变量--->未初始化 bss, 已初始化 data

	var ++;
	printf("var:%d\n", var);
}

