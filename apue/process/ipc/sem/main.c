#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TMPFILE	"/tmp/out"
#define PRO_NR	20
#define BUFSIZE	20

static int semid;

static void P(void)
{
	struct sembuf op;

	op.sem_num = 0; // 指定集合中的第几个元素
	op.sem_op = -1;
	op.sem_flg = 0;
	if (semop(semid, &op, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

static void V(void)
{
	struct sembuf op;

	op.sem_num = 0; // 指定集合中的第几个元素
	op.sem_op = 1;
	op.sem_flg = 0;
	if (semop(semid, &op, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

static int fileop(void)
{
	FILE *fp;
	char buf[BUFSIZE] = {};

	fp = fopen(TMPFILE, "r+");
	// if error
	P();
	fgets(buf, BUFSIZE, fp);
	rewind(fp);
	sleep(1);
	fprintf(fp, "%d", atoi(buf)+1);
	fclose(fp);
	V();

	return 0;
}

int main(void)
{
	int fd;
	pid_t pid;

	fd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1) {
		perror("open()");
		exit(1);
	}
	write(fd, "0", 1);
	close(fd);

	// 创建信号量集合 ---》一个元素
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1) {
		perror("semget()");
		exit(1);
	}
	// 初始化信号
	semctl(semid, 0, SETVAL, 1);
	
	for (int i = 0; i < PRO_NR; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			fileop();
			exit(0);
		}
	}

	for (int i = 0; i < PRO_NR; i++)
		wait(NULL);

	exit(0);
}

