#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <tbf.h>

#define BUFSIZE	10

int cpfile(int rfd, int wfd);
int main(int argc, char *argv[]) 
{
	int pfd[2] = {};
	pid_t pid;
	int fd;

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		close(pfd[1]);	
		cpfile(pfd[0], 1);
		close(pfd[0]);
		exit(0);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open()");
		goto ERROR;
	}
	close(pfd[0]);
	cpfile(fd, pfd[1]);

	close(pfd[1]);
	close(fd);

	wait(NULL);

	exit(0);
ERROR:
	close(pfd[0]);
	close(pfd[1]);
}

int cpfile(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt, n;
	int td;

	td = tbf_init(BUFSIZE, 100);
	// if error

	while (1) {
		n = tbf_fetch(td, BUFSIZE);
		cnt = read(rfd, buf, n);	
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("read()");
			return -1;
		}
		if (cnt == 0) 
			break;
		write(wfd, buf, cnt);
	}
	
	tbf_destroy(td);

	return 0;
}

