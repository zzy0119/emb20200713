#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define TMPFILE	"/tmp/out"
#define THRNR	20
#define BUFSIZE	20

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *thr_job(void *s)
{
	FILE *fp;
	char buf[BUFSIZE] = {};

	fp = fopen(TMPFILE, "r+");
	// if error;
	pthread_mutex_lock(&mut);
	fgets(buf, BUFSIZE, fp);	
	rewind(fp);
	fprintf(fp, "%d", atoi(buf)+1);
	fflush(NULL);
	pthread_mutex_unlock(&mut);
	fclose(fp);

	pthread_exit(NULL);
}

int main(void)
{
	FILE *fp;
	pthread_t tids[THRNR] = {};

	fp = fopen(TMPFILE, "w");
	// if error
	fputs("0", fp);
	fclose(fp);

	for (int i = 0; i < THRNR; i++) {
		pthread_create(tids+i, NULL, thr_job, NULL);
		// if error
	}

	for (int i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	exit(0);
}

