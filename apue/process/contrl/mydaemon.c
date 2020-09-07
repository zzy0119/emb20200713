#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int mydaemon(void);
int main(void)
{
	if (mydaemon() == -1) {
		fprintf(stderr, "mydaemon() failed\n");
		exit(1);
	}
	
	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

int mydaemon(void)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		return -1;
	}
	if (pid > 0) {
		// parent
		exit(0);
	}
	// child 不是所在进程组的组长
	if (setsid() == -1) {
		perror("setsid()");
		return -1;
	}

	umask(0);
	chdir("/");

	fd = open("/dev/null", O_RDWR);
	if (fd == -1) {
		perror("open()");
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);

	if (fd > 2)
		close(fd);

	return 0;
}

