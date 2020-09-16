#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "proto.h"

#define BUFSIZE	MSGSIZE

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	char buf[BUFSIZE] = {};
	socklen_t raddr_len;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &laddr.sin_addr);
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	raddr_len = sizeof(raddr);
	while (1) {
		if (recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&raddr, &raddr_len) == -1) {
			perror("recvfrom()");
			goto ERROR;
		}
		printf("recv msg from ip:%s, port:%d, msg:%s\n", \
				inet_ntoa(raddr.sin_addr), ntohs(raddr.sin_port), buf);
		if (strcmp(buf, "bye") == 0)
			break;
	}
	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

