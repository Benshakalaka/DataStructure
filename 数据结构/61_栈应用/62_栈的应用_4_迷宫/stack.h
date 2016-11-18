#ifndef STACK_H
#define STACK_H
#include <stdio.h>                  
#include <malloc.h>
#include <stdlib.h>

enum {N,Y};
typedef int Direction;

typedef struct
{
	int x,y;
}position;

typedef struct
{
	position posi;				//点在矩阵中的位置
	Direction dire[4];			//分别为上、下、左、右
}Node,*pNode;

typedef struct subject 
{
	pNode data;
	struct subject *pnext;
}node,* pnode;

typedef struct First 
{
	pnode ptop;
	pnode pbottom;
}s,* ps;




void init(ps S)               
{
	S->ptop=(pnode)malloc(sizeof(node));
	if(NULL == S->ptop)
	{
		printf("FALE\n");
		exit(1);
	}
	S->ptop->pnext=NULL;
	S->pbottom=S->ptop;
}


void push(ps S,pNode val)						           
{
	pnode newx=(pnode)malloc(sizeof(node));
	if(NULL == newx)
	{
		printf("FALE\n");
		exit(1);
	}
	newx->data=val;
	newx->pnext=S->ptop;
	S->ptop=newx;
}

bool empty(ps S)            
{
	if(S->ptop==S->pbottom)
		return true;
	else
		return false;
}



void traverse(ps S)					
{
	if(empty(S))
		return;
	else
	{
		pnode p;
		p=S->ptop;
		while(p!=S->pbottom)
		{
			printf("(%d,%d)\n",p->data->posi.x,p->data->posi.y);
			p=p->pnext;
		}
		putchar('\n');
	}
}




void pop(ps S,pNode &e)				         
{
	if(empty(S))
		return;
	else
	{
	pnode r;
	r=S->ptop;
	S->ptop=r->pnext;
	e = r->data;
	free(r);
	}
}

void Gettop(ps S,pNode &e)
{
	e = S->ptop->data;
}

void clear(ps S)                 
{
	pnode p;
	pnode q;
	p=S->ptop;
	while(p != S->pbottom)
	{
		q=p->pnext;
		free(p);
		p=q;
	}
	S->ptop=S->pbottom;
}


#endif