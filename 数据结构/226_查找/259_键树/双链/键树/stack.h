//以下内容取自   /数据结构与算法/3简单的 栈.cpp
#ifndef STACK_H
#define STACK_H                 
#include <malloc.h>
#include <stdio.h>
#include "head.h"


typedef struct subject 
{
	DLTree data;
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
	if(0 == S->ptop)
		return;
	S->ptop->pnext=0;
	S->pbottom=S->ptop;
}


void push(ps S,DLTree val)						           
{
	pnode newx=(pnode)malloc(sizeof(node));
	if(0 == newx)
		return;
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


void pop(ps S,DLTree &e)				         
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