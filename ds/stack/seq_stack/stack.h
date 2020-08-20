#ifndef __STACK_H
#define __STACK_H

/*ADT*/
typedef struct {
	void *base;// 栈的首地址
	void *top;// 栈顶地址
	int size;// 数据字节个数
	int nmembs;// 容量
}stack_t;

/*接口*/
// 初始化栈
stack_t *stack_init(int size, int nmembs);

// 栈是否空
int empty(const stack_t *s);

// 栈是否满
int full(const stack_t *s);

// 入栈
int push(stack_t *s, const void *data);

// 出栈
int pop(stack_t *s, void *data);

// 销毁
void destroy(stack_t *s);

#endif

