#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_op 30

typedef struct Listnode
{
	int data;
	//指向下一个节点
	struct Listnode* next;
}Listnode;

typedef struct Linklist
{
	Listnode head;//虚拟头结点
	int length;//链表的长度
};

//初始化节点
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

//初始化节点
Linklist* init_link()
{
	Linklist* l = (Linklist*)malloc(sizeof(Linklist));
	if (l)
	{
		l->length = 0;//初始长度为0
		//这里先将虚拟头结点的下一位置为空
		l->head.next = NULL;//利用虚拟头结点，虚拟头结点的下一位才是第一位
		return l;
	}
	else
	{
		return NULL;
	}
}

//清除节点
void clear_node(Listnode* node)
{
	if (node == NULL) return;
	free(node);
}

//清除链表
void clear_link(Linklist* l)
{
	if (l == NULL) return;
	Listnode* p = l->head.next;
	Listnode* q;
	while (p)
	{
		//将下一个节点存在q中，便于找到下一个节点
		q = p->next;
		clear_node(p);
		p = q;
	}
	free(l);
}

//插入节点
int insert(Linklist* l, int idx, int val)
{
	if (l == NULL) return 0;
	if (idx<0 || idx>l->length) return 0;
	//指向虚拟头结点，虚拟头结点下一位就是真正的第一位节点
	//走一步就是可以向那个位置插入
	//找到虚拟头结点
	Listnode* p = &(l -> head);
	//生成要插入的节点
	Listnode* node = init_node(val);
	while (idx--)
	{
		//找到插入位置的前一位
		p = p->next;
	}
	//画一个小图可以容易理解
	node->next = p->next;
	p->next = node;
	l->length += 1;
	return 1;
}

//删除节点
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
	//q用于存储删除节点指向的下一个位置
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
	//随机生成操作
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
			printf("在位置 %d 插入 %d\n", idx, val);
			insert(l, idx, val);
			break;
		case 3:
			printf("删除位置 %d 的节点\n ", idx);
			del(l, idx);
			break;
		}
		output(l);
		printf("\n");
	}
	return 0;
}