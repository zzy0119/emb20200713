#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	printf("i am the calling process\n");
	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	// 两份一样的代码同时在运行
	if (pid == 0) {
		// 子进程
		printf("pid:%d, i am child\n", getpid());
		sleep(40);
		exit(0);
	}

	// 父进程
	printf("pid:%d, i am parent\n", getpid());

	sleep(40);
	exit(0);
}

