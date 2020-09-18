#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"

// 发放任务的数据类型
struct data_st {
	int connect_sd;
	char msg[MAXMSG];
};

// 任务进程类型
struct process_st {
	pid_t pid;
	int pfd[2];
};

// 任务池类型
typedef struct {
	struct process_st *proc;
	int pro_nr; // 进程池中的子进程个数
	int cur_index; // 当前要分配给哪一个任务子进程的索引
}pool_t;

/*
 任务子进程取任务
 */
static int worker_job(pool_t *pool)
{
	struct data_st task;
	int cnt;

	int i = pool->cur_index;

	while (1){
		cnt = read((pool->proc)[i].pfd[0], &task, sizeof(task));
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("read()");
			close((pool->proc)[i].pfd[0]);
			return -1;
		}
		printf("[%d]get task, msg:%s\n", getpid(), task.msg);
		sleep(10);
		write(task.connect_sd, "ok", 2);
		close(task.connect_sd);
	}

}

/*
 任务的分配
 */
static int manager_job(pool_t *pool)
{
	int sd, newsd;
	struct sockaddr_in myaddr;
	char buf[MAXMSG] = {};
	int cnt;
	struct data_st task;
	int i = 0;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return -1;
	}
	myaddr.sin_family = AF_INET;
	inet_aton(SERVERIP, &myaddr.sin_addr);
	myaddr.sin_port = htons(SERVERPORT);
	if (bind(sd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
		perror("bind()");
		close(sd);
		return -1;
	}
	if (listen(sd, 20) == -1) {
		perror("listen()");
		close(sd);
		return -1;
	}
	while (1) {
		newsd = accept(sd, NULL, NULL);	
		if (newsd == -1) {
			if (errno == EINTR)
				continue;
			perror("accept()");
			close(sd);
			return -1;
		}
		cnt = read(newsd, buf, MAXMSG);
		if (cnt == -1) {
			perror("read()");
			continue;
		}
		task.connect_sd = newsd;
		strncpy(task.msg, buf, cnt);
		// 写入对应管道
		write((pool->proc)[i].pfd[1], &task, sizeof(task));	
		i = (i+1) % pool->pro_nr;
	}

}

/*
 创建任务池
 */
int pool_init(pool_t *pool, int num)
{
	int i;
	if (pool == NULL || num <= 0)
		return -1;
	pool->pro_nr = num;
	pool->cur_index = 0;
	pool->proc = calloc(pool->pro_nr, sizeof(struct process_st));
	if (NULL == pool->proc)
		return -1;
	for (i = 0; i < pool->pro_nr; i++) {
		if (pipe((pool->proc)[i].pfd) == -1) {
			perror("pipe()");
			goto ERROR1;
		}
		(pool->proc)[i].pid = fork();
		if ((pool->proc)[i].pid == -1) {
			perror("fork()");
			goto ERROR2;
		}
		if ((pool->proc)[i].pid == 0) {
			// 子进程--->读管道任务
			close((pool->proc)[i].pfd[1]);
			pool->cur_index = i;
			worker_job(pool);
			exit(0);
		} else {
			// 调用进程
			close((pool->proc)[i].pfd[0]);
		}
	}

	// 所有所需的任务子进程创建完成
	// 发放任务
	manager_job(pool);

ERROR2:
	close((pool->proc)[i].pfd[0]);
	close((pool->proc)[i].pfd[1]);
ERROR1:
	free(pool->proc);
	return -1;
}

int main(void)
{
	pool_t p;

	pool_init(&p, 3);

	exit(0);
}

