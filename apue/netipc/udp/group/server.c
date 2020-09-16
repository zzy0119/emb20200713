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
	struct ip_mreqn imr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// 使能多播选项
	inet_aton(GROUPADDR, &imr.imr_multiaddr);
	imr.imr_address.s_addr	= INADDR_ANY;
	imr.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &imr, sizeof(imr)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	raddr.sin_family = AF_INET;
	inet_aton(GROUPADDR, &raddr.sin_addr);
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

