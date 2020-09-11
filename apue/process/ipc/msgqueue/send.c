#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include "proto.h"

int main(int argc, char *argv[])
{
	key_t key;
	int msgid;
	struct msgbuf sndbuf;

	if (argc < 3)
		exit(1);

	// 得到数据交换的消息队列
	key = ftok(PATHNAME, PRO_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
	if (msgid == -1) {
		if (errno == EEXIST) {
			msgid = msgget(key, 0);
		} else {
			perror("msgget()");
			exit(1);
		}
	}

	sndbuf.mtype = atoi(argv[1]);
	strncpy(sndbuf.msg, argv[2], MSGSIZE);
	msgsnd(msgid, &sndbuf, strlen(argv[2])+1, 0);

	return 0;
}


