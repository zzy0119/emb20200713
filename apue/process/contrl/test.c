#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define START	100
#define END		300

static int is_primer(int n)
{
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}

int main(void)
{
	pid_t pid;

	for (int i = START; i <= END; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			// 判断i是否是质数
			if (is_primer(i))
				printf("[%d]%d is a primer\n", getpid(), i);
			exit(0);
		}
	}

	for (int i = START; i <= END; i++)	
		wait(NULL);

	exit(0);
}
