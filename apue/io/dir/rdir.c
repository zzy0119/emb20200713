#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	DIR *dr;
	struct dirent *entry;

	if (argc < 2)
		return 1;

	dr = opendir(argv[1]);
	if (NULL == dr) {
		perror("opendir()");
		return 1;
	}

	// 读
	while (1) {
		entry = readdir(dr);
		if (NULL == entry) {
			if (errno) {
				// 出错了
				perror("readdir()");
				goto ERROR;
			}
			break;// 目录流到文件末尾
		}
		// 读成功
		printf("%s\n", entry->d_name);	
	}

	closedir(dr);

	return 0;
ERROR:
	closedir(dr);
	return 1;
}

