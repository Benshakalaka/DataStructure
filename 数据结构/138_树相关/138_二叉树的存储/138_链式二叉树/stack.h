#ifndef STACK_H										//这个栈头函数的目的是为了实现非递归遍历
#define STACK_H
#include <stdio.h>                  
#include <malloc.h>
#include <stdlib.h>
#include "head.h"



typedef struct subject 
{
	BiTree data;
	struct subject *pnext;
}node,* pnode;



typedef struct First 
{
	pnode ptop;
	pnode pbottom;
}s,* ps;




void init(ps S)									//初始化
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


void push(ps S,BiTree val)						//入栈					           
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

bool empty(ps S)							//是否为空
{
	if(S->ptop==S->pbottom)
		return true;
	else
		return false;
}







void pop(ps S,BiTree &e)								//出栈
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



void clear(ps S)						//清空
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


bool Gettop(ps S,BiTree &e)
{
	if(!empty(S))
	{
		e = S->ptop->data;
		return true;
	}
	return false;
}

#endif
/*
* 　　　┏┓　　　┏┓
* 　　┏┛┻━━━┛┻┓
* 　　┃　　　　　　　┃
* 　　┃　　　━　　　┃
* 　　┃　┳┛　┗┳　┃
* 　　┃　　　　　　　┃
* 　　┃　　　┻　　　┃
* 　　┃　　　　　　　┃
* 　　┗━┓　　　┏━┛
* 　　　　┃　　　┃神兽保佑
* 　　　　┃　　　┃代码无BUG！
* 　　　　┃　　　┗━━━┓
* 　　　　┃　　　　　　　┣┓
* 　　　　┃　　　　　　　┏┛
* 　　　　┗┓┓┏━┳┓┏┛
* 　　　　　┃┫┫　┃┫┫
* 　　　　　┗┻┛　┗┻┛
* ━━━━━━神兽出没━━━━━━
*/