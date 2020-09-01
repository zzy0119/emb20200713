#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd;
	int cur_offset;
	char buf[10] = {};

	if (argc < 2)			
		return 1;

	fd = open(argv[1], O_RDWR);
	// if error
	read(fd, buf, 3);
	puts(buf);
	cur_offset = lseek(fd, 10, SEEK_CUR);
	printf("%d\n", cur_offset);
	memset(buf, '\0', 10);
	read(fd, buf, 9);
	puts(buf);

	lseek(fd, 1024, SEEK_END);
	write(fd, "world", 5);
	
	close(fd);

	return 0;
}

