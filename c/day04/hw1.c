#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N	10

int main(void)
{
	int arr[N] = {};
	int max, min;
	int tmp;
	int sum = 0;
	int cnt = 0;

	srand(getpid());

	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 100;	
		printf("%d ", arr[i]);
		sum += arr[i];
		if (arr[i] % 2 == 0)
			cnt ++;
	}
	printf("\n");
	max = min = 0;// 最大最小元素的下标值
	for (int j = 1; j < N; j++) {
		if (arr[j] > arr[max])
			max = j;
		if (arr[j] < arr[min])
			min = j;
	}

	tmp = arr[max];
	arr[max] = arr[min];
	arr[min] = tmp;
	printf("交换最大最小值后\n");
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");

	printf("平均数是%d\n", sum / N);

	for (int i = N-1; i >= 0; i --) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("偶数的个数是:%d\n", cnt);

	return 0;
}

