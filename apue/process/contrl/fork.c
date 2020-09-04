#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int fd;
	char buf[100] = {};

	printf("i am the calling process");
	fflush(NULL);

	fd = open("/etc/passwd", O_RDONLY);

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	// 两份一样的代码同时在运行
	if (pid == 0) {
		// 子进程
		printf("pid:%d, i am child\n", getpid());
		//sleep(40);
	
		read(fd, buf, 99);
		puts(buf);

		close(fd);

		exit(0);
	}

	sleep(3);

	printf("子进程已终止buf:\n");
	puts(buf);
	read(fd, buf, 99);
	puts(buf);

	// 父进程
	printf("pid:%d, i am parent\n", getpid());

	close(fd);

//	sleep(40);
	exit(0);
}

