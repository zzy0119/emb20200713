#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

int main(void)
{
	struct sigaction act, oldact;
	pid_t pid;

	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, &oldact);

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		sigaction(SIGCHLD, &oldact, NULL);
		exit(1);
	}
	if (pid == 0) {
		for (int i = 0; i < 5; i++) {
			write(1, "*", 1);
			sleep(1);
		}
		exit(0);
	}
	if (wait(NULL) == -1) {
		perror("wait()");	
		sigaction(SIGCHLD, &oldact, NULL);
		exit(1);
	}
	printf("main will be endding\n");

	exit(0);
}

