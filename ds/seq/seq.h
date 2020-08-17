// 函数的声明 类型的定义
// 条件编译
#ifndef __SEQ_H
#define __SEQ_H

// 线性表---》存储任意类型的数值
typedef struct {
	void *ptr;// 存储结构的首地址
	int nmemb;// 存储结构中当前有的元素个数
	int size;// 存储每个元素的字节个数
}seq_t;

// 用于比较的函数指针类型
typedef int (*cmp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

// 创建表结构
/*
size:用户所要存储的数据每个元素的字节个数
s:存储用户用于存放表结构首地址的变量的地址
 */
int seq_init(int size, seq_t **s);

/*
 增加新的元素
s:表结构的地址
data:待插入的元素的地址
return:成功0 失败-1
 */
int seq_add(seq_t *s, const void *data);

/*
删除指定元素 
s:表结构的首地址
key:要删除元素关键字的地址
cmp:存储用户提供的比较函数的地址
 */
int seq_del(seq_t *s, const void *key, cmp_t cmp);

/*
 遍历
s:表结构的地址
pri:根据地址能够打印元素的函数的地址
 */
void seq_traval(const seq_t *s, pri_t pri);

#endif

