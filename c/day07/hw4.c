#include <stdio.h>

void sepStr(char *s, char **p, int n);
int main(void)
{
	char arr[] = "good  mor   ning every one";
	char *res[20] = {}; 

	sepStr(arr, res, 20);
	for (int i = 0; res[i] != NULL; i++)
		puts(res[i]);

	return 0;
}

/*
 p存放切割后每一个字符串的首地址的那个数组的地址
 n数组成员个数
 */
void sepStr(char *s, char **p, int n)
{
	int i = 0;
	int first = 0;

	while (*s && i < n) {
		if (*s != ' ' && first == 0) {
			p[i] = s;
			first ++;
			i++;
		}
		if (*s == ' ') {
			*s = '\0';
			first = 0;
		}
		s ++;
	}
}


