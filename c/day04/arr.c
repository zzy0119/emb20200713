#include <stdio.h>

int sumofarr(int arr[], int n);
int main(void)
{
	int a;
	int arr[3] = {1, 5, 3};

	printf("sizeof(a):%ld\n", sizeof(a));
	printf("sizeof(a):%ld\n", sizeof(int));
	printf("sizeof(a):%ld\n", sizeof a);
	// printf("sizeof(a):%d\n", sizeof int);

	printf("%ld\n", sizeof(arr));

	printf("%d\n", sumofarr(arr, sizeof(arr) / sizeof(arr[0])));

	return 0;
}

/*
 计算数组中所有成员和
 */
int sumofarr(int arr[], int n)
{
	int s = 0;

	for(int i = 0; i < n; i++)
		s += arr[i];

	return s;
}


