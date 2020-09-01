#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	fd = open("./ps", O_RDWR);
	if (fd == -1) {
		perror("open()");
		return 1;
	}

#if 0
	// 不原子操作   原子操作：不可分割的最小单位
	close(1);
	dup(fd);
#endif
	dup2(fd, 1); // 原子操作

	printf("apue is comming\n");

	return 0;
}

