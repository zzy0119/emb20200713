#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFSIZE	128

long mydu(const char *path);
int main(int argc, char *argv[])
{

	if (argc < 2)
		return 1;
	printf("%ld\n",mydu(argv[1]));

	return 0;
}

// 统计给定文件所占用磁盘空间大小(K)
long mydu(const char *path)
{
	int sum = 0;
	struct stat res;
	DIR *dp;
	struct dirent *entry;
	char buf[BUFSIZE] = {};

	if (lstat(path, &res) == -1) {
		perror("stat()");
		return -1;
	}
	// 是否是目录
	if (!S_ISDIR(res.st_mode)) {
		printf("path:%s大小是%ldK\n", path, res.st_blocks/2);
		return res.st_blocks / 2;
	}

	// 目录自身大小累加
	printf("path:%s大小是%ldK\n", path, res.st_blocks/2);
	sum = res.st_blocks/2;

	// 解析目录中的每一个文件，累加总大小
	dp = opendir(path);
	if (NULL == dp) {
		perror("opendir()");
		return -1;
	}
	while (1) {
		entry = readdir(dp);	
		if (NULL == entry) {
			if (errno) {
				perror("readdir()");
				goto ERROR;
			}
			break;
		}
		// 刨除"path/.和path/.."
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		// "/etc" "/etc/"
		memset(buf, '\0', BUFSIZE);
		strncpy(buf, path, BUFSIZE);
		strncat(buf, "/", BUFSIZE);
		strncat(buf, entry->d_name, BUFSIZE); //path下文件的路径 
		sum += mydu(buf);
	}

	closedir(dp);
	return sum;
ERROR:
	closedir(dp);
	return -1;
}



