#include <stdio.h>
#include <unistd.h>

int main(void)
{
	write(1, "output", 6);
	write(2, "errput", 6);

	return 0;
}


