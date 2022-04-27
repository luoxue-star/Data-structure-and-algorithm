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
	//�������Ľڵ����
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
	//�ݹ����
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

//�����������ڵ��ֵС���ұߣ��������
//�ݹ����
node* insertnode(node* root, int val, int* tmp)
{	
	//��Ϊ�գ����ʼ��һ���ڵ�
	if (root == NULL)
	{
		*tmp = 1;
		//ÿ��getnewnode���൱�ڳ�ʼ��һ���ڵ�
		return getnewnode(val);

	}
	if (root->val == val) return root;
	//���ǱȽڵ��ֵС������������
	if (root->val > val) root->left = insertnode(root->left, val, tmp);
	else root->right = insertnode(root->right, val, tmp);
	return root;
}

void insert(tree* t, int val)
{
	//���ڴ洢���Ľڵ����
	int tmp = 0;
	//�ݹ����
	t->root = insertnode(t->root, val, &tmp);
	t->n += tmp;
}

//ǰ�����
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
	//���ֱ�����ʽ
	preorder(t);
	inorder(t);
	postorder(t);
	return 0;
}