#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	system("cp /etc/passwd ps");

	return 0;
}

int mysystem(const char *ptr)
{
	pid_t pid;

	pid = fork();
	//if error

	if (pid == 0) {
		// exec...(ptr);
	}
	wait(NULL);
	return 0;
}


