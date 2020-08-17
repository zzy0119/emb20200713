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
	struct stu_st stu;
	seq_t *p;
	char *del_name = "stu8"; 
	int del_age = 22;

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

	return 0;
}
