#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_OP 30

void insert_sort(int* num, int n)
{
	for (int i = 1; i < n; i++)
	{
		//因为第一次不需要排序，且由于插入排序待排序区是在前
		for (int j = i; j > 0 && num[j] < num[j - 1]; --j)
		{
			int tmp = num[j];
			num[j] = num[j - 1];
			num[j - 1] = tmp;
		}
	}
}

void bubble_sort(int* num, int n)
{
	int flag = 1;
	for (int i = 1; i < n && flag; i++)
	{
		//为0表明没有进行一次交换，可以直接跳出循环结束
		int flag = 0;
		for (int j = 0; j < n - i; j++)
		{
			if (num[j] > num[j + 1])
			{
				int tmp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = tmp;
				flag++;
			}
		}
	}
}

//传入的l为起始位置，r为终止位置，为元素个数减一
void merge_sort(int* num, int l, int r)
{
	//如果此时数组个数为2个就结束了
	if (r - l <= 1)
	{	
		//若两个相邻且左边大于右边就要进行交换
		if (r - l == 1 && num[l] > num[r])
		{
			int tmp = num[l];
			num[l] = num[r];
			num[r] = tmp;
		}
		return;
	}
	int mid = (l + r) >> 1;
	//左右分别分裂排序
	merge_sort(num, l, mid);
	merge_sort(num, mid + 1, r);
	//最先运行到这里的应该是最先左右全部排完的
	int* temp = (int*)malloc(sizeof(int) * (r - l + 1));
	//三种指针分别要指向左边的第一位，右边的第一位，临时存储区的头部位置
	int p1 = l, p2 = mid + 1, k = 0;
	//p1 <= mid || p2 < r 这种情况才会填充合并
	while (p1 <= mid || p2 <= r)
	{
		//每次都将最小的值排到tmp中
		if (p2 > r || (p1 <= mid && num[p1] <= num[p2]))
		{
			temp[k++] = num[p1++];
		}
		else
		{
			temp[k++] = num[p2++];
		}
	}
	//将数据拷贝到num+l（起始位置）
	memcpy(num + l, temp, sizeof(int) * (r - l + 1));
	free(temp);
}

void output(int* arr, int n)
{
	printf("[");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}
	printf("]\n");
}

int main()
{
	srand((unsigned int)time(NULL));
	int arr1[MAX_OP];
	int arr2[MAX_OP];
	int arr3[MAX_OP];
	for (int i = 0; i < MAX_OP; i++)
	{
		arr1[i] = arr2[i] = arr3[i] = rand() % 100;
	}
	output(arr1, MAX_OP);
	output(arr2, MAX_OP);
	output(arr3, MAX_OP);
	insert_sort(arr1, MAX_OP);
	bubble_sort(arr2, MAX_OP);
	merge_sort(arr3, 0, MAX_OP-1);
	output(arr1, MAX_OP);
	output(arr2, MAX_OP);
	output(arr3, MAX_OP);
	return 0;
}