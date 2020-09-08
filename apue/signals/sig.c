#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void handler(int s)
{
	write(1, "!", 1);
}

int main(int argc, char *argv[]) 
{
	signal(SIGINT, handler);
	
	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

