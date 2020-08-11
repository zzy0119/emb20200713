#include <stdio.h>
#include <string.h>

int myatoi(const char *p);
int main(int argc, char **argv)
{
	int left, right;
	int res;
	// 命令行参数
	if (argc < 4)
		return 1;

	left = myatoi(argv[1]);
	right = myatoi(argv[3]);

	if (strcmp(argv[2], "+") == 0) {
		res = left + right;
	} else if (strcmp(argv[2], "-") == 0) {
		res = left - right;
	}
	printf("%d %s %d = %d\n", left, argv[2], right, res);	

	return 0;
}

int myatoi(const char *p)
{
	int res = 0;
	//"123"--->123 
	while (*p) {
		res = res * 10 + (*p-'0');
		p++;
	}

	return res;
}


