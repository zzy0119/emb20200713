#include <stdio.h>

#define N	10

int main(void)
{
	int score[N] = {};
	int cnt[N+1] = {};
	int sum = 0;

	for (int i = 0; i < N; i++) {
		printf("请输入第%d个学生的成绩:", i+1);
		scanf("%d", &score[i]);// score+i
		cnt[score[i] / 10]++;
	}

	// 打印
	printf("100:");
	for (int i = 0; i < cnt[10]; i++)
		printf("* ");
	printf("\n");
	for (int i = 9; i >= 6; i--) {
		printf("%d~%d:", i*10, i*10+9);	
		// 当前分数段的个数
		for (int j = 0; j < cnt[i]; j++) {
			printf("* ");	
		}
		printf("\n");
	}
	// 0~50
	for (int i = 0; i <= 5; i++)
		sum += cnt[i];
	printf("0~59:");
	for (int i = 0; i < sum; i++)
		printf("* ");
	printf("\n");

	return 0;
}

