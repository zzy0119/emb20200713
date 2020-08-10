#include <stdio.h>

int main(void)
{
	char str[] = "hello   world  good";	
	int i, flag = 1;
	int len;

	for (i = 0; str[i]; i++)
		if (str[i] == ' ')
			str[i] = 0;
	len = i; // 原字符串长度

	// "hello\0\0world"
	for (i = 0; i <= len; i++) {
		if (flag == 1 && str[i] != '\0') {
			puts(str+i);
			flag = 0;
		}
		if (str[i] == '\0')
			flag = 1;
	}

	return 0;
}

