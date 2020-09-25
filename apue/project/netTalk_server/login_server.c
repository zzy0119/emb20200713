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
#include <sqlite3.h>

#include "proto.h"

#define __DEBUG
#define BUFSIZE	1024

int socket_init(const char *ip, short port, int *sd);
int is_login_ok(struct login_st rcvbuf);
int main(void)
{
	struct sockaddr_in client_addr;
	socklen_t client_addrlen;
	int sd;
	int err, cnt, ret;
	struct login_st rcvbuf;
	struct sigaction act;
	pid_t pid;
	sqlite3 *db;
	const char *sqlp;
	char *errmsg = NULL;

	// 子进程终止时不会成为僵尸进程
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	// 初始化套接字
	err = socket_init(LOGIN_SERVER_IP, LOGIN_SERVER_PORT, &sd);
	if (err) {
		fprintf(stderr, "socket_init():%s\n", strerror(err));
		exit(1);
	}

	// 等待接受客户端登录请求
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
			// 判断能否登录---》发送客户端
			ret = is_login_ok(rcvbuf);	
			if (ret == 0) {
				rcvbuf.loginState = LOGIN_OK;
			} else if (ret == 1) {
				rcvbuf.loginState = LOGIN_NOTEXITS_CNT;
			} else if (ret == 2) {
				rcvbuf.loginState = LOGIN_ERROR_PWD;
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

int is_login_ok(struct login_st rcvbuf)
{
	sqlite3 *db;
	int ret;
	sqlite3_stmt *stmt = NULL;
	char *sql;
	char buf[BUFSIZE] = {};
	const char *sqlpwd;
	int retvalue = 0;

	// 打开数据库 查注册表中是否有rcvbuf.cnt账号
	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_open() failed\n");
		exit(0);
	}
	sql = "select * from rgsTables where count=?";
	sqlite3_prepare(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, rcvbuf.cnt, -1, NULL);
	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ERROR) {
		fprintf(stderr, "sqlite3_step() error\n");
		goto ERROR;
	}
	if (ret == SQLITE_ROW) {
		// 有 密码是否正确
		sqlpwd = sqlite3_column_text(stmt, 1);
		if (strcmp(sqlpwd, rcvbuf.pwd) == 0) {
			// 密码正确
			retvalue = 0;
		} else {
			retvalue = 2;
		}

	} else {
	// 没有  返回1
		retvalue = 1;
	}	
	sqlite3_finalize(stmt); // 释放stmt结构
	sqlite3_close(db);
	return retvalue;
ERROR:
	sqlite3_finalize(stmt); // 释放stmt结构
	sqlite3_close(db);
	return -1;
}

