#include <stdio.h>

typedef struct {
	char ch1;
	int a;
	char ch2;
	short ch3;
}test_t;

int main(void)
{
	test_t t;

	printf("%ld\n", sizeof(test_t));
	printf("%p\n", &t.ch1);
	printf("%p\n", &t.a);
	printf("%p\n", &t.ch2);
	printf("%p\n", &t.ch3);

	return 0;
}

