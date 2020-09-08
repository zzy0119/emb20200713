#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void alrm_handler(int s)
{
	alarm(3);
	write(1, "!", 1);
}

int main(void)
{

	signal(SIGALRM, alrm_handler);
	alarm(3);

	for (int i = 0; ; i++) {
		write(1, "*", 1);	
		sleep(1);
	}

	exit(0);
}

