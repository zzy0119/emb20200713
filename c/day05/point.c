#include <stdio.h>

void swap2num(int *m, int *n);
int maxmin_num(int a, int b, int c, int *min);
int main(void)
{
	int n = 10;
	// 初始化
	int *p = &n; // int *
	// 定义
	int *q;
	int a = 10, b = 200;
	int c = 9;
	int max, min;

	// 赋值
	q = &n;
	
	// 取值
	printf("%d\n", *p);

	swap2num(&a, &b);
	printf("a:%d, b:%d\n", a, b);

	max = maxmin_num(a, b, c, &min);
	printf("最大值:%d, 最小值:%d\n", max, min);

	return 0;
}

/*
 通过指针可以形参改变实参
 */
void swap2num(int *m, int *n)
{
	int t;
	
	t = *m;
	*m = *n;
	*n = t;

}

/*
 通过函数的参数返回值
 */
int maxmin_num(int a, int b, int c, int *min)
{
	int ret;
	ret = (a > b ? a : b) > c ? (a > b ? a : b) : c;
	*min = (a < b ? a : b) < c ? (a < b ? a : b) : c;

	return ret;
}



