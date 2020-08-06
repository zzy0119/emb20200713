#include <stdio.h>

/*
 修饰变量关键字
 	auto 默认
	static
	const
	register --->寄存器变量
	volatile --->易失变量
 */

static int g; // 限制全局变量作用域在本文件

static void test(); // 限制此函数只能在本文件中调用
int main(void)
{
	int a; // auto int a;
	const int b = 10; // 常变量

	b = 20;

	test();
	test();

	return 0;
}

static void test() 
{
	static int var = 1; // 局部静态变量--->未初始化 bss, 已初始化 data

	var ++;
	printf("var:%d\n", var);
}

