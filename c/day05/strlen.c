#include <stdio.h>

int mystrlen(const char *s);
int main(void)
{
	char str[] = "hello world";

	printf("%d\n", mystrlen(str));
	
	return 0;
}

/*
 计算出字符串的长度
 */
int mystrlen(const char *s)
{
	int i = 0;

	while (s[i])
		i++;

	return i;
}

