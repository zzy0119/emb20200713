#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int var = 100;
	pid_t pid;

	pid = vfork();
	if (-1 == pid) {
		perror("vfork()");
		exit(1);
	}

	if (pid == 0) {
		sleep(3);
		var = 200;
		_exit(0);
	}
	printf("var:%d\n", var);

	exit(0);
}

