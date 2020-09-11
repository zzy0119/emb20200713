#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static void sig_handler(int s)
{
	;
}

int main(void)
{
	pid_t pid;

	signal(SIGINT, sig_handler);	

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		pause();
		write(1, "world", 5);
		exit(1);
	}
	sleep(3);
	write(1, "hello", 5);
	kill(pid, SIGINT);
	wait(NULL);

	exit(0);
}

