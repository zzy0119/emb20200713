#include <stdio.h>

void test(int *a, int n);
int main(void)
{
	int arr[] = {3,2,7}; 
	// arr类型 int * 常量 不能改变

	printf("sizeof(arr):%ld\n", sizeof(arr));

	test(arr, 3); // 

	return 0;
}

// void test(int a[], int n)
void test(int *a, int n)
{
	printf("sizeof(a):%ld\n", sizeof(a));
}

