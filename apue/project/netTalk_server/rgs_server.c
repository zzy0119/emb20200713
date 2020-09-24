#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"

#define __DEBUG

int socket_init(const char *ip, short port, int *sd);
int is_rgs_ok();
int main(void)
{
	struct sockaddr_in client_addr;
	socklen_t client_addrlen;
	int sd;
	int err, cnt, ret;
	struct rgs_st rcvbuf;
	struct sigaction act;
	pid_t pid;

	// 子进程终止时不会成为僵尸进程
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	// 初始化套接字
	err = socket_init(RGS_SERVER_IP, RGS_SERVER_PORT, &sd);
	if (err) {
		fprintf(stderr, "socket_init():%s\n", strerror(err));
		exit(1);
	}

	// 等待接受客户端注册请求
	client_addrlen = sizeof(client_addr);
	while (1) {
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&client_addr, &client_addrlen);
		if (cnt == -1) {
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
#ifdef __DEBUG
		printf("rcv cnt:%s, pwd:%s\n", rcvbuf.cnt, rcvbuf.pwd);
#endif

		pid = fork();
		if (pid == -1) {
			perror("fork()");
			close(sd);
			exit(1);
		}
		if (pid == 0) {
			// 判断能否注册---》发送客户端
			ret = is_rgs_ok();	
			if (ret == 0) {
				rcvbuf.rgsState = RGS_OK;
			} else if (ret == 1) {
				rcvbuf.rgsState = RGS_ALREADY_EXISTS;
			}
			sendto(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&client_addr, client_addrlen);
			exit(0);
		}
	}



	return 0;
}

// 
int socket_init(const char *ip, short port, int *sd)
{
	struct sockaddr_in server_addr;

	*sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (*sd == -1) {
		return errno;
	}
	server_addr.sin_family = AF_INET;
	inet_aton(ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	if (bind(*sd, (void *)&server_addr, sizeof(server_addr)) == -1) {
		close(*sd);
		return errno;
	}

	return 0;	
}

int is_rgs_ok()
{
	return 0;
}

