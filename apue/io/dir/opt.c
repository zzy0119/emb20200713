#include <stdio.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *optstring = "-lah:d::";
	// 长格式选项
	struct option ops[] = {
		{"help", 0, NULL, 'e'},
		{"long", 1, NULL, 'o'},
		{0, 0, 0, 0}
	};
	int ch;

	while (1) {
		// ch = getopt(argc, argv, optstring);
		ch = getopt_long(argc, argv, optstring, ops, NULL);
		if (ch == -1)
			break;
		switch (ch) {
			case 'l':
				printf("识别到了选项-l\n");
				break;
			case 'a':
				printf("识别到了选项-a\n");
				break;
			case 'h':
				printf("识别到了带参数选项选项-h\n");
				printf("参数%s\n", optarg);
				break;
			case 'd':
				printf("识别到了可选参数选项-d\n");
				if (optarg != NULL) {
					printf("参数%s\n", optarg);
				}
				break;
			case 1:
				printf("非选项参数\n");
				printf("%s\n", argv[optind-1]);
				break;
			case 'e':
				printf("识别到长格式选项help\n");
				break;
			case 'o':
				printf("识别到长格式选项long\n");
				printf("%s\n", optarg);
				break;
			default:
				printf("不知道\n");
				break;
		}
	}

	return 0;
}



