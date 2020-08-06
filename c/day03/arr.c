#include <stdio.h>

/*
 数组：相同类型元素的集合
 定义
 初始化
 赋值
 取值
 */

int main(void)
{
	// 定义
	int arr[10];
	// 初始化
	int arr2[5] = {1, [4]=10} ;

	// 赋值
	for (int i = 0; i < 10; i++) {
		arr[i] = i+1; // a[b]--->(a+b)
	}

	// 遍历
	for (int i = 0; i < 10; i++)
		printf("%d ", i[arr]);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("%d ", arr2[i]);
	printf("\n");

	return 0;
}

