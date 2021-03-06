#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>

// 注册
#define RGS_SERVER_IP   "192.168.1.211"
#define RGS_SERVER_PORT 1111
#define CNT_SIZE        32
#define PWD_SIZE        128

enum {
    RGS_OK,
    RGS_ALREADY_EXISTS
};

struct rgs_st {
    char cnt[CNT_SIZE];
    char pwd[PWD_SIZE];
    int8_t rgsState;
}__attribute__((packed));


// 登陆
#define LOGIN_SERVER_IP     "192.168.1.211"
#define LOGIN_SERVER_PORT   1112

enum {
    LOGIN_OK,
    LOGIN_NOTEXITS_CNT,
    LOGIN_ERROR_PWD
};

struct login_st {
    char cnt[CNT_SIZE];
    char pwd[PWD_SIZE];
    int8_t loginState;
}__attribute__((packed));

#endif // PROTO_H
