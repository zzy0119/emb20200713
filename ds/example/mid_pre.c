#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack.h>

char *mid_to_pre(const char *p);
int main(int argc, char **argv)
{
	char *res;

	if (argc < 2)
		return 1;

	res =mid_to_pre(argv[1]);
	if (res == NULL)
		return 1;
	puts(res);

	free(res);

	return 0;
}

static int asscosi_value(char ch1)
{
	int val;
	if (ch1 == '+' || ch1 == '-')
		val = 1;
	else if (ch1 == '*' || ch1 == '/')
		val = 2;

	return val;
}


/*
   将给定中缀表达式转换为前缀表达式返回
 */
char *mid_to_pre(const char *p)
{
	stack_t *res, *op;
	int len, i;
	char elm;
	int have_r = 0; // 标记是否有右括号
	char *resStr = NULL;

	len = strlen(p);
	res = stack_init(sizeof(char), len); 
	op = stack_init(sizeof(char), len);
	// if error

	i = len - 1;
	while ( i >= 0) {
		if (p[i] >= '0' && p[i] <= '9') {
			push(res, p+i);
		} else if (p[i] == ')') {
			push(op, p+i);	
		} else if (p[i] == '(') {
			while (!empty(op)) {
				pop(op, &elm);	
				if (elm != ')') {
					push(res, &elm);
				} else {
					have_r = 1;
					break;
				}
			}	
			if (!have_r) {
				// 只有左括号却没有右括号---》表达式出错
				goto ERROR;
			}
			have_r = 0;
		} else {
			// 运算符--->"+-*/"
			while (1) {
				if (empty(op)) {
					push(op, p+i);
					break;
				} else {
					pop(op, &elm);
					if (elm == ')') {
						push(op, &elm);
						push(op, p+i);
						break;
					} else {
						// 比较运算符优先级
						if (asscosi_value(p[i]) >= asscosi_value(elm)) {
							push(op, &elm);
							push(op, p+i);
							break;
						} else {
							push(res, &elm);
						}
					}
				}
			}
		}

		i--;
	}

	// 所有运算符栈中的运算符出栈入结果栈
	while (!empty(op)) {
		pop(op, &elm);
		push(res, &elm);
	}

	resStr = calloc(1, 1); // '\0'
	len = 1; // 结果字节个数
	i = 0;
	while (!empty(res)) {
		pop(res, &elm);	
		resStr = realloc(resStr, len+1);
		resStr[i++] = elm;
		len ++;
	}
	destroy(res);
	destroy(op);
	return resStr;

ERROR:
	destroy(res);
	destroy(op);
	return NULL;
}

