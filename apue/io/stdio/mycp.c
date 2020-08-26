#include <stdio.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	FILE *rfp, *wfp;
	char buf[BUFSIZE] = {};
	int cnt;

	if (argc < 3)
		return -1;

	rfp = fopen(argv[1], "r");
	if (NULL == rfp) {
		printf("fopen() failed\n");
		goto ERROR;
	}
	wfp = fopen(argv[2], "w");
	if (NULL == wfp) {
		fprintf(stderr, "fopen() failed\n");
		goto ERROR2;
	}

	while (1) {
		cnt = fread(buf, 1, BUFSIZE, rfp);
		if (cnt == 0) {
			if (ferror(rfp)) 
				goto ERROR3;
			break;
		}
		fwrite(buf, 1, cnt, wfp);
	}
	fclose(rfp);
	fclose(wfp);

	return 0;
ERROR3:
	fclose(wfp);
ERROR2:
	fclose(rfp);
ERROR:
	return -1;
}

