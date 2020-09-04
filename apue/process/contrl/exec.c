#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	printf("main start...\n");
	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
		perror("execl()");
		exit(1);
	}

	wait(NULL);
	printf("main end...\n");

	exit(0);
}

