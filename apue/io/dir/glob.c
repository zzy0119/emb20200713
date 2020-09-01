#include <stdio.h>
#include <glob.h>

int main(int argc, char *argv[])
{
	glob_t res;

	if (argc < 2)
		return 0;

	glob(argv[1], GLOB_NOSORT | GLOB_NOCHECK, NULL, &res);

	for (int i = 0; i < res.gl_pathc; i++)
		puts((res.gl_pathv)[i]);

	globfree(&res);

	return 0;
}

