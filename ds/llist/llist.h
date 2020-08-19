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

#endif

