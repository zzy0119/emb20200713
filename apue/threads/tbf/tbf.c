#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "tbf.h"

typedef struct {
	int cps;
	int token;
	int burst;
	pthread_mutex_t token_mut; // 存取令牌的线程同步
	pthread_cond_t token_cond;
}tbf_t;

typedef void (*sighandler_t)(int);

static tbf_t *jobs[TBF_MAXSIZE] = {};
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // 保证多线程使用jobs数组同步
static pthread_t tbf_tid;
static pthread_once_t once_control = PTHREAD_ONCE_INIT;

static void *thr_handler(void *s)
{
	while (1) {
		pthread_mutex_lock(&mut);
		for (int i = 0; i < TBF_MAXSIZE; i++) {
			if (jobs[i] != NULL) {
				pthread_mutex_lock(&jobs[i]->token_mut);
				jobs[i]->token += jobs[i]->cps;
				if (jobs[i]->token >= jobs[i]->burst)
					jobs[i]->token = jobs[i]->burst;
				pthread_cond_broadcast(&jobs[i]->token_cond);
				pthread_mutex_unlock(&jobs[i]->token_mut);
			}
		}
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	
}

// 管理令牌桶库
static void moduler_load(void)
{
	int err;
	// 创建流量控制的线程
	err = pthread_create(&tbf_tid, NULL, thr_handler, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}
}

static void moduler_unload(void)
{
	pthread_cancel(tbf_tid);
	pthread_join(tbf_tid, NULL);
}

static int get_free_pos_unlocked(void)
{
	for (int i = 0; i < TBF_MAXSIZE; i++)
		if (jobs[i] == NULL)
			return i;
	return -1;
}

int tbf_init(int cps, int burst)
{
	tbf_t *t;
	int pos;
	
	// 第一个令牌桶构建 加载管理令牌桶库的模块
	pthread_once(&once_control, moduler_load);

	t = malloc(sizeof(tbf_t));
	if (NULL == t)
		return -1;
	t->cps = cps;
	t->burst = burst;
	t->token = 0;

	pthread_mutex_lock(&mut);
	pos = get_free_pos_unlocked();
	if (pos == -1) {
		free(t);
		return -1;
	}
	jobs[pos] = t;
	pthread_mutex_unlock(&mut);

	return pos;
}

int tbf_fetch(int td, int token)
{
	int fetch = 0;

	if (td < 0 || token <= 0)
		return -1;
	pthread_mutex_lock(&jobs[td]->token_mut);
	while (jobs[td]->token <= 0)
		pthread_cond_wait(&jobs[td]->token_cond, &jobs[td]->token_mut);
	if (jobs[td]->token < token) {
		fetch = jobs[td]->token;	
	} else {
		fetch = token;
	}
	jobs[td]->token -= fetch;
	pthread_mutex_unlock(&jobs[td]->token_mut);

	return fetch;
}

int tbf_return(int td, int token)
{
	if (td < 0 || token <= 0)
		return -1;
	pthread_mutex_lock(&jobs[td]->token_mut);
	jobs[td]->token += token;
	if (jobs[td]->token >= jobs[td]->burst)
		jobs[td]->token = jobs[td]->burst;
	pthread_cond_broadcast(&jobs[td]->token_cond);
	pthread_mutex_unlock(&jobs[td]->token_mut);
	
	return 0;
}

void tbf_destroy(int td)
{
	pthread_mutex_lock(&mut);
	pthread_mutex_destroy(&jobs[td]->token_mut);
	pthread_cond_destroy(&jobs[td]->token_cond);
	free(jobs[td]);
	jobs[td] = NULL;
	pthread_mutex_unlock(&mut);
}

void tbf_destroy_all(void)
{
	moduler_unload();	
	pthread_mutex_lock(&mut);
	for (int i = 0; i < TBF_MAXSIZE; i++) {
		if (jobs[i] != NULL) {
			free(jobs[i]);
			jobs[i] = NULL;
		}
	}
	pthread_mutex_unlock(&mut);
}

