#include <stdio.h>

// const修饰指针

int main(void)
{
	char str[] = "c plus plus";
	// const char *p = "good afternoon"; // 字符串常量
	char const *p = "good"; // 常量(de)指针
	char *const q = str;// 指针(de)常量
 
	p = str;

	printf("%p\n", p);
	p++;
	printf("%p\n", p);
#define CONSTQ
#ifdef CONSTQ
	*p = 'm';// 编译没有报错，但是不能改变常量的值
#endif

	*q = 'h';
	// q ++;

	return 0;
}

