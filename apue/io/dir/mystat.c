#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	struct stat res;

	if (argc < 2)
		return 1;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	// 文件的类型
	if ((res.st_mode & S_IFMT) == S_IFREG)
		putchar('-');
	else if ((res.st_mode & S_IFMT) == S_IFDIR)
		putchar('d');
	printf("\n");

	return 0;
}
