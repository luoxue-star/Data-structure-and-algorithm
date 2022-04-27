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
	//n+1��Ϊ�˱�֤���Ϊ2*i���ұ�Ϊ2*i-1������±��Ǵ�1��ʼ
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
	//��Ԫ�طŵ��������ǰ����
	if (p->count == p->size)return 0;
	p->count += 1;
	p->data[p->count] = val;
	int idx = p->count;
	//����һλ��ʾ����2�����������ǵõ����ڵ�
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
	//��������Ԫ���õ�ǰ�棬�ٽ���Ԫ������
	p->data[1] = p->data[p->count];
	p->count--;
	int idx = 1;
	while ((idx << 1) <= p->count)
	{
		int tmp = idx;
		//�ҵ���������������������
		int l = idx << 1;
		int r = idx << 1 | 1;
		if (p->data[l] > p->data[tmp])tmp = l;
		if (r <= p->count && p->data[r] > p->data[tmp])tmp = r;
		//��ʱ�����Ѿ�����Сֵ����Ϊtmp����
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
		printf("����%d�����ȶ�����\n", val);
	}
	for (int i = 0; i < 30; i++)
	{
		printf("%d ", top(p));
		pop(p);
	}
	return 0;
}