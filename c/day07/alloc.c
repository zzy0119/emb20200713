#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverseStr(const char *s);
int mygetline(char **ptr);
int main(int argc, char *argv[])
{
	char *ptr = NULL;
	int n;

	if (argc < 2)
		return 1;

	// 动态开辟 堆空间
#if 0
	ptr = malloc(strlen(argv[1])+1);
	if (NULL == ptr) {
		return 1;
	}
	memset(ptr, '\0', strlen(argv[1])+1); // 将开辟的存储空间置0
#endif
	ptr = calloc(strlen(argv[1])+1, sizeof(char));
	if (NULL == ptr)
		return 1;
	strcpy(ptr, argv[1]);
	puts(ptr);
	free(ptr);

	ptr = reverseStr(argv[1]);
	if (NULL == ptr)
		return 1;
	puts(ptr);
	free(ptr);

	n = mygetline(&ptr);
	printf("字符串长度为%d, %s\n", n, ptr);

	return 0;
}

/*
	定义一个函数，将用户给定的字符串倒叙存储到函数内开辟的存储空间中并返回
 */
char *reverseStr(const char *s)
{
	char *ptr;
	int i, j;

	ptr = malloc(strlen(s)+1);
	if (NULL == ptr)
		return NULL;
	for (i = strlen(s)-1, j=0; i >= 0; i--, j++) {
		ptr[j] = s[i];
	}
	ptr[j] = '\0';

	return ptr;
}

/*
	从终端读入一个字符串，并存放到堆空间中，要做到空间的大小与字符串大小一致 
 */
int mygetline(char **ptr)
{
	char ch;
	char *s = NULL, *new = NULL;
	int i = 0, len = 1;

	s = calloc(1, 1); // "\0"

	while (1) {
		scanf("%c", &ch);	
		if (ch == '\n')
			break;
		new = malloc(len+1);	
		memset(new, '\0', len+1);
		strcpy(new, s);
		new[i] = ch;
		free(s);
		s = new;
		i++;
		len++;
	}
	*ptr = s;
	return i;
}










