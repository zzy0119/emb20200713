#include <stdio.h>

#define BASEYEAR	1990 // 宏定义

int main(void)
{
	int y, m;
	int sumdays = 0;
	int i;
	int firstday;
	int monthdays;

	// 读入用户输入的年月 y/m
	printf("请输入年/月:");
	scanf("%d/%d", &y, &m);

	// 计算BASEYEAR.1.1~y/m/1有多少天
	// 1.[BASEYEAR,y) + [y.1,y.m)+1
	for (i = BASEYEAR; i < y; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)	{
			// 闰年
			sumdays += 366; // sumdays = sumdays + 366;
		} else {
			sumdays += 365;
		}
	}
	for (i = 1; i < m; i++) {
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || \
				i == 10 || i == 12)	
			sumdays += 31;
		else if (i == 4 || i == 6 || i == 9 || i == 11)
			sumdays += 30;
		else
			sumdays += (y % 4 == 0 && y % 100 != 0 || y % 400 == 0 ? 29 : 28);
	}
	sumdays ++; // 1号

	// y/m/1是星期几
	firstday = sumdays % 7;
// 	printf("%d\n", firstday);

	// m月有多少天
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		monthdays = 31;
	else if (m == 4 || m == 6 || m == 9 || m == 11)
		monthdays = 30;
	else
		monthdays = (y % 4 == 0 && y % 100 != 0 || y % 400 == 0 ? 29 : 28);

	// 打印日历
	printf("     %d %d\n", m, y);
	printf("Su Mo Tu We Th Fr Sa\n");
	// 1号星期几之前的空格
	for (i = 0; i < firstday; i++)
		printf("   ");
	for (i = 1; i <= monthdays; i ++ ) {
		printf("%2d%c", i, (firstday+i)%7==0?'\n':' ');	
	}
	printf("\n");

	return 0;
}

