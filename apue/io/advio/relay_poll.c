#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define TTY1	"/dev/tty9"
#define TTY2	"/dev/tty10"
#define BUFSIZE	1024

// 枚举状态机状态
enum {
	STATE_R,
	STATE_W,
	STATE_E,
	STATE_T
};

// 有限状态机的结构
typedef struct fsm_st {
	int rfd;
	int wfd;
	int state;
	char buf[BUFSIZE]; // 读到数据存储位置
	int cnt;// 读到字节个数
	char *errmsg;
}fsm_t;

int fsm_drive(fsm_t *fsm);
int create_fsm(int fd1, int fd2);
int main(void)
{
	int fd1, fd2;
	
	fd1 = open(TTY1, O_RDWR | O_NONBLOCK);
	if (fd1 == -1) {
		perror("open()");
		return 1;
	}
	fd2 = open(TTY2, O_RDWR);
	if (-1 == fd2) {
		perror("open()");
		close(fd1);
		return 1;
	}
	create_fsm(fd1, fd2);

	return 0;
}

// 构建两个状态机
int create_fsm(int fd1, int fd2)
{
	// 构建使用的两个状态机
	fsm_t fsm12, fsm21;
	int fd1_state, fd2_state;
	struct pollfd pfd[2];

	// 获取fd1 fd2文件的状态 + 非阻塞
	fd1_state = fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_state | O_NONBLOCK);
	fd2_state = fcntl(fd2, F_GETFL);
	fcntl(fd2, F_SETFL, fd2_state | O_NONBLOCK);

	fsm12.rfd = fd1;
	fsm12.wfd = fd2;
	fsm12.state = STATE_R;
	memset(fsm12.buf, '\0', BUFSIZE);
	fsm12.cnt = 0;

	fsm21.rfd = fd2;
	fsm21.wfd = fd1;
	fsm21.state = STATE_R;
	memset(fsm21.buf, '\0', BUFSIZE);
	fsm21.cnt = 0;

	// 初始化poll结构成员
	pfd[0].fd = fd1;
	pfd[1].fd = fd2;

	// 推动状态机运行
	// 轮询
	while (fsm12.state != STATE_T && fsm21.state != STATE_T) {
		if (fsm12.state == STATE_E) {
			fsm_drive(&fsm12);
			continue;
		}
		if (fsm21.state == STATE_E) {
			fsm_drive(&fsm21);
			continue;
		}
		pfd[0].revents = 0;
		pfd[1].revents = 0;

		if (fsm12.state == STATE_R) {
			pfd[0].events |= POLLIN;
		} else if (fsm12.state == STATE_W) {
			pfd[1].events |= POLLOUT;	
		}

		if (fsm21.state == STATE_R) {
			pfd[1].events |= POLLIN;		
		} else if (fsm21.state == STATE_W) {
			pfd[0].events |= POLLOUT;
		}

		if (poll(pfd, 2, -1) == -1) {
			perror("poll()");
			goto ERROR;
		}

		if (pfd[0].revents & POLLIN || pfd[1].revents & POLLOUT)
			fsm_drive(&fsm12); // r tty1  w tty2
		if (pfd[1].revents & POLLIN || pfd[0].revents & POLLOUT)
			fsm_drive(&fsm21); // r tty2 w tty1
	}

	fcntl(fd1, F_SETFL, fd1_state);
	fcntl(fd2, F_SETFL, fd2_state);
	return 0;
ERROR:
	fcntl(fd1, F_SETFL, fd1_state);
	fcntl(fd2, F_SETFL, fd2_state);
	return -1;
}

// 状态机状态改变
int fsm_drive(fsm_t *fsm)
{
	int ret;

	switch (fsm->state) {
		case STATE_R:
			// 非阻塞io eof-->0 success--->cnt -1&&errno==EAGAIN EWOULDBLOCK
			fsm->cnt = read(fsm->rfd, fsm->buf, BUFSIZE);
			if (fsm->cnt == -1) {
				if (errno == EAGAIN || errno == EWOULDBLOCK) {
					// 没数据
					break;
				}
				// 出错
				fsm->state = STATE_E;
				fsm->errmsg = "read()";
			} else if (fsm->cnt > 0) {
				fsm->state = STATE_W;
			} else {
				// == 0 eof
				fsm->state = STATE_T;
			}
			break;
		case STATE_W:
			ret = write(fsm->wfd, fsm->buf, fsm->cnt);
			if (ret == -1) {
				fsm->errmsg = "write()";
				fsm->state = STATE_E;
			} else {
				fsm->state = STATE_R;
				memset(fsm->buf, '\0', BUFSIZE);
				fsm->cnt = 0;
			}
			break;
		case STATE_E:
			perror(fsm->errmsg);
			fsm->state = STATE_T;
			break;
		case STATE_T:
			break;
		default:
			break;
	}

}

