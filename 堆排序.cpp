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
		//r<=n防止越界
		if (arr[r] > arr[tmp] && r <= n)tmp = r;
		if (tmp == idx)break;
		swap(arr[tmp], arr[idx]);
		idx = tmp;
	}
}

void heap_sort(int* arr, int n)
{
	//使得数组下标从1开始
	arr -= 1;
	//向下调整,大的在上小的在下
	//第一层循环是在调整这一层的所有节点，最下面一层到最上
	for (int i = n >> 1; i >= 1; --i)
	{
		//第二层循环调整该节点和下方节点(在downupdate内)
		int idx = i;
		downupdate(arr, n, i);
	}

	//因为上面进行建立堆后，只是每一个子树内是有序的，所以现在弹出进行全部排序
	//弹出操作，将最下方的换到最上方后进行重排
	//每次都将大数往最后放，所以最终结果输出的是从小到大的序列
	for (int i = n; i > 1; i--)
	{
		swap(arr[1], arr[i]);
		//弹出后剩下i-1个，要调整的是第一个元素
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
