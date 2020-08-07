#include <stdio.h>

/*
 定义两个字符数组，成员个数都为100
 读入两个字符串存储到字符数组中，比较两个字符串的大小
 */
#define N 100
int mystrcmp(char s1[], char s2[]);
int main(void)
{
	char str1[N] = {};
	char str2[N] = {};
	int ret;

	printf("请输入第一个字符串:");
	scanf("%s", str1);
	printf("请输入第二个字符串:");
	scanf("%s", str2);

	ret = mystrcmp(str1, str2);
	if (ret == 0) {
		printf("%s等于%s\n", str1, str2);
	} else if(ret > 0) {
		printf("%s大于%s\n", str1, str2);
	} else {
		printf("%s小于%s\n", str1, str2);
	}

	return 0;
}

int mystrcmp(char s1[], char s2[])
{
	int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0') {
		i++;
	}
	if (s1[i] == '\0') // 字符串相等
		return 0;

	return s1[i] - s2[i];
}

