#include <stdio.h>

int isLeap(int year);
int daysofmonth(int m, int y);
int main(void)
{
	int y, m, d;
	int sum = 0;

	printf("请输入年/月/日:");
	scanf("%d/%d/%d", &y, &m, &d);

	for (int i = 1; i < m; i++) {
		sum += daysofmonth(i, y);	
	}
	sum += d;
	printf("%d/%d/%d是这一年的第%d天\n", y, m, d, sum);

	return 0;
}

/*
 是否是闰年
 */
int isLeap(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return 1;
	return 0;
}

/*
 计算给定的月份有多少天
 */
int daysofmonth(int m, int y)
{
	int ret;

	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		ret =  31;
	else if (m == 2)
		ret = 28 + isLeap(y);	
	else
		ret = 30;

	return ret;
}

