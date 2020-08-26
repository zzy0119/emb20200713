#include <stdio.h>

int main(void)
{

	// stdin stdout---》行缓存	stderr 无缓存	全缓存(满了才会刷新 4k)
	// 进程结束会刷新所有缓存区
	// 调用fflush();
	printf("hello world");
	fprintf(stderr, "hello error");
	fflush(NULL); // 刷新所有打开的输出流

	while (1)
		;

	return 0;
}

