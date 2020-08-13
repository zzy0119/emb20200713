#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(const void *, const void *); // 函数指针类型

int sort(void *arr, int n, int size, cmp_t);
int cmp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d2 - *d1;
}

int cmp_string(const void *data1, const void *data2)
{
	char **d1 = (char **)data1;
	char **d2 = (char **)data2;

	return strcmp(*d2, *d1);
}

int main(void)
{
	int num[10] = {3,1,2,6,7,8,9,4,5,0};
	char *str[] = {"he", "hel", "abort", "about", "cell", "caculate"};

	sort(num, 10, sizeof(int), cmp_int);
	for (int i = 0; i < 10; i++)
		printf("%d ", num[i]);
	printf("\n");

	sort(str, sizeof(str) / sizeof(str[0]), sizeof(char *), cmp_string);
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
		puts(str[i]);

	return 0;
}

/*
 任意类型的数组排序
 */
int sort(void *arr, int n, int size, cmp_t cmp)
{
	int i, j;

	char *p = malloc(size);
	// if error

	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (cmp((char *)arr+j*size, (char *)arr+(j+1)*size) > 0) {
				memcpy(p, (char *)arr+j*size, size);	
				memcpy((char *)arr+j*size, (char *)arr+(j+1)*size, size);
				memcpy((char *)arr+(j+1)*size, p, size);
			}
		}	
	}
	free(p);

	return 0;
}

