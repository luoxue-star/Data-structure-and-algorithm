#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_op 30

typedef struct stack
{
	int* data;
	int top, size;
}stack;

stack* init(int n)
{
	stack* s = (stack*)malloc(sizeof(stack));
	s->data = (int*)malloc(sizeof(int) * n);
	s -> size = n;
	//因为每次压栈top都要加1，所以这里初始化为-1
	s -> top = -1;
	return s;
}

void clear(stack* s)
{
	if (s == NULL) return;
	free(s->data);
	free(s);
}

int empty(stack* s)
{
	return s->top == -1;
}

//查看栈顶元素
int top(stack* s)
{
	if (empty(s)) return 0;
	return s->data[s->top];
}

int push(stack* s, int val)
{
	if (s == NULL) return 0;
	if (s->size == s->top + 1) return 0;
	s->data[++s->top] = val;
	return 1;
}

int pop(stack* s)
{
	if (s == NULL) return 0;
	if (empty(s)) return 0;
	s->top -= 1;
	return 1;
}

void output(stack* s)
{
	printf("stack(%d)= [",s->top+1);
	for (int i = s->top; i >= 0; i--)
	{
		printf("%d ", s->data[i]);
	}
	printf("]\n");
}
int main()
{
	stack* s = init(Max_op);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < Max_op; i++)
	{
		int op = rand() % 2;
		int val = rand() % 100;
		switch (op)
		{
		case 0:
			push(s, val);
			printf("%d 入栈\n", val);
			break;
		case 1:
			pop(s);
			printf("出栈\n");
			break;
		default:
			break;
		}
		output(s);
	}
	return 0;
}