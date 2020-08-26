#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[10] = {};

	if (argc < 2)
		return 1;
	fp = fopen(argv[1], "r");
	// if error
	fseek(fp, -10, SEEK_END);
	fread(buf, 1, 9, fp);
	puts(buf);
	
	// 获取当前流的偏移值
	printf("%ld\n", ftell(fp));

	fclose(fp);

	return 0;
}

