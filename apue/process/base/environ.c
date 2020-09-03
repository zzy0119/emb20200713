#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
	for (int i = 0; environ[i] != NULL; i++)
		puts(environ[i]);

	puts(getenv("PATH"));
	setenv("PATH", ".", 0);
	puts(getenv("PATH"));

	exit(0);
}

