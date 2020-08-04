#include <stdio.h>

#define BASEYEAR	1990 // 宏定义

/*
	函数的声明
 */
int is_leap(int year);
int days_month(int m, int year);

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
		/*
		 函数的调用
		 	传递的是值！！！！
		 */
		if (is_leap(i))	{ // year = i
			// 闰年
			sumdays += 366; // sumdays = sumdays + 366;
		} else {
			sumdays += 365;
		}
	}
	for (i = 1; i < m; i++) {
		sumdays += days_month(i, y);
	}
	sumdays ++; // 1号

	// y/m/1是星期几
	firstday = sumdays % 7;

	// m月有多少天
	monthdays = days_month(m, y);

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

// 根据给定的年份，判断是否为闰年
/*
   函数的定义
	@year:带计算的年份
	@return:0否 1是
 */
int is_leap(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

/*
 判断给定的月份有多少天
 */
int days_month(int m, int year)
{
	int monthdays;	

	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		monthdays = 31;
	else if (m == 4 || m == 6 || m == 9 || m == 11)
		monthdays = 30;
	else
		monthdays = is_leap(year)+28;

	return monthdays;
}





