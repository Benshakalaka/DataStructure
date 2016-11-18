#include <stdio.h>                 
#include <malloc.h>
#include <stdlib.h>



typedef struct subject            //节点类型
{
	double data;
	struct subject *pnext;
}node,* pnode;



typedef struct First               //包含最顶端节点（不断变化） 和最低端节点（不变）
{
	pnode ptop;
	pnode pbottom;
}s,* ps;






void init(ps S)               //初始化    与链表的头结点类似  便于对栈的操作
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


void push(ps S,double val)						               //入栈    
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



void pop(ps S,double *val)				               //出栈
{
	if(empty(S))
		exit(1);
	else
	{
	pnode r;
	r=S->ptop;
	S->ptop=r->pnext;
	*val=r->data;
	free(r);
	}
}



void clear(ps S)                        //清空
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
