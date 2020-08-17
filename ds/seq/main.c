#include <stdio.h>
#include <string.h>

#include "seq.h"

#define NAMESIZE	32

struct stu_st {
	char name[NAMESIZE];
	int age;
};

static void pri_stu(const void *data)
{
	const struct stu_st *d = data;
	printf("%s %d\n", d->name, d->age);
}

static int name_cmp(const void *data, const void *key)
{
	const struct stu_st *d = data;
	const char *k = key;

	return strcmp(d->name, k);
}

static int age_cmp(const void *data, const void *key)
{
	const struct stu_st *d = data;
	const int *k = key;

	return d->age - *k;
}

int main(void)
{
	struct stu_st stu, newstu;
	seq_t *p;
	char *del_name = "stu8"; 
	int del_age = 22;
	char *find_name = "stu15";
	struct stu_st *find;

	seq_init(sizeof(struct stu_st), &p);

	for (int i = 0; i < 10; i++) {
		snprintf(stu.name, NAMESIZE, "stu%d", i+1);
		stu.age = 30-i;
		seq_add(p, &stu);
	}

	seq_traval(p, pri_stu);

	printf("*************删除************\n");
	seq_del(p, del_name, name_cmp);
	seq_traval(p, pri_stu);
	printf("*************删除************\n");
	seq_del(p, &del_age, age_cmp);
	seq_traval(p, pri_stu);

	printf("***********替换**************\n");
	strcpy(newstu.name, "数据结构");
	newstu.age = 30;
	seq_update(p, "stu1", name_cmp, &newstu);
	seq_traval(p, pri_stu);

	printf("***********查找**************\n");
	find = seq_find(p, find_name, name_cmp);	
	if (find == NULL)
		printf("没有名字为%s的元\n", find_name);
	else {
		printf("找到了:%s, %d\n", find->name, find->age);
	}

	seq_destroy(p);

	return 0;
}
