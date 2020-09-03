#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

// 求出两个整型数的商
int div2num(int m, int n)
{
	if (n == 0)	 
		// 让调用着重新输入
		longjmp(env, 1);

	return m / n;
}

int main(int argc, char *argv[]) 
{
	int num1, num2;
	int res, ret;

	ret = setjmp(env);
	if (ret == 0) {
		// 直接调用的
		printf("请输入两个整型数:");
	} else {
		// longjmp跳转过来
		printf("请重新输入两个整型数:");
	}

	scanf("%d%d", &num1, &num2);
	res = div2num(num1, num2);
	printf("%d / %d = %d\n", num1, num2, res);
	

	exit(0);
}

