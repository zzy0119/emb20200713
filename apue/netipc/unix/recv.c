#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>

#include "proto.h"

int main(void)
{
	int sd, newsd;
	struct sockaddr_un un;
	char buf[MSGMAX] = {};

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}
	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, SUNPATH, 108);
	if (bind(sd, (struct sockaddr *)&un, offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path) + 1) == -1) {
		perror("bind()");
		goto ERROR;
	}
	listen(sd, 2);

	newsd = accept(sd, NULL, NULL);
	if (newsd == -1) {
		perror("accept()");
		goto ERROR;
	}
	printf("newsd:%d\n", newsd);
	read(newsd, buf, MSGMAX);
	puts(buf);
	close(newsd);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

