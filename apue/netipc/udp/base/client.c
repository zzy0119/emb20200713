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


int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in raddr;
	socklen_t raddr_len;

	if (argc < 2)
		exit(1);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	raddr.sin_family = AF_INET;
	inet_aton(SERVERIP, &raddr.sin_addr);
	raddr.sin_port = htons(SERVERPORT);
	sendto(sd, argv[1], strlen(argv[1])+1, 0, (struct sockaddr *)&raddr, sizeof(raddr));

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

