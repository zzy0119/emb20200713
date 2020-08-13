#include <stdio.h>

int main(void)
{
	int arr[4][4] = {
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	};

	printf("\33[2J");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[i][j]) {
				printf("\33[46m\33[%d;%dH[]", i+1, j*2+1);
				printf("\33[0m");
			}
		}
	}

	return 0;
}
