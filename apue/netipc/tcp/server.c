#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in local_addr, remote_addr;
	socklen_t len;
	int newsd;
	struct msg_st rcvbuf;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	local_addr.sin_family = AF_INET;
	inet_aton(SERVERIP, &local_addr.sin_addr);
	local_addr.sin_port = htons(SERVERPORT);
	if (bind(sd, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	if (listen(sd, 20) == -1) {
		perror("listen()");
		goto ERROR;
	}

	len = sizeof(remote_addr);

	while (1) {
		newsd = accept(sd, (struct sockaddr *)&remote_addr, &len);
		if (newsd == -1) {
			if (errno == EINTR)	{
				continue;
			}
			perror("accept()");
			goto ERROR;
		}

		recv(newsd, &rcvbuf, sizeof(&rcvbuf), 0);
		printf("from ip:%s, port:%d, msg id:%d, name:%s\n", \
				inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), \
				rcvbuf.id, rcvbuf.name);
		close(newsd);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

