#include <stdio.h>               //用链表实现队列
#include <stdlib.h>
#include <malloc.h>

typedef struct NODE
{
	int n;
	struct NODE *pnext;
}node, * pnode;


typedef struct S
{
	pnode phead;
	pnode ptail;
}s, * ps;


void init(ps);
void en_queue(ps,int);
void out_queue(ps);
bool is_empty(ps);
void traverse(ps);



int main()
{
	s X;
	init(&X);
	en_queue(&X,5);
	en_queue(&X,3);
	en_queue(&X,7);
	en_queue(&X,9);
	traverse(&X);
	out_queue(&X);
	out_queue(&X);
	traverse(&X);
	en_queue(&X,22);
	traverse(&X);
	out_queue(&X);
	out_queue(&X);
//	out_queue(&X);
	traverse(&X);
	return 0;
}



void init(ps Y)
{
	Y->phead=(pnode)malloc(sizeof(node));
	if(Y->phead == NULL)
		exit(-1);
	Y->phead->pnext=NULL;
	Y->ptail=Y->phead;
}


void en_queue(ps Y,int val)
{
	pnode new_x=(pnode)malloc(sizeof(node));
	if(new_x == NULL)
		exit(-1);
	new_x->n=val;
	new_x->pnext=NULL;
	Y->ptail->pnext=new_x;
	Y->ptail=new_x;
}


bool is_empty(ps Y)
{
	if(Y->phead == Y->ptail)
		return true;
	else
		return false;
}


void out_queue(ps Y)
{
	if(is_empty(Y))
		printf("It is empty now\n");
	else
	{
		pnode r=Y->phead->pnext;
		Y->phead->pnext=r->pnext;
		if(Y->phead->pnext==NULL)         //我就觉得这里需要注意一下  就是只剩下一个没有val的头结点和一个尾节点指向的节点的时候   没有这一步的话无法判断 is_empty
			Y->ptail=Y->phead;
		free(r);
	}
}


void traverse(ps Y)
{
	if(is_empty(Y))
		printf("no values\n");
	else
	{
	pnode p=Y->phead->pnext;
	while(p!=Y->ptail)
	{
		printf("%d   ",p->n);
		p=p->pnext;
		
	}
	printf("%d",Y->ptail->n);
	printf("\n");
	}
}