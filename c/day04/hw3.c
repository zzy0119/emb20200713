#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define N 20

static int isprimer(int n)
{
	if (n <= 1)
		return 0;
	if (n == 2)
		return 1;
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

int main(void)
{
	int arr[N] = {};
	int i;

	srand(getpid());
	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
		printf("%d\n", arr[i]);
		if (isprimer(arr[i]))
			printf("%d是质数\n", arr[i]);
	}

	return 0;
}

