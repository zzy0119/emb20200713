#include <stdio.h>

void mystrcopy(char dest[], char str[]);
int main(void)
{
	char str1[] = "hello world";
	char str2[] = "good";
	mystrcopy(str1, str2);

	puts(str1);

	return 0;
}

/*
 字符串的复制
 */
void mystrcopy(char dest[], char str[])
{
	int i = 0;

	while (str[i]) {
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}



