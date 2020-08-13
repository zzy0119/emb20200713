#include <stdio.h>

int main(void)
{
	int arr[2][4][4] = {
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}, 
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		} 
	};

	for (int r = 0; r < 2; r++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (arr[r][i][j]) {
					printf("[]");
				} else {
					printf("  ");
				}
			}
			printf("\n");
		}
	}

	return 0;
}
