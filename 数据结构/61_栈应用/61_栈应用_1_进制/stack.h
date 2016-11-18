//以下内容取自   /数据结构与算法/3简单的 栈.cpp
#ifndef STACK_H
#define STACK_H
#include <stdio.h>                  
#include <malloc.h>
#include <stdlib.h>



typedef struct subject 
{
	int data;
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


void push(ps S,int val)						           
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
	{
		printf("it is empty\n");
		return;
	}
	else
	{
		pnode p;
		p=S->ptop;
		while(p!=S->pbottom)
		{
			printf("%d  ",p->data);
			p=p->pnext;
		}
		putchar('\n');
	}
}




void pop(ps S,int &e)				         
{
	if(empty(S))
		return;
	else
	{
	pnode r;
	r=S->ptop;
	S->ptop=r->pnext;
	e=r->data;
	free(r);
	}
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