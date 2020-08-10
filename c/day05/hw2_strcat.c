#include <stdio.h>

void mystrcat(char s1[], char s2[]);
int main(void)
{
	char str1[100] = {"good morning"};
	char str2[] = "boys and girls";

	mystrcat(str1, str2);

	puts(str1);

	return 0;
}

/*
 字符串拼接
 */
void mystrcat(char s1[], char s2[])
{
	int i = 0, j;

	while (s1[i]) // for (i = 0; s[i]; i++) ;
		i++;
	for (j = 0; s2[j]; j++) {
		s1[i+j] = s2[j];
	}
	s1[i+j] = '\0';
}

