#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define CPS		10
#define BUFSIZE	CPS
#define BURST	10*CPS

static int token = 0;

int copy_file(int rfd, int wfd);
int main(int argc, char *argv[])
{
	int fd;

	if (argc < 2)
		return 1;
	do {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			if (errno == EINTR)
				continue;
			perror("open()");	
			return 1;
		} else
			break;
	} while (1);

	copy_file(fd, 1);

	close(fd);

	return 0;
}

static void alrm_handler(int s)
{
	alarm(1);
	token += CPS;
	if (token >= BURST)
		token = BURST;
}

// 将rfd文件全部读出来写入wfd
int copy_file(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt, ret, pos;

	signal(SIGALRM, alrm_handler);	
	alarm(1);

	while (1) {
		// 流量控制 --->令牌桶
		while (token <= 0)	
			pause();
		token -= CPS;

		cnt = read(rfd, buf, BUFSIZE);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			fprintf(stderr, "read() failed\n");
			return -1;
		}
		pos = 0;
		while (1) {
			ret = write(wfd, buf+pos, cnt);
			if (ret == -1) {
				if (errno == EINTR) 
					continue;
				perror("write()");
				return -1;
			}
			if (cnt > ret) {
				cnt -= ret;
				pos += ret;
			} else 
				break;
		}
	}

	return 0;
}


