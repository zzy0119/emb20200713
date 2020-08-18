#ifndef __MYLIST_H
#define __MYLIST_H

// 抽象数据类型
// 数据结点类型
struct node_st {
	void *data;// 存储数据域地址
	struct node_st *next;// 后继结点地址
};
// 头结点类型
typedef struct {
	struct node_st head; // head.data不需要，head.next存储的第一个结点地址
	int size;// 存储数据结点所存储的数据大小
}lhead_t;

// 枚举
typedef enum {
	HEAD,
	TAIL
}way_t;

typedef int (*cmp_t)(const void *key, const void *data);
typedef void (*pri_t)(const void *data);

// 声明接口函数
/*
 初始化头结点
 */
lhead_t *lhead_init(int size);
//int lhead_init(int size, lhead_t **h);

/*
 插入
 */
int lhead_insert(lhead_t *h, const void *data, way_t way);

/*
 删除
 */
int lhead_delete(lhead_t *h, const void *key, cmp_t cmp);

/*
 遍历
 */
void lhead_traval(const lhead_t *h, pri_t pri);

/*
 销毁 
 */
void lhead_destroy(lhead_t *h);

#endif

