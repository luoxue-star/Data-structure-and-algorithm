#include <stdio.h>
#include <stdlib.h>
#define Max_op 20
#include <time.h>

typedef struct Vector
{
	//�洢����Ϊ����
	int* data;
	//˳���Ĵ�С��Ŀǰ�ĳ���
	int size, length;
}Vector;

//��ʼ��˳���,������������ΪVector*
Vector* init(int n)
{
	Vector* vec = (Vector*)malloc(sizeof(Vector));
	vec->data = (int*)malloc(sizeof(int) * n);
	vec->size = n;
	vec->length = 0;
	return vec;
}

//����˳���
void clear(Vector* vec)
{
	//�����ٿռ�ʧ��ʱ���ٿռ�
	if (vec == NULL)
	{
		return;
	}
	free(vec->data);
	free(vec);
}

//����ʱ��������
int expand(Vector* vec)
{
	int new_size = vec->size * 2;
	int * p= (int*)realloc(vec->data, sizeof(int) * new_size);
	//����ռ�ʧ��ʱ����0
	if (p == NULL) return 0;
	vec->size = new_size;
	vec->data = p;
	return 1;
}

//����Ԫ��
int insert(Vector* vec, int idx, int val)
{
	//��˳���Ϊ��ʱ����ʧ��
	if (vec == NULL) return 0;
	//������λ�÷���ʱ����ʧ��
	if (idx<0 || idx>vec->length) return 0;
	//��˳�����ʱ��������
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

//ɾ��Ԫ��
int del(Vector* vec, int idx)
{
	if (vec == NULL) return 0;
	if (vec->length == 0) return 0;
	if (idx < 0 ||idx >= vec->length) return 0;
	//idx���ǳ���Ա���е�λ��
	for (int i = idx+1; i < vec->length; i++)
	{
		vec->data[i - 1] = vec->data[i];
	}
	vec->length -= 1;
	return 1;
}

//���˳���
void output(Vector* vec)
{
	//���˳���ĳ���
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
	//���ģ�����ɾ��
	int op, idx, val;
	//���Ĳ�������
	Vector* vec = init(1);
	for (int i = 0; i < Max_op; i++)
	{
		//�����ɾ��Ϊ3:1�ı���
		op = rand() % 4;
		idx = rand() % (vec->length + 1);
		val = rand() % 100;
		switch (op)
		{
		case 0:
			printf("���� %d �� ˳���λ�� %d ��\n", val, idx);
			insert(vec, idx, val);
			break;
		case 1:
			printf("��˳����λ�� %d ɾ��Ԫ��\n", idx);
			del(vec, idx);
			break;
		case 2:
			printf("���� %d �� ˳���λ�� %d ��\n", val, idx);
			insert(vec, idx, val);
			break;
		case 3:
			printf("���� %d �� ˳���λ�� %d ��\n", val, idx);
			insert(vec, idx, val);
			break;
		}
		output(vec);
		printf("\n");
	}
	return 0;
}