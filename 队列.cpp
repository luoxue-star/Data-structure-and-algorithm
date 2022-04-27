#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_op 30

typedef struct queue
{
	int* data;
	int length;
	int head, tail;
	int count;//存储当前队列元素的个数
}queue;

queue* init(int n)
{
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL) return NULL;
	else
	{
		q->data = (int*)malloc(sizeof(int) * n);
		q->head = q->tail = q->count = 0;
		q->length = n;
		return q;
	}
}

void clear(queue* q)
{
	if (q == NULL) return;
	free(q->data);
	free(q);
}

//判断队列是否为空
int empty(queue* q)
{
	return q->count == 0;
}

int front(queue* q)
{
	return q->data[q->head];
}

int push(queue* q, int val)
{
	if (q == NULL) return 0;
	if (q->count == q->length) return 0;
	q->data[q->tail++] = val;
	//当尾部指针指向最后时，让尾部指向第0位
	if (q->tail == q->length) q->tail -= q->length;
	q->count += 1;
	return 1;
}

int pop(queue* q)
{
	if (q == NULL) return 0;
	if (empty(q)) return 0;
	q->head++;
	if (q->head == q->length) q->head -= q->length;
	q->count -= 1;
	return 1;
}

void output(queue* q)
{
	printf("queue = [");
	//小于尾部的理由和上面等于长度一致
	for (int i = q->head; i < q->head+q->count; i++)
	{
		//需要自己仔细推敲，画图思索，head的位置始终是程序员认为的位置
		//而tail的位置则是程序员所认为的位置加上1
		//可以执行一下试试看
		int idx = i % q->length;
		printf("%d ", q->data[idx]);
	}
	printf("]\n");
}
int main()
{
	queue* q = init(3);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < Max_op; i++)
	{
		int val = rand() % 100;
		int op = rand() % 2;
		switch (op)
		{
		case 0:
			push(q, val);
			printf("%d 入队\n", val);
			break;
		case 1:
			pop(q);
			printf("出队\n");
		default:
			break;
		}
		output(q);
		printf("head:%d, tail:%d, count:%d\n", q->head,
			q->tail, q->count);
	}
	return 0;
}