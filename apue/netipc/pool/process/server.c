#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "proto.h"

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

}

int main(void)
{
	pool_t p;

	pool_init(&p);


	exit(0);
}

