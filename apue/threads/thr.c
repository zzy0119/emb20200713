#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t tid;
static void *thrs(void *arg)
{
	pthread_t mytid;

	mytid = pthread_self();
	printf("%d\n", pthread_equal(mytid, tid));

	for (int i = 0; i < 5; i++) {
		write(1, "*", 1);
		sleep(1);
	}
	// return NULL;
	pthread_exit((void *)0);
}

int main(void)
{
	int err;
	pthread_attr_t attr;

#if 0
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
#endif

	err = pthread_create(&tid, NULL, thrs, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	pthread_detach(tid);

	// 收尸
	err = pthread_join(tid, NULL);
	if (err) {
		fprintf(stderr, "pthread_join():%s\n", strerror(err));
		exit(1);
	}

	for (int i = 0; i < 10; i ++) {
		write(1, "!", 1);
		sleep(1);
	}

	exit(0);
}

