#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static void handler1(void *s)
{
	printf("%s is called\n", __FUNCTION__);
}

static void handler2(void *s)
{
	printf("%s is called\n", __FUNCTION__);
}

static void *thr_fun(void *s)
{
	pthread_cleanup_push(handler1, NULL);	
	pthread_cleanup_push(handler2, NULL);	

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	pthread_exit(NULL);

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

int main(void)
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, thr_fun, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	sleep(3);
	pthread_cancel(tid);

	pthread_join(tid, NULL);

	exit(0);
}

