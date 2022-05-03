#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_OP 30

void insert_sort(int* num, int n)
{
	for (int i = 1; i < n; i++)
	{
		//��Ϊ��һ�β���Ҫ���������ڲ������������������ǰ
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
		//Ϊ0����û�н���һ�ν���������ֱ������ѭ������
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

//�����lΪ��ʼλ�ã�rΪ��ֹλ�ã�ΪԪ�ظ�����һ
void merge_sort(int* num, int l, int r)
{
	//�����ʱ�������Ϊ2���ͽ�����
	if (r - l <= 1)
	{	
		//��������������ߴ����ұ߾�Ҫ���н���
		if (r - l == 1 && num[l] > num[r])
		{
			int tmp = num[l];
			num[l] = num[r];
			num[r] = tmp;
		}
		return;
	}
	int mid = (l + r) >> 1;
	//���ҷֱ��������
	merge_sort(num, l, mid);
	merge_sort(num, mid + 1, r);
	//�������е������Ӧ������������ȫ�������
	int* temp = (int*)malloc(sizeof(int) * (r - l + 1));
	//����ָ��ֱ�Ҫָ����ߵĵ�һλ���ұߵĵ�һλ����ʱ�洢����ͷ��λ��
	int p1 = l, p2 = mid + 1, k = 0;
	//p1 <= mid || p2 < r ��������Ż����ϲ�
	while (p1 <= mid || p2 <= r)
	{
		//ÿ�ζ�����С��ֵ�ŵ�tmp��
		if (p2 > r || (p1 <= mid && num[p1] <= num[p2]))
		{
			temp[k++] = num[p1++];
		}
		else
		{
			temp[k++] = num[p2++];
		}
	}
	//�����ݿ�����num+l����ʼλ�ã�
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