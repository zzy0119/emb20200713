
/*
1. 将命令行的argv[1]对应的字符串存储到堆空间中，并将字符串中的字符排序 
2. 定义动态数组，能够随机向数组中增减元素，是的数组的空间恰好能够容纳数组的成员 
	int addArr(int *arr, int *n, int newElement)
	int delArr(int *arr, int *n, int key)
	void showArr(int *arr, int n);
3. 统计命令行第二个参数字符串中大写字母的个数，小写字母的个数，以及数字字符的个数
4. 尝试打印一下图形
	[]
	[]
	[][]

	[][]
	[][]

	[][][]
	  []
5. 打印一个杨辉三角的前10行
1
1  1
1  2  1
1  3  3  1
1  4  6  4  1
1  5  10 10 5  1
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_str(char *str);
int main(int argc, char *argv[])
{
	char *p;

	if (argc < 2)
		return 1;

	p = malloc(strlen(argv[1])+1);
	if (NULL == p)
		return 1;
	strcpy(p, argv[1]);
	sort_str(p);
	puts(p);

	return 0;
}

/*
 字符串排序
 */
void sort_str(char *str)
{
	int i, j;
	int len = strlen(str);
	char t;
	int min_index;

	for (i = 0; i < len-1; i++) {
		min_index = i;
		for (j = i+1; j < len; j++) {
			if (str[j] < str[min_index])
				min_index = j;
		}
		if (min_index != i) {
			t = str[i];
			str[i] = str[min_index];
			str[min_index] = t;
		}
	}	
}




