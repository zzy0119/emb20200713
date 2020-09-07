#include <stdio.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define LOCKFILE	"/var/run/mydaemon.pid"
#define BUFSIZE		1024

int mydaemon(void);
int running_only(void);
int main(void)
{
	// 连接
	openlog("mydaemon.c", LOG_PID | LOG_PERROR, LOG_DAEMON);
#if 1
	if (mydaemon() == -1) {
		fprintf(stderr, "mydaemon() failed\n");
		exit(1);
	}
#endif
#if 0
	if (daemon(0, 0) == -1) {
		perror("daemon()");
		exit(1);
	}
#endif
	// 单实例
	if (running_only() == -1) {
		syslog(LOG_ERR, "running_only() failed\n");
		exit(1);
	}

	// 提交日志
	syslog(LOG_INFO, "my daemon process successfully");
	
	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	closelog();

	exit(0);
}

int mydaemon(void)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		return -1;
	}
	if (pid > 0) {
		// parent
		exit(0);
	}
	// child 不是所在进程组的组长
	if (setsid() == -1) {
		perror("setsid()");
		return -1;
	}

	umask(0);
	chdir("/");

	fd = open("/dev/null", O_RDWR);
	if (fd == -1) {
		perror("open()");
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);

	if (fd > 2)
		close(fd);

	return 0;
}

// 单实例
int running_only(void)
{
	int fd;
	char buf[BUFSIZE] = {};

	fd = open(LOCKFILE, O_RDWR | O_CREAT, 0664);
	if (-1 == fd) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}
	if (lockf(fd, F_TLOCK, 0) == -1) {
		syslog(LOG_ERR, "lockf():%s", strerror(errno));
		close(fd);
		return -1;
	}
	ftruncate(fd, 0);
	snprintf(buf, BUFSIZE, "%d", getpid());
	write(fd, buf, strlen(buf));
	// close(fd);

	return 0;
}






