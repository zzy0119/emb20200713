#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t tm;
	struct tm *tmp;
	char buf[64] = {};

	//time(&tm);
	tm = time(NULL);

	tmp = localtime(&tm);

	strftime(buf, 63, "%Y-%m-%d %H:%M:%S", tmp);
	puts(buf);

	return 0;
}

