#include <stdio.h>

#define NAMESIZE	32

typedef struct stu_st {
	char name[NAMESIZE];
	float score;
} a;
// a结构体类型

typedef struct stu_st stu_t;

int main(void)
{
	stu_t arr[10];
	int max, min;

	max = min = 0;
	for (int i = 0; i < 10; i++) {
		printf("请输入第%d学生的名字: ", i+1);	
		scanf("%s", arr[i].name);
		printf("请输入第%d学生的成绩: ", i+1);
		scanf("%f", &arr[i].score);
		if (i > 0) {
			if (arr[i].score > arr[max].score)
				max = i;
			if (arr[i].score < arr[min].score)
				min = i;
		}
	}

	printf("%s的成绩最高，为%f\n", arr[max].name, arr[max].score);
	printf("%s的成绩最低，为%f\n", arr[min].name, arr[min].score);

	return 0;
}
 
