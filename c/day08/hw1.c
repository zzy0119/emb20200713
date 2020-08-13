#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_str(char *str);
int main(int argc, char *argv[])
{
	char *p;

	if (argc < 2)
		return 1;

	p = malloc(strlen(argv[1])+1);
	if (NULL == p)
		return 1;
	strcpy(p, argv[1]);
	sort_str(p);
	puts(p);

	return 0;
}

/*
 字符串排序
 */
void sort_str(char *str)
{
	int i, j;
	int len = strlen(str);
	char t;
	int min_index;

	for (i = 0; i < len-1; i++) {
		min_index = i;
		for (j = i+1; j < len; j++) {
			if (str[j] < str[min_index])
				min_index = j;
		}
		if (min_index != i) {
			t = str[i];
			str[i] = str[min_index];
			str[min_index] = t;
		}
	}	
}




