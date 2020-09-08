#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "tbf.h"

typedef struct {
	int cps;
	int token;
	int burst;
}tbf_t;

typedef void (*sighandler_t)(int);

static tbf_t *jobs[TBF_MAXSIZE] = {};
static int flag = 0;
sighandler_t alrm_save;

static void alrm_handler(int s)
{
	alarm(1);

	for (int i = 0; i < TBF_MAXSIZE; i++) {
		if (jobs[i] != NULL) {
			jobs[i]->token += jobs[i]->cps;
			if (jobs[i]->token >= jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}
	
}

// 管理令牌桶库
static void moduler_load(void)
{
	alrm_save = signal(SIGALRM, alrm_handler);
	alarm(1);
}

static void moduler_unload(void)
{
	signal(SIGALRM, alrm_save);	
	alarm(0);
}

static int get_free_pos(void)
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
	if (flag == 0) {
		moduler_load();
		flag = 1;
	}

	t = malloc(sizeof(tbf_t));
	if (NULL == t)
		return -1;
	t->cps = cps;
	t->burst = burst;
	t->token = 0;

	pos = get_free_pos();
	if (pos == -1) {
		free(t);
		return -1;
	}
	jobs[pos] = t;

	return pos;
}

int tbf_fetch(int td, int token)
{
	int fetch = 0;

	if (td < 0 || token <= 0)
		return -1;
	while (jobs[td]->token <= 0)
		pause();
	if (jobs[td]->token < token) {
		fetch = jobs[td]->token;	
	} else {
		fetch = token;
	}
	jobs[td]->token -= fetch;

	return fetch;
}

int tbf_return(int td, int token)
{
	if (td < 0 || token <= 0)
		return -1;
	jobs[td]->token += token;
	if (jobs[td]->token >= jobs[td]->burst)
		jobs[td]->token = jobs[td]->burst;
	
	return 0;
}

void tbf_destroy(int td)
{
	free(jobs[td]);
	jobs[td] = NULL;
}

void tbf_destroy_all(void)
{
	moduler_unload();	
	for (int i = 0; i < TBF_MAXSIZE; i++) {
		if (jobs[i] != NULL) {
			free(jobs[i]);
			jobs[i] = NULL;
		}
	}
}

