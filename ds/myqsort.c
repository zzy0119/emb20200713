#include <stdio.h>
#include <unistd.h>

void __qsort(int *arr, int low, int high)
{
	int key = arr[low];
	int start = low;
	int end = high;

	if (low >= high)
		return ;

	while (low < high) {
		while (key <= arr[high] && low < high)
			high--;
		// 下标为high比key小 或者low==hight
		if (low != high)
			arr[low] = arr[high];
		while (key >= arr[low] && low < high)
			low++;
		// low元素比key大了 应该在右侧
		if (low != high)
			arr[high] = arr[low];
	}
	arr[low] = key; // key位置确定并左边都小 右边都大
	printf("low:%d, hight:%d\n", low, high);
	sleep(1);
	__qsort(arr, start, low-1);
	__qsort(arr, high+1, end);

}

int myqsort(int *arr, int n)
{
	__qsort(arr, 0, n-1);
}

int main(void)
{
	int arr[] = {3,2,1,9,7,8,4,5,6};
	myqsort(arr, sizeof(arr) / sizeof(*arr));

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)
		printf("%d\n", arr[i]);

	return 0;
}

