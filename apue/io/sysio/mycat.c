#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE	100

int copy_file(int rfd, int wfd);
int main(int argc, char *argv[])
{
	int fd;

	if (argc < 2)
		return 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
	// 	fprintf(stderr, "open():%s\n", strerror(errno));
		perror("open()");	
		return 1;
	}

	copy_file(fd, 1);

	close(fd);

	return 0;
}

// 将rfd文件全部读出来写入wfd
int copy_file(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = read(rfd, buf, BUFSIZE);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			fprintf(stderr, "read() failed\n");
			return -1;
		}
		write(wfd, buf, cnt);
	}

	return 0;
}


