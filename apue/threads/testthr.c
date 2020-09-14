#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define START	100
#define END		300
#define THRNR	(END)-(START)+1

static int is_primer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;

	return 1;
}

static void *thr_job(void *n)
{
	//sleep(1);
	int num = (int)n;
	// printf("num:%d\n", num);

	if (is_primer(num))	{
		printf("%d is a primer\n", num);
	}
	
	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tid[THRNR] = {};	
	int j = 0;
	int err;

	for (int i = START; i <= END; i++, j++) {
		err = pthread_create(tid+j, NULL, thr_job, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; i < THRNR; i++)
		pthread_join(tid[i], NULL);

	exit(0);
}








