#include <stdio.h>

int main(void)
{
	int arr[10][10] = {};
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			arr[i][0] = 1;
			if (i >= j && i > 0) {
				// 左下角
				arr[i][j] = arr[i-1][j]+arr[i-1][j-1];
			}
		}
	}

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (i >= j) {
				printf("%3d ", arr[i][j]);
			}
		}
		printf("\n");
	}

	return 0;
}

