#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
/*
 最多可以定1024时钟
 */

int main(void)
{

	anytimer_alarm(5, fun1);
	anytimer_alarm(3, fun2);
	anytimer_alarm(10, fun3);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

