#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *ptr = NULL;

	if (argc < 2)
		exit(1);

	key = ftok(PATHNAME, PRO_ID);
	// if error

	shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0600);
	if (shmid == -1) {
		if (errno == EEXIST)
			shmid = shmget(key, 1024, 0);
		else {
			perror("shmget()");
			exit(1);
		}
	}
	// 挂载
	ptr = shmat(shmid, NULL, 0);
	strcpy(ptr, "good night");
	shmdt(ptr);
	
	exit(0);
}



