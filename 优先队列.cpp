#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct priority_queue
{
	int* data;
	int count, size;
}priority_queue;

priority_queue* init(int n)
{
	priority_queue* q = (priority_queue*)malloc(sizeof(priority_queue));
	//n+1是为了保证左边为2*i，右边为2*i-1，最初下标是从1开始
	q->data = (int*)malloc(sizeof(int) * (n + 1));
	q->count = 0;
	q->size = n;
	return q;
}

void clear(priority_queue* q)
{
	if (q == NULL)return;
	free(q->data);
	free(q);
}

void swap(int& p1, int& p2)
{
	int tmp = p1;
	p1 = p2;
	p2 = tmp;
}

int push(priority_queue* p, int val)
{
	//将元素放到最后，再向前调整
	if (p->count == p->size)return 0;
	p->count += 1;
	p->data[p->count] = val;
	int idx = p->count;
	//右移一位表示除以2操作，即就是得到父节点
	while (idx >> 1 && p->data[idx] > p->data[idx >> 1])
	{
		swap(p->data[idx], p->data[idx >> 1]);
		idx >>= 1;
	}
	return 1;
}


int empty(priority_queue* p)
{
	return p->count == 0;
}

int pop(priority_queue* p)
{
	if (empty(p))return 0;
	//将最后面的元素拿到前面，再将该元素重排
	p->data[1] = p->data[p->count];
	p->count--;
	int idx = 1;
	while ((idx << 1) <= p->count)
	{
		int tmp = idx;
		//找到左子树和右子树的索引
		int l = idx << 1;
		int r = idx << 1 | 1;
		if (p->data[l] > p->data[tmp])tmp = l;
		if (r <= p->count && p->data[r] > p->data[tmp])tmp = r;
		//此时表明已经是最小值，因为tmp不变
		if (tmp == idx)break;
		swap(p->data[idx], p->data[tmp]);
		idx = tmp;
	}
	return 1;
}

int top(priority_queue* p)
{
	return p->data[1];
}

int main()
{
	srand(time(0));
	priority_queue* p = init(30);
	for (int i = 0; i < 30; i++)
	{
		int val = rand() % 100;
		push(p, val);
		printf("插入%d到优先队列中\n", val);
	}
	for (int i = 0; i < 30; i++)
	{
		printf("%d ", top(p));
		pop(p);
	}
	return 0;
}