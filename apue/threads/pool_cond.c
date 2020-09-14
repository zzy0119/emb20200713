#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>

#define START	100
#define END		300
#define THRNR	3

// 多线程竞争的变量
static int job = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // 多线程存取job时候同步
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_jobs(void *s);

static int is_primer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;

	return 1;
}


int main(void)
{
	// 创建任务线程 发放任务
	pthread_t tid[THRNR];
	int err;

	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tid+i, NULL, thr_jobs, NULL);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = START; i <= END; i++) {
		pthread_mutex_lock(&mut);
		while (job != 0) {
			// 上一次发放的任务还未取走
			pthread_cond_wait(&cond, &mut);
		}
		job = i;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}
	// 所有任务发放完成
	pthread_mutex_lock(&mut);
	while (job > 0) {
		// 最后一个任务未被取走
		pthread_cond_wait(&cond, &mut);
	}
	job = -1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	// 收尸
	for (int i = 0; i < THRNR; i++) {
		pthread_join(tid[i], NULL);	
	}

	pthread_mutex_destroy(&mut);

	exit(0);
}

// 任务线程 执行的函数
static void *thr_jobs(void *s)
{
	int myjob;

	while (1) {
		pthread_mutex_lock(&mut);
		while (job == 0) {
			// 未方放
			pthread_cond_wait(&cond, &mut);
		}
		if (job == -1) {
			pthread_mutex_unlock(&mut);
			break;
		}
		// 去任务
		myjob = job;
		job = 0;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mut);
		if (is_primer(myjob))
			printf("%d is a primer\n", myjob);
	}

	pthread_exit((void *)0);
}





