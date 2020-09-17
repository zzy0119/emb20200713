#ifndef __TCP_PROTO_H
#define __TCP_PROTO_H

#define SERVERIP	"192.168.1.211"
#define SERVERPORT	3344

#define NAMESIZE	32

struct msg_st {
	int8_t id;
	char name[NAMESIZE];
}__attribute__((packed));

#endif

