#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int delArr(int **arr, int *n, int key);
int addArr(int **arr, int *n, int elm);
void showarr(int *arr, int n);
int main(void)
{
	int choose;
	int *p = NULL;
	int n = 0;
	int elm;

	while (1) {
		printf("请选择你想要的操作:\n");
		printf("1. 增加数组元素 2. 删除 3. 显示整个数组 9.退出\n");
		scanf("%d", &choose);
		if (choose == 9)
			break;
		switch(choose) {
			case 1:
				printf("请输入你要增加的元素:");
				scanf("%d", &elm);
				addArr(&p, &n, elm);
				break;
			case 2:
				printf("你要删除哪一个元素:");
				scanf("%d", &elm);
				delArr(&p, &n, elm);
				break;
			case 3:
				showarr(p, n);
				break;	
			default:
				break;
		}

	}

	return 0;
}

int addArr(int **arr, int *n, int elm)
{
	int *new;
	new = realloc(*arr, (*n+1)*sizeof(int));
	if (new == NULL)
		return -1;
	*arr = new;
	(*arr)[*n] = elm;
	(*n)++;
	
	return 0;
}

int delArr(int **arr, int *n, int key)
{
	int *new;
	int i;
	for (i = 0; i < *n; i++) {
		if (key == (*arr)[i])
			break;
	}
	if (i == *n)
		return -1;
	// i就是要删除的元素
#if 0
	for (int j = i; j < *n-1; j++) {
		(*arr)[j] = (*arr)[j+1];	
	}
#endif
	memcpy(*arr+i, *arr+i+1, (*n-(i+1))*sizeof(int));
	(*n)--;

	new = realloc(*arr, *n * sizeof(int));
	if (NULL == new)
		return -1;
	*arr = new;

	return 0;
}

void showarr(int *arr, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}




