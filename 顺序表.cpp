#include <stdio.h>
#include <stdlib.h>
#define Max_op 20
#include <time.h>

typedef struct Vector
{
	//存储类型为整型
	int* data;
	//顺序表的大小和目前的长度
	int size, length;
}Vector;

//初始化顺序表,函数返回类型为Vector*
Vector* init(int n)
{
	Vector* vec = (Vector*)malloc(sizeof(Vector));
	vec->data = (int*)malloc(sizeof(int) * n);
	vec->size = n;
	vec->length = 0;
	return vec;
}

//销毁顺序表
void clear(Vector* vec)
{
	//当开辟空间失败时销毁空间
	if (vec == NULL)
	{
		return;
	}
	free(vec->data);
	free(vec);
}

//当满时进行扩容
int expand(Vector* vec)
{
	int new_size = vec->size * 2;
	int * p= (int*)realloc(vec->data, sizeof(int) * new_size);
	//申请空间失败时返回0
	if (p == NULL) return 0;
	vec->size = new_size;
	vec->data = p;
	return 1;
}

//插入元素
int insert(Vector* vec, int idx, int val)
{
	//当顺序表为空时插入失败
	if (vec == NULL) return 0;
	//当插入位置符合时插入失败
	if (idx<0 || idx>vec->length) return 0;
	//当顺序表满时进行扩容
	if (vec->length == vec->size)
	{
		if (expand(vec) == 0)return 0;
		
	}
	for (int i = vec->length; i > idx; i--)
	{
		vec->data[i] = vec->data[i - 1];
	}
	vec->data[idx] = val;
	vec->length += 1;
	return 1;
}

//删除元素
int del(Vector* vec, int idx)
{
	if (vec == NULL) return 0;
	if (vec->length == 0) return 0;
	if (idx < 0 ||idx >= vec->length) return 0;
	//idx就是程序员眼中的位置
	for (int i = idx+1; i < vec->length; i++)
	{
		vec->data[i - 1] = vec->data[i];
	}
	vec->length -= 1;
	return 1;
}

//输出顺序表
void output(Vector* vec)
{
	//输出顺序表的长度
	printf("Vector(%d)=[", vec->length);
	for (int i = 0; i < vec->length; i++)
	{
		printf("%d", vec->data[i]);
		if (i != (vec->length) - 1) printf(",");
	}
	printf("]\n");
}
int main()
{
	srand((unsigned int)time(NULL));
	//随机模拟插入删除
	int op, idx, val;
	//最多的操作次数
	Vector* vec = init(1);
	for (int i = 0; i < Max_op; i++)
	{
		//插入和删除为3:1的比例
		op = rand() % 4;
		idx = rand() % (vec->length + 1);
		val = rand() % 100;
		switch (op)
		{
		case 0:
			printf("插入 %d 至 顺序表位置 %d 中\n", val, idx);
			insert(vec, idx, val);
			break;
		case 1:
			printf("从顺序表的位置 %d 删除元素\n", idx);
			del(vec, idx);
			break;
		case 2:
			printf("插入 %d 至 顺序表位置 %d 中\n", val, idx);
			insert(vec, idx, val);
			break;
		case 3:
			printf("插入 %d 至 顺序表位置 %d 中\n", val, idx);
			insert(vec, idx, val);
			break;
		}
		output(vec);
		printf("\n");
	}
	return 0;
}