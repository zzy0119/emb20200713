#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void sig_handler(int s)
{
	write(1, "!", 1);
}

int main(void)
{
	sigset_t set, oldset;

	signal(SIGINT, sig_handler);	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, &oldset);
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col ++) {
			write(1, "*", 1);	
			sleep(1);
		}
		write(1, "\n", 1);
		sigsuspend(&oldset);
		/*
		 sigprocmask(SIG_SETMASK, &oldset, &save);
		 pause();
		 sigprocmask(SIG_SETMASK, &save, NULL);
		 */
	}

	exit(0);
}

