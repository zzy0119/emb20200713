#ifndef __LLIST_H
#define __LLIST_H

/*
 抽象数据类型
 */
struct node_st {
	void *data;
	struct node_st *prev;
	struct node_st *next;
};

// 头结点
typedef struct {
	struct node_st head;
	int size;
}llisthead_t;

typedef enum {
	INSERT_HEAD,
	INSERT_TAIL
}insert_way_t;

typedef int cmp_t(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

// 接口
/*
 初始化头结点
 */
int llisthead_init(int size, llisthead_t **h);

/*
 插入
 */ 
int llist_insert(llisthead_t *h, const void *data, insert_way_t way);

/*
 删除
 */
int llist_delete(llisthead_t *h, const void *key, cmp_t *cmp);

/*
 遍历
 */
void llist_traval(const llisthead_t *h, pri_t pri);

/*
 销毁
 */
void llist_destroy(llisthead_t *h);

/*
 返回第一个结点数据  
 */
void *llist_pop(const llisthead_t *h);

/*
 返回最后一个结点数据 
 */
void *llist_last(const llisthead_t *h);

/*
 返回链表的结点个数
 */
int llist_all_membs(const llisthead_t *h);

/*
 返回给定结点的数据(通过参数回填数据)并将其删除
 */
int llist_fetch(llisthead_t *h, const void *key, cmp_t *cmp, void *data);

#endif

