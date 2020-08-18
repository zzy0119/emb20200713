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
}list_t;

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
list_t *list_init(int size);
//int list_init(int size, list_t **h);

/*
 插入
 */
int list_insert(list_t *h, const void *data, way_t way);

/*
 删除
 */
int list_delete(list_t *h, const void *key, cmp_t cmp);

/*
 遍历
 */
void list_traval(const list_t *h, pri_t pri);

/*
 销毁 
 */
void list_destroy(list_t *h);

/*
 修改
 */
int list_update(list_t *h, const void *key, cmp_t cmp, const void *newdata);

/*
 返回第一个结点的数据
 */
void *list_firstnode(const list_t *h);
/*
 最后一个结点的数据
 */
void *list_lastnode(const list_t *h);

/*
 转置
 */
void list_reverse(list_t *h);

#endif

