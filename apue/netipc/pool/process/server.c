#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

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
 创建任务池
 */
int pool_init(pool_t *pool, int num)
{
	int i;
	if (pool == NULL || num <= 0)
		return -1;
	pool->pro_nr = num;
	pool->cur_index = 0;
	pool->proc = calloc(pool->nr, sizeof(struct process_st));
	if (NULL == pool->proc)
		return -1;
	for (i = 0; i < pool->nr; i++) {
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
			struct data_st task;
			int cnt;
			// 子进程--->读管道任务
			close((pool->proc)[i].pfd[1]);
#if 0
			while (1){
				cnt = read((pool->proc)[i].pfd[0], &task, sizeof(task));
				if (cnt == -1) {
					if (errno == EINTR)
						continue;
					perror("read()");
					close((pool->proc)[i].pfd[0]);
					goto ERROR1;
				}
				printf("get task, msg:%s\n", task.msg);
				wrtie(task.connect_sd, "ok", 2);
			}
#endif
			woker_job(pool);
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

	pool_init(&p);


	exit(0);
}

