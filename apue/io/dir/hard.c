#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>

#define BUFSIZE	64

int main(int argc, char *argv[])
{
	struct stat res;
	struct passwd *pw;
	struct group *grp;
	struct tm *tmp;
	char buf[BUFSIZE] = {};

	if (argc < 2)
		return 1;

	if (lstat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	// 文件的类型
	if ((res.st_mode & S_IFMT) == S_IFREG)
		putchar('-');
	else if ((res.st_mode & S_IFMT) == S_IFDIR)
		putchar('d');

	// 文件权限 
	if (res.st_mode & S_IRUSR)
		putchar('r');
	else 
		putchar('-');
	if (res.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if (res.st_mode & S_IXUSR) {
		if (res.st_mode & S_ISUID)
			putchar('s');
		else 
			putchar('x');
	}else
		putchar('-');

	// 文件硬链接个数
	printf(" %ld ", res.st_nlink);

	// 文件拥有者
	// re.st_uid --->uname getpwuid(3)
	pw = getpwuid(res.st_uid);
	if (NULL == pw) {
		perror("getpwuid");
		return 1;
	}
	printf("%s ", pw->pw_name);	
	// 文件所属组
	// res.st_gid --->gname  getgrgid(3)
	grp = getgrgid(res.st_gid);
	// if error
	printf("%s ", grp->gr_name);

	// 文件的字节个数 != 所占用磁盘空间大小(块 4k)
	printf("%ld ", res.st_size);

	// 文件最后一次修改时间
	tmp = localtime(&res.st_mtime);
	strftime(buf, BUFSIZE-1, "%m %d %H:%M", tmp);
	printf("%s ", buf);

	printf("\n");

	return 0;
}



