#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include "stack.h"
//#include "btnode.h"
#define END '#'

typedef char Elemtype;

typedef struct BtNode 
{
	Elemtype data;
	struct BtNode *liftchild;
	struct BtNode *rightchild;

}BtNode;

#define Elem BtNode
#define MAXSIZE 50	

typedef struct MyStack
{
	Elem *data[MAXSIZE];
	int top;
	int size;
}MyStack;

typedef struct Quque
{
	Elem *data[MAXSIZE];
	int front;
	int end;
}Quque;

Quque * creatquque()
{
	Quque *tmp = (Quque *)malloc(sizeof (Quque) *1);
	if(tmp == NULL)
	{
		printf("error: Quque creat error!\n");
		return NULL;
	}
	memset(tmp , 0, sizeof(*tmp));

}

int ifempty_quque(Quque *head)
{
	if(head == NULL)
	{
		printf("quque is error\n");
		return 1;
	}
	return head->front == head->end;

}

int iffull_quque(Quque * head)
{
	if(head == NULL)
	{
		printf("error: Quque is error\n");
		return 1;
	}
	return (head->end+1)%MAXSIZE == head->front;
}

void pop_quque(Quque *head, Elem **data)
{
	if(head == NULL)
	{
		return ;	
	}
	if(ifempty_quque(head) == 0)
	{
		*data = (head->data)[head->front];
		head->front = (head->front + 1) % MAXSIZE;
	}
	else
	{
		printf("quque is empty\n");
		return ;
	}
}
void push_quque(Quque *head, Elem *data)
{
	if(head == NULL)
	{
		return ;

	}
	if(iffull_quque(head) == 0)
	{
		(head->data)[head->end] = data;
		head->end = (head->end + 1) % MAXSIZE;
	}
	else
	{
		printf("quque is full\n");
		return ;
	}
}
MyStack *creatstack()
{
	MyStack *p = (MyStack * )malloc(sizeof(MyStack) * 1);
	if(p == NULL)
	{
		exit (-1);
	}
	memset(p, 0, sizeof(*p));
	p-> size = MAXSIZE;
	return p;

}

int ifempty(MyStack *p)
{

	if(p == NULL)
	{
		return 1;
	}
	return p->top == 0;
}

int iffull(MyStack *p)
{
	if(p == NULL)
	{
		return 1;
	}
	return p->top == p->size;

}

void push(MyStack *p , Elem *data)
{
	if(p == NULL)
	{
		return ;

	}

	if(iffull(p))
	{
		printf("error:this stack is full\n");
		return ;
	}
	(p->data)[p->top] = data;
	(p->top)++;


}

void pop(MyStack *p, Elem **data)
{
	if(p == NULL)
	{
		return ;
	}
	if(ifempty(p))
	{
		printf("error:this stack is empty\n");
		return ;
	}
	*data = ((*p).data)[--((*p).top)];
}

static BtNode* buynode()
{
	BtNode *tmp = (BtNode *)malloc(sizeof(BtNode) * 1);
	if (tmp == NULL)
	{
		exit (-1);
	}
	memset(tmp, 0, sizeof (BtNode));
	return tmp;

}

BtNode* creattree()
{
	char data = '#';
	BtNode *root = NULL;
	data = getchar() ;
	if(data == '#')
	{
		return NULL;
	}
	
	else
	{
		root = buynode();
		root -> data = data;
		root -> liftchild = creattree();
		root -> rightchild = creattree();
	}
	return root;

}
void printtree(BtNode * Node)
{

	if(Node == NULL)
	{
		return ;
	}
	printtree(Node -> liftchild);
	printf("%c  ", Node-> data );
	printtree(Node -> rightchild);
}

void isprinttree( BtNode * root)
{
	if(root == NULL )
	{
		return ;
	}
	printf("is recursion: ");
	printtree( root);
	putchar('\n');
}

void printtree2(BtNode *Node)
{
	MyStack *head = creatstack();
	while(Node != NULL || ifempty(head) == 0)
	{
		while(Node != NULL)
		{
			push(head, Node);
			Node = Node->liftchild;
		}
		pop(head, &Node);
		printf("%c  ", Node->data);
		Node = Node->rightchild;
	}

}

void isprinttree2(BtNode *root)
{
	if(root == NULL)
	{
		return ;

	}
	printf("not recursion: ");
	printtree2(root);
	putchar('\n');
	
}
void arrangement(BtNode *node)
{
	Quque *head = creatquque();
	while(node != NULL || ifempty_quque(head) == 0)
	{
		if(node != NULL)
		{
			printf("%c  ", node ->data);
			push_quque(head, node->liftchild);
			
		
			push_quque(head, node->rightchild);
		}
		pop_quque(head, &node);
	}
}

void arrangement_print(BtNode *root)
{
	if(root == NULL)
	{
		return ;
	}
	printf("arrangement:");
	arrangement(root);
	putchar('\n');
}

void high(BtNode *root, int *cont, int *tmp)
{
	if(root != NULL)
	{
		(*cont)++;
		high(root->liftchild, cont, tmp);
		high(root->rightchild, cont, tmp);
		(*cont) --;
	}
	if(*tmp < *cont)
	{
		*tmp = *cont;
	}

}

int high_tree(BtNode *root)
{
	if(root == NULL)
	{
		printf("root is error\n");
		return 0;
	}
	int cont = 0;
	int tmp = 0;
	high(root, &cont, &tmp);
	return tmp;

}

void number(BtNode *root, int *count)
{
	if(root != NULL)
	{
		(*count)++;
		number(root->liftchild, count);
		number(root->rightchild, count);
	}
}

int node_number(BtNode *root)
{
	if(root == NULL)
	{
		printf("root is error\n");
		return 0;
	}
	int count = 0;
	number(root, &count);
	return count;
}

void leaf(BtNode *root, int *count)
{
	if(root != NULL)
	{
		if(root->liftchild == NULL && root->rightchild == NULL)
		{
			(*count)++;
		}
		leaf(root->liftchild, count);
		leaf(root->rightchild, count);
	}
}

int leaf_number(BtNode *root)
{
	if(root == NULL)
	{
		printf("root is error\n");
		return 0;
	}
	int count = 0;
	leaf(root, &count);
	return count;
}

void change(BtNode * root)
{
	if(root != NULL)
	{
		BtNode *tmp = NULL;
		tmp = root->liftchild;
		root->liftchild = root->rightchild;
		root->rightchild = tmp;
		change(root->liftchild);
		change(root->rightchild);
	}
}

void change_child(BtNode *root)
{
	if(root == NULL)
	{
		printf("root is error\n");
		return ;
	}
	change(root);

}


int main()
{
	BtNode * root = creattree();
	isprinttree(root);
	isprinttree2(root);
	arrangement_print(root);
	int i = 0;
	i = high_tree(root);
	printf("the tree high: %d\n", i);
	i = node_number(root);
	printf("the node number: %d\n", i);
	i = leaf_number(root);
	printf("leaf number: %d\n", i);
	change_child(root);
	printf("change_child->");
	isprinttree(root);
	return 0;
}
