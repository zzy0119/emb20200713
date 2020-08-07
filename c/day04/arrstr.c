#include <stdio.h>

int mystrlen(char s[]);
int main(void)
{
	// 字符数组
	char str[] = "hello wrold";
	char str2[] = {"hello wrold"};
	char str3[] = {'h', 'e', 'l', 'l', '0', ' '}; // 不是字符串

	// 读入字符串
	// scanf("%s", str);
	gets(str);
	// 遍历字符串
	puts(str); // printf("%s\n", str);

	printf("%d\n", mystrlen(str));
	printf("%d\n", mystrlen(str2));

	return 0;
}

/*
 计算出字符串的长度
 */
int mystrlen(char s[])
{
	int i = 0;

	while (s[i])
		i++;

	return i;
}

