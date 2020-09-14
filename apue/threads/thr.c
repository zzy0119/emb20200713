#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static void *thrs(void *arg)
{
	for (int i = 0; i < 5; i++) {
		write(1, "*", 1);
		sleep(1);
	}
	return NULL;
}

int main(void)
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, thrs, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	for (int i = 0; i < 10; i ++) {
		write(1, "!", 1);
		sleep(1);
	}

	exit(0);
}

