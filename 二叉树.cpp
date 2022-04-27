#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_op 30

typedef struct node
{
	struct node* right;
	struct node* left;
	int val;
}node;

typedef struct tree
{
	node* root;
	//二叉树的节点个数
	int n;
}tree;

node* getnewnode(int val)
{
	node* n = (node*)malloc(sizeof(node));
	n->val = val;
	n->left = n->right = NULL;
	return n;
}

tree* getnewtree()
{
	tree* t = (tree*)malloc(sizeof(tree));
	t->n = 0;
	t->root = NULL;
	return t;
}

void clearnode(node* n)
{
	if (n == NULL) return;
	clearnode(n->right);
	clearnode(n->left);
	free(n);
}

void cleartree(tree* t)
{
	if (t == NULL) return;
	clearnode(t->root);
	free(t);
}

void output_node(node* root)
{	
	//递归输出
	if (root == NULL) return;
	printf("%d", root->val);
	if (root->left == NULL && root->right == NULL) return;
	printf("(");
	output_node(root->left);
	printf(",");
	output_node(root->right);
	printf(")");
}	
void output_tree(tree* t)
{
	printf("tree(%d)=", t->n);
	output_node(t->root);
	printf("\n");
}

//排序树，根节点的值小于右边，大于左边
//递归插入
node* insertnode(node* root, int val, int* tmp)
{	
	//若为空，则初始化一个节点
	if (root == NULL)
	{
		*tmp = 1;
		//每次getnewnode就相当于初始化一个节点
		return getnewnode(val);

	}
	if (root->val == val) return root;
	//若是比节点的值小，则插入在左边
	if (root->val > val) root->left = insertnode(root->left, val, tmp);
	else root->right = insertnode(root->right, val, tmp);
	return root;
}

void insert(tree* t, int val)
{
	//用于存储树的节点个数
	int tmp = 0;
	//递归插入
	t->root = insertnode(t->root, val, &tmp);
	t->n += tmp;
}

//前序遍历
void preordernode(node* n)
{
	if (n == NULL) return;
	printf(" %d", n->val);
	preordernode(n->left);
	preordernode(n->right);

}
void preorder(tree* t)
{
	printf("preorder:");
	preordernode(t->root);
	printf("\n");
}

void inordernode(node* n)
{
	if (n == NULL) return;
	inordernode(n->left);
	printf(" %d", n->val);
	inordernode(n->right);

}
void inorder(tree* t)
{
	printf("inorder:");
	preordernode(t->root);
	printf("\n");
}

void postordernode(node* n)
{
	if (n == NULL) return;
	postordernode(n->left);
	postordernode(n->right);
	printf(" %d", n->val);
}
void postorder(tree* t)
{
	printf("postorder:");
	postordernode(t->root);
	printf("\n");
}
int main()
{
	srand((unsigned int)time(NULL));
	tree* t = getnewtree();
	for (int i = 0; i < Max_op; i++)
	{
		int val = rand() % 100;
		insert(t, val);
		output_tree(t);
	}
	//三种遍历方式
	preorder(t);
	inorder(t);
	postorder(t);
	return 0;
}