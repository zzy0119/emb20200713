#include <stdio.h>

// 练习：定义一个学生结构体(姓名，成绩), 读入10个学生的信息, 求得成绩最高的学生和最低的学生

// 结构体
struct stu_st {
	char *name;
	int age;
	float score;
};

int main(void)
{
	struct stu_st s = {"小李", 20, 100};
	struct stu_st *p = &s;
	struct stu_st arr[3] = {{"小王", 29, 99}, {"小白", 24, 80}, {"小黑", 26, 98}};

	s.score = 98;
	printf("%s %d %f\n", s.name, s.age, s.score);
	printf("%s %d %f\n", p->name, p->age, p->score);

	for (int i = 0; i < 3; i++) {
		printf("%s %d %f\n", arr[i].name, arr[i].age, arr[i].score);
	}

	return 0;
}

