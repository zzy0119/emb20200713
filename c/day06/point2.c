#include <stdio.h>

int main(void)
{
	int arr[] = {3,2,1,6,7,9,8};
	int *p = arr;

	printf("%d\n", *p++); // a = *p++;
	printf("%d\n", (*p)++); // a = (*p)++;
	printf("%d\n", ++*p); // a = ++*p;
	printf("%d\n", ++(*p));

	return 0;
}

