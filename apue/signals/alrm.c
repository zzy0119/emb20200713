#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void alrm_handler(int s)
{
//	alarm(1);
	for (int i = 0; i < 5; i++) {
		write(1, "!", 1);
		//sleep(1);
	}
}

int main(void)
{
	struct sigaction act;
	struct itimerval itv;

// 	signal(SIGALRM, alrm_handler);
	act.sa_handler = alrm_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaction(SIGALRM, &act, NULL);
//	alarm(3);
	itv.it_interval.tv_sec = 3;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, NULL);

	for (int i = 0; ; i++) {
		write(1, "*", 1);	
		sleep(1);
	}

	exit(0);
}

