#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "tbf.h"

#define CPS		10
#define BUFSIZE	CPS
#define BURST	10*(CPS)

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

int copy_file(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt, ret, pos;
	int mytd;	

	mytd = tbf_init(CPS, BURST);
	if (mytd == -1) {
		fprintf(stderr, "tbf_init() failed\n");
		return -1;
	}

	while (1) {
		// 流量控制
		ret = tbf_fetch(mytd, CPS);
		if (ret == -1) {
			fprintf(stderr, "tbf_fetch() failed\n");
			return -1;
		}
		printf("fetch %d tokens\n", ret);

		cnt = read(rfd, buf, ret);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			fprintf(stderr, "read() failed\n");
			return -1;
		}
		if (cnt < ret) {
			// 取到的token没有完全消耗
			tbf_return(mytd, cnt-ret);
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

	tbf_destroy(mytd);

	return 0;
}


