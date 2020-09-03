#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat res;
	char *ptr;

	if (argc < 2)
		return 1;

	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		perror("open()");
		return 1;
	}
	
	if (fstat(fd, &res) == -1) {
		perror("fstat()");
		close(fd);
		return 1;
	}

	ptr = mmap(NULL, res.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == ptr) {
		perror("mmap()");
		close(fd);
		return 1;
	}
	puts(ptr);
	munmap(ptr, res.st_size);

	close(fd);

	return 0;
}

