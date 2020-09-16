#include <stdio.h>
#include <stdio.h>
#include <net/if.h>
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

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in laddr;
	char buf[BUFSIZE] = {};

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	inet_aton("0.0.0.0", &laddr.sin_addr);
	laddr.sin_port = htons(RCVPORT);
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	if (recvfrom(sd, buf, BUFSIZE, 0, NULL, NULL) == -1) {
		perror("rcvfrom()");
		goto ERROR;
	}
	puts(buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

