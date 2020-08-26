#include <stdio.h>

#define BUFSIZE	100

// 将fp1文件写入fp2
static int copyfile(FILE *fp1, FILE *fp2)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = fread(buf, 1, BUFSIZE, fp1);	
		if (cnt == 0) {
			if (ferror(fp1))
				return -1;
			break;
		}
		fwrite(buf, 1, cnt, fp2);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fp, *tmp;
	int len;

	if (argc < 2)	
		return -1;

	fp = fopen(argv[1], "r+");
	// if error
	tmp = tmpfile();
	// if error

	// 倒叙读fp, 写tmp
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 1, SEEK_CUR);	
	while (len > 0) {
		fseek(fp, -2, SEEK_CUR);	
		fputc(fgetc(fp), tmp);
		len --;
	}
	rewind(tmp);
	rewind(fp);

	copyfile(tmp, fp);
	fclose(tmp);
	fclose(fp);

	return 0;
}






	
