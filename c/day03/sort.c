#include <stdio.h>

int main(void)
{
	int arr[] = {6, 2, 4, 3, 1, 7, 9, 8, 3, 2};
	int t, j, i;

#if 0
	// 冒泡排序
	for (i = 0; i < 9; i++) { // 比较的趟数
		// 每一趟，要比较的数值范围	
		for (j = 0; j < 9-i; j++) { // n-i-1
			if (arr[j] > arr[j+1]) {
				t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;		
			}
		}
	}
#endif

#if 0
	// 直接插入排序   从小到大
	for (i = 1; i < 10; i++) { // 待插入到有序序列的变量
		t = arr[i]; // 存储带插入的元素
		for (j = i-1; j >= 0; j--) { // 遍历所有有序序列中的元素，依次与带插入元素比较
			if (t < arr[j]) {
				arr[j+1] = arr[j];
			} else {
				// 所选择的元素 位置已找到
				break;
			}
		}
		// 将待插入元素插入
		arr[j+1] = t;
	}
#endif

	// 选择排序
	for (i = 0; i < 9; i++) { // 选出待排序的位置
		// 待比较的所有元素
		for (j = i+1; j < 10; j ++) {
			if (arr[i] < arr[j]) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}

	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

