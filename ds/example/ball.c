#include <stdio.h>
#include <stack.h>
#include <queue.h>

// 判断此队列中的数据是否顺序的
static int seq_ball(queue_t *q)
{
	queue_t *tmp;
	int cur;
	int pre = 0;
	int flag = 1;

	tmp = queue_init(sizeof(int), 28);

	while (!queue_empty(q)) {
		deq(q, &cur);
		if (cur < pre && flag == 1) {
			flag = 0;// 不是顺序的
		} 
		enq(tmp, &cur);
		pre = cur;
	}
	
	while (!queue_empty(tmp)) {
		deq(tmp, &cur);
		enq(q, &cur);
	}
	queue_destroy(tmp);

	return flag;
}

int main(void)
{
	stack_t *one_min, *five_min, *one_hour;
	queue_t *ball;
	int n, m;
	int days = 0;

	one_min = stack_init(sizeof(int), 4);
	five_min = stack_init(sizeof(int), 11);
	one_hour = stack_init(sizeof(int), 11);
	// if error
	ball = queue_init(sizeof(int), 28);
	// if error	

	// 27个入队
	for (int i = 1; i <= 27; i++) {
		enq(ball, &i);	
	}

	while (1) {
		deq(ball, &n);	
		if (!full(one_min))	{
			push(one_min, &n);
		} else {
			while (!empty(one_min)) {
				pop(one_min, &m);
				enq(ball, &m);
			}
			if (!full(five_min)) {
				push(five_min, &n);
			} else {
				while (!empty(five_min)) {
					pop(five_min, &m);
					enq(ball, &m);
				}
				if (!full(one_hour)) {
					push(one_hour, &n);
				} else {
					while (!empty(one_hour)) {
						pop(one_hour, &m);
						enq(ball, &m);
					}
					enq(ball, &n);
					days ++;
					// 所有的球都在队列---》判断是否从1号到27
					if (seq_ball(ball)) {
						// 满足
						break;	
					}
				}
			}
		}
	}

	printf("经过%d天球的次序回到了初始的从小到大\n", days / 2);

	destroy(one_min);
	destroy(five_min);
	destroy(one_hour);
	queue_destroy(ball);

	return 0;
}

