#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	char *name[] = {"李文章", "孙飞超", "王晓润", "李嘉豪", "尤杨", "刘天赐", "龚俊"};
	char ch;
	
	do {
		printf("请按回车键开始抽奖\n");
		scanf("%c", &ch);
	} while (ch != '\n');

	sleep(3);
	srand(getpid());
	printf("恭喜%s中奖了，五百万!!!\n", name[rand() % (sizeof(name) / sizeof(*name))]);

	return 0;
}

