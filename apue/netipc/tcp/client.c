#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in server_addr;
	struct msg_st sndbuf;
	int cnt;

	if (argc < 3)
		exit(1);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	inet_aton(SERVERIP, &server_addr.sin_addr);
	server_addr.sin_port = htons(SERVERPORT);
	if (connect(sd, (void *)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect()");
		goto ERROR;
	}

	sndbuf.id = atoi(argv[1]);
	strncpy(sndbuf.name, argv[2], NAMESIZE);
	cnt = send(sd, &sndbuf, sizeof(sndbuf), 0);
	if (cnt == -1) {
		perror("send()");
		goto ERROR;
	}
	printf("send %d bytes\n", cnt);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

