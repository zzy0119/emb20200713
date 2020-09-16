#include <stdio.h>
#include <arpa/inet.h>
#include <net/if.h>
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
	struct sockaddr_in raddr;
	int val;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// 使能广播选项
	val = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	raddr.sin_family = AF_INET;
	inet_aton("192.168.1.255", &raddr.sin_addr);
	raddr.sin_port = htons(RCVPORT);
	while (1) {
		if (sendto(sd, "hello", 6, 0, (struct sockaddr *)&raddr, sizeof(raddr)) == -1) {
			perror("sendto()");
			goto ERROR;
		}
		sleep(1);
	}
	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

