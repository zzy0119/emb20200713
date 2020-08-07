#include <stdio.h>

int main(void)
{
	int arr[2][3]; // 二位数组的定义
	int arr2[2][3] = { // {1,2,3,4,5,6} // 初始化
		{1,2,3},
		{4,5,6}
	};
	int i, j;

	// 取出小数组
	for (i = 0; i < 2; i++) {
		// 取出小数组中的成员
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr2[i][j]);	
		}
		printf("\n");
	}

	return 0;
}

