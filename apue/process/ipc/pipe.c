#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	100

// 练习: 父进程将argv[1]文件 写入管道，每秒钟写入10个字节(用现成的流量控制),子进程读管道数据写到标准输出

int main(void)
{
	pid_t pid;
	int pipefd[2];
	char buf[BUFSIZE] = {};

	if (pipe(pipefd) == -1) {
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		close(pipefd[0]);
		write(pipefd[1], "good", 4);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	read(pipefd[0], buf, BUFSIZE);
	puts(buf);
	close(pipefd[0]);
	wait(NULL);

	exit(0);
ERROR:
	close(pipefd[0]);
	close(pipefd[1]);
}

