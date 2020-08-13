#include <stdio.h>

typedef int *TYPET;

#define TYPED	int *

int main(void)
{
	TYPET a, b;
	TYPED m, n; // int *m, n;

	printf("sizeof(a):%ld\n", sizeof(a));
	printf("sizeof(b):%ld\n", sizeof(b));
	printf("sizeof(m):%ld\n", sizeof(m));
	printf("sizeof(n):%ld\n", sizeof(n));

	return 0;
}

