#include <stdio.h>

/*
   四则运算
   ./a.out 1 + 2
   1 + 2 = 3
   ./a.out 1 x 100
   1 * 100 = 
 
 */

int main(int argc, char **argv)
{
	// 字符串变量
	char str[2][50] = {"hello", "world"};
	// 字符串常量
	char *s[2] = {"hello", "world"}; // 指针数组
	char **p = s; // 二级指针

	for (int i = 0; i < argc; i++)
		puts(argv[i]);

	return 0;
}

