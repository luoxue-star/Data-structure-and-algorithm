#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int& a1, int& a2)
{
	int tmp = a1;
	a1 = a2;
	a2 = tmp;
}

void downupdate(int* arr, int n, int idx)
{
	while ((idx << 1) <= n)
	{
		int tmp = idx;
		int l = idx << 1;
		int r = idx << 1 | 1;
		if (arr[l] > arr[tmp] && l >= 1)tmp = l;
		//r<=n��ֹԽ��
		if (arr[r] > arr[tmp] && r <= n)tmp = r;
		if (tmp == idx)break;
		swap(arr[tmp], arr[idx]);
		idx = tmp;
	}
}

void heap_sort(int* arr, int n)
{
	//ʹ�������±��1��ʼ
	arr -= 1;
	//���µ���,�������С������
	//��һ��ѭ�����ڵ�����һ������нڵ㣬������һ�㵽����
	for (int i = n >> 1; i >= 1; --i)
	{
		//�ڶ���ѭ�������ýڵ���·��ڵ�(��downupdate��)
		int idx = i;
		downupdate(arr, n, i);
	}

	//��Ϊ������н����Ѻ�ֻ��ÿһ��������������ģ��������ڵ�������ȫ������
	//���������������·��Ļ������Ϸ����������
	//ÿ�ζ������������ţ��������ս��������Ǵ�С���������
	for (int i = n; i > 1; i--)
	{
		swap(arr[1], arr[i]);
		//������ʣ��i-1����Ҫ�������ǵ�һ��Ԫ��
		downupdate(arr, i - 1, 1);
	}
}

void output(int* arr, int n)
{
	printf("arr[%d] = [", n);
	for (int i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}
	printf("]\n");
}
int main()
{
	srand((unsigned int)time(NULL));
	int* arr = (int*)malloc(sizeof(int*) * 30);
	for (int i = 0; i < 30; i++)
	{
		arr[i] = rand() % 100;
	}
	output(arr, 30);
	heap_sort(arr, 30);
	output(arr, 30);
	return 0;
}
