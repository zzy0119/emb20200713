#include <stdio.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

#define NAMESIZE	32

int main(void)
{
	char name[NAMESIZE] = {};
	char *pwd = NULL;
	struct spwd *sp = NULL;
	char *encrypt = NULL;

	// 读入用户名
	printf("用户名:");
	fgets(name, NAMESIZE, stdin);
	// *strchr(name, '\n') = '\0';
	name[strlen(name)-1] = '\0';

	// 读入密码
	pwd = getpass("密码:");
	// 加密
	sp = getspnam(name);
	if (NULL == sp) {
		perror("getspnam()");
		return 1;
	}
	encrypt = crypt(pwd, sp->sp_pwdp);
	if (NULL == encrypt) {
		perror("crypt");
		return 1;
	}
	// 比对
	if (!strcmp(sp->sp_pwdp, encrypt)) {
		printf("登录成功\n");
	} else {
		printf("密码错误\n");
	}

	return 0;
}

