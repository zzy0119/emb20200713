#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE	1024

int main(void)
{
	pid_t pid;
	int sv[2] = {};

	if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) == -1) {
		perror("socketpairt()");
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		char buf[BUFSIZE] = {};
		close(sv[0]);
		read(sv[1], buf, BUFSIZE);	
		puts(buf);
		close(sv[1]);
		exit(0);
	}
	close(sv[1]);
	write(sv[0], "good morining", 14);
	close(sv[0]);
	wait(NULL);

	exit(0);
ERROR:
	close(sv[0]);
	close(sv[1]);
	exit(1);
}

