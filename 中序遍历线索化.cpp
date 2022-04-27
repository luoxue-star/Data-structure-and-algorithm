#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NORMAL 0
#define THREAD 1

typedef struct Node
{
	int key;
	struct Node* lchild, * rchild;
	//����������Ľڵ㻹����������
	int ltag, rtag;
}Node;

Node* getnewnode(int key)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->lchild = p->rchild = NULL;
	p->key = key;
	p->ltag = p->rtag = 0;
	return p;
}

void clear(Node* root)
{
	if (root == NULL)return;
	//����tag��֤������������Ľڵ��������������
	if (root->ltag == NORMAL)clear(root->lchild);
	if (root->rtag == NORMAL)clear(root->rchild);
	free(root);
}

Node* insert(Node* root, int key)
{
	if (root == NULL)return getnewnode(key);
	if (key == root->key)return root;
	//����������Ĳ��뷽ʽ
	if (key > root->key)root->rchild = insert(root->rchild, key);
	else root->lchild = insert(root->lchild, key);
	//ÿ�η���root����һ�λ�һֱ�ҵ����ʵ�λ�òŽ��в���
	return root;
}

//����������
void inorder(Node* root)
{
	if (root == NULL)return;
	//�ݹ����������
	//���������ҵ�˳�����ÿһ�Ŷ�����
	if(root->ltag==NORMAL)inorder(root->lchild);
	printf("%d ", root->key);
	if(root->rtag==NORMAL)inorder(root->rchild);
}

//�Լ�����ͼ�����
void build_thread(Node* root)
{
	if (root == NULL)return;
	static Node* pre = NULL;
	build_thread(root->lchild);
	if (root->lchild == NULL)
	{
		//��ʱlchild��pre�ĺ��
		root->lchild = pre;
		root->ltag = THREAD;
	}
	if (pre != NULL && pre->rchild == NULL)
	{
		pre->rchild = root;
		pre->rtag = THREAD;
	}
	pre = root;
	//�����ұߵ�������
	build_thread(root->rchild);
}

void output(Node* root)
{
	//pÿ�ζ�ָ��ڵ�ĺ��
	Node* p = root;
	//�ҵ���ǰ��������������ڵ�
	while (p && p->ltag == NORMAL && p->lchild)p = p->lchild;
	while (p)
	{
		printf("%d ", p->key);
		if (p->rtag == THREAD)
		{
			p = p->rchild;
		}
		else
		{
			p = p->rchild;
			//�ҵ���ǰ�ұ߽ڵ������ڵ�
			while (p && p->ltag == NORMAL && p->lchild)p = p->lchild;
		}
	}
	printf("\n");
}

int main()
{
	srand(time(0));
	Node* root = NULL;
	for (int i = 0; i < 30; i++)
	{
		int val = rand() % 100;
		root = insert(root, val);
	}
	build_thread(root);
	inorder(root);
	printf("\n");
	output(root);
	clear(root);
	return 0;
}