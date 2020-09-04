#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <glob.h>
#include <string.h>

int parse_str(char *ptr, glob_t *res);
int main(void)
{
	char *ptr = NULL;
	size_t n = 0;
	glob_t globres;
	pid_t pid;

	while (1) {
		printf("[myshell]$ ");
		// 读一行	getline(3)
		if (getline(&ptr, &n, stdin) == -1) {
			perror("getline()");
			exit(1);
		}
		if (!strcmp(ptr, "exit\n"))
			break;
		// "ls -l"--->"ls" "-l" glob(3)GLOB_NOCHCK
		// 按空格和换行切割字符串 strsep(3) /strtok(3) 
		parse_str(ptr, &globres);
#if 0
		for (int i = 0; i < globres.gl_pathc; i++)
			puts((globres.gl_pathv)[i]);
#endif
		pid = fork();
		if (pid == 0) {
			execvp((globres.gl_pathv)[0], globres.gl_pathv);
			perror("execvp()");
			exit(1);
		}
		wait(NULL);
		free(ptr);
		ptr = NULL;
		n = 0;
	}

	return 0;
}

/*
 将ptr切割结果存储到globres
 */
int parse_str(char *ptr, glob_t *res)
{
	char *ret;
	int i = 0;
	// "ls -l -a -h   "
	while (1) {
		ret = strsep(&ptr, " \n\t");	
		if (ret == NULL)
			break;
		if (*ret == '\0') // 分隔符连续
			continue;
		glob(ret, GLOB_NOCHECK | GLOB_APPEND * i, NULL, res);
		i = 1;
	}

	return 0;
}









