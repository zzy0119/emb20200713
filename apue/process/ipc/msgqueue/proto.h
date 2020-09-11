#ifndef __PROT_H
#define __PROT_H

#define PATHNAME	"/etc/passwd"
#define PRO_ID		1

#define MSGSIZE		1024

struct msgbuf {
	long mtype;	
	char msg[MSGSIZE];
};

#endif
