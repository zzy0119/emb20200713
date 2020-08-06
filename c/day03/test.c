#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define N	10

int main(void)
{
	int arr[N];
	int max, min;

	// 为随机数提供种子
	// srand(time(NULL));
	srand(getpid());

	// 读入用户输入的是个整型数
	for (int i = 0; i < 10; i++) {
#if 0
		printf("请输入第%d数:", i+1);
		scanf("%d", arr+i);
#endif
		arr[i] = rand() % 100;
		printf("%d ", arr[i]);
	}
	printf("\n");

	max = min = arr[0];
	for (int i = 1; i < 10; i++) {
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	printf("max:%d, min:%d\n", max, min);

	return 0;
}

