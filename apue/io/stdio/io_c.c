#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch;

	if (argc < 2)
		return -1;

	fp = fopen(argv[1], "r");
	if (NULL == fp)
		return -1;
	// 读fp 写stdout
	while (1) {
		ch = fgetc(fp);
		if (ch == EOF) {
			// 结束/出错
			if (ferror(fp)) {
				printf("fgetc() error\n");
				fclose(fp);
				return -1;
			}
			break;
		}
		fputc(ch, stdout);
	}
	fclose(fp);

	return 0;
}

