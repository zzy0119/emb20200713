#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include "proto.h"

int main(void)
{
	key_t key;
	int msgid;
	struct msgbuf rcvbuf;

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

	// 读
	while (1) {
		if (msgrcv(msgid, &rcvbuf, MSGSIZE, 0, 0) == -1) {
			perror("msgrcv()");
			exit(1);
		}
		if (strcmp(rcvbuf.msg, "exit") == 0)
			break;
		puts(rcvbuf.msg);	
	}

	// 销毁
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}


