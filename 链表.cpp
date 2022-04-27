#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_op 30

typedef struct Listnode
{
	int data;
	//ָ����һ���ڵ�
	struct Listnode* next;
}Listnode;

typedef struct Linklist
{
	Listnode head;//����ͷ���
	int length;//����ĳ���
};

//��ʼ���ڵ�
Listnode* init_node(int val)
{
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	if (p)
	{
		p->data = val;
		p->next = NULL;
		return p;
	}
	else
	{
		return NULL;
	}

}

//��ʼ���ڵ�
Linklist* init_link()
{
	Linklist* l = (Linklist*)malloc(sizeof(Linklist));
	if (l)
	{
		l->length = 0;//��ʼ����Ϊ0
		//�����Ƚ�����ͷ������һλ��Ϊ��
		l->head.next = NULL;//��������ͷ��㣬����ͷ������һλ���ǵ�һλ
		return l;
	}
	else
	{
		return NULL;
	}
}

//����ڵ�
void clear_node(Listnode* node)
{
	if (node == NULL) return;
	free(node);
}

//�������
void clear_link(Linklist* l)
{
	if (l == NULL) return;
	Listnode* p = l->head.next;
	Listnode* q;
	while (p)
	{
		//����һ���ڵ����q�У������ҵ���һ���ڵ�
		q = p->next;
		clear_node(p);
		p = q;
	}
	free(l);
}

//����ڵ�
int insert(Linklist* l, int idx, int val)
{
	if (l == NULL) return 0;
	if (idx<0 || idx>l->length) return 0;
	//ָ������ͷ��㣬����ͷ�����һλ���������ĵ�һλ�ڵ�
	//��һ�����ǿ������Ǹ�λ�ò���
	//�ҵ�����ͷ���
	Listnode* p = &(l -> head);
	//����Ҫ����Ľڵ�
	Listnode* node = init_node(val);
	while (idx--)
	{
		//�ҵ�����λ�õ�ǰһλ
		p = p->next;
	}
	//��һ��Сͼ�����������
	node->next = p->next;
	p->next = node;
	l->length += 1;
	return 1;
}

//ɾ���ڵ�
int del(Linklist* l, int idx)
{
	if (l == NULL) return 0;
	if (idx < 0 || idx >= l->length) return 0;
	Listnode* p = &(l->head);
	Listnode* q;
	while (idx--)
	{
		p = p->next;
	}
	//q���ڴ洢ɾ���ڵ�ָ�����һ��λ��
	q = p->next->next;
	clear_node(p->next);
	p->next = q;
	l->length -= 1;
	return 1;
}

void output(Linklist* l)
{
	printf("Linklist(%d):", l->length);
	for (Listnode* p = l->head.next; p; p = p->next)
	{
		printf("%d-> ", p->data);
	}
	printf("NULL\n");
}
int main()
{
	//������ɲ���
	srand((unsigned int)time(NULL));
	Linklist* l = init_link();
	for (int i = 0; i < Max_op; i++)
	{
		int op = rand() % 4;
		int idx = rand() % (l->length + 1);
		int val = rand() % 100;
		switch (op)
		{
		case 0:
		case 1:
		case 2:
			printf("��λ�� %d ���� %d\n", idx, val);
			insert(l, idx, val);
			break;
		case 3:
			printf("ɾ��λ�� %d �Ľڵ�\n ", idx);
			del(l, idx);
			break;
		}
		output(l);
		printf("\n");
	}
	return 0;
}