#ifndef __TBF_H
#define __TBF_H

#define TBF_MAXSIZE	1024

// 接口
/*
 cps 速率
 burst 上限
return:桶描述符 标志所创建的令牌桶
 */
int tbf_init(int cps, int burst);

/*
 取令牌
td:令牌桶的标识
token:所要取得的令牌的个数
 */
int tbf_fetch(int td, int token);

/*
 归还为消耗的令牌
td:令牌桶的标示
token:所还的令牌个数
 */
int tbf_return(int td, int token);

void tbf_destroy(int td);

void tbf_destroy_all(void);

#endif

