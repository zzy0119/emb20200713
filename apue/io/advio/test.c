#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("/dev/tty9", O_WRONLY);
	if (fd == -1) {
		perror("open()");
		return 1;
	}

	write(fd, "hello", 5);
	close(fd);

	return 0;
}

