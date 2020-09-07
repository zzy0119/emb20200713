#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	printf("the calling process:pid:%d, pgid:%d, sid:%d\n", getpid(), getpgrp(), getsid(0));

	pid = fork();
	if (pid < 0) {
		perror("fork()");
		exit(1);
	}

	if (pid == 0) {
		printf("child:pid:%d, pgid:%d, sid:%d\n", getpid(), getpgrp(), getsid(0));
		setpgid(getpid(), getpid());	
		printf("after set child:pid:%d, pgid:%d, sid:%d\n", getpid(), getpgrp(), getsid(0));
		exit(0);
	}
	wait(NULL);

	exit(0);
}

