#include <stdio.h>
#include <string.h>

#define N	100

void reverseStr(char *s);
int main(int argc, char *argv[])
{
	char str[N] = {};

	if (argc < 2)
		return 1;

	strcpy(str, argv[1]);

	reverseStr(str);
	puts(str);

	return 0;
}

/*
	将给定的字符串中的大写改小写小写改大写 
 */
void reverseStr(char *s)
{
	int i = 0;

	while (s[i]) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + ('a'-'A');
		else if (s[i] >= 'a' && s[i] <= 'z')
			s[i]-= ('a'-'A');
		i++;
	}
}

