#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void handler1(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void handler2(void)
{
	printf("%s is called\n", __FUNCTION__);
}

int main(void)
{
	// 终止处理程序的注册
	atexit(handler1);
	atexit(handler2);

	printf("afternoon");
	// return 0;
	// exit(EXIT_SUCCESS);
	_exit(0);
}

