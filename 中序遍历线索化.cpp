#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NORMAL 0
#define THREAD 1

typedef struct Node
{
	int key;
	struct Node* lchild, * rchild;
	//标记是正常的节点还是线索化的
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
	//利用tag保证清除的是正常的节点而不是线索化的
	if (root->ltag == NORMAL)clear(root->lchild);
	if (root->rtag == NORMAL)clear(root->rchild);
	free(root);
}

Node* insert(Node* root, int key)
{
	if (root == NULL)return getnewnode(key);
	if (key == root->key)return root;
	//中序二叉树的插入方式
	if (key > root->key)root->rchild = insert(root->rchild, key);
	else root->lchild = insert(root->lchild, key);
	//每次返回root，下一次会一直找到合适的位置才进行插入
	return root;
}

//中序遍历输出
void inorder(Node* root)
{
	if (root == NULL)return;
	//递归遍历左子树
	//按照左中右的顺序输出每一颗二叉树
	if(root->ltag==NORMAL)inorder(root->lchild);
	printf("%d ", root->key);
	if(root->rtag==NORMAL)inorder(root->rchild);
}

//自己画个图好理解
void build_thread(Node* root)
{
	if (root == NULL)return;
	static Node* pre = NULL;
	build_thread(root->lchild);
	if (root->lchild == NULL)
	{
		//此时lchild是pre的后继
		root->lchild = pre;
		root->ltag = THREAD;
	}
	if (pre != NULL && pre->rchild == NULL)
	{
		pre->rchild = root;
		pre->rtag = THREAD;
	}
	pre = root;
	//建立右边的线索化
	build_thread(root->rchild);
}

void output(Node* root)
{
	//p每次都指向节点的后继
	Node* p = root;
	//找到当前非线索化的最左节点
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
			//找到当前右边节点的最左节点
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