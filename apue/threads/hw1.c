#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define THRNR	5

static int curid = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_job(void *s)
{
	int myid = (int)s;

	while (1) {
		pthread_mutex_lock(&mut);		
		while (curid != myid) {
			pthread_cond_wait(&cond, &mut);
		}
		printf("%c", 'a'+myid);
		fflush(NULL);
		curid = -1;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}	
}


int main(void)
{
	pthread_t tids[THRNR];
	int err;

	alarm(5);

	for (int i = 0; i < THRNR; i++) {
		if ((err = pthread_create(tids+i, NULL, thr_job, (void *)i))) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; ; i = (i + 1) % THRNR) {
		pthread_mutex_lock(&mut);
		while (curid >= 0) {
			pthread_cond_wait(&cond, &mut);
		}
		curid = i;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}


	exit(0);
}

