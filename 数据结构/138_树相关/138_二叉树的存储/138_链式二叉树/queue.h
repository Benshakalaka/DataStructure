#ifndef QUEUE_H						//这个头文件是为了实现层序遍历
#define QUEUE_H
#include "head.h"
#include <stdio.h>               //用链表实现队列
#include <stdlib.h>
#include <malloc.h>

typedef struct NODE
{
	BiTree n;
	struct NODE *pnext;
}nod, * pnod;


typedef struct S
{
	pnod phead;
	pnod ptail;
}ss, * pss;


void init(pss);
void en_queue(pss,BiTree);
void out_queue(pss,BiTree &);
bool is_empty(pss);





void init(pss Y)
{
	Y->phead=(pnod)malloc(sizeof(nod));
	if(Y->phead == NULL)
		exit(-1);
	Y->phead->pnext=NULL;
	Y->ptail=Y->phead;
}


void en_queue(pss Y,BiTree val)
{
	pnod new_x=(pnod)malloc(sizeof(nod));
	if(new_x == NULL)
		exit(-1);
	new_x->n=val;
	new_x->pnext=NULL;
	Y->ptail->pnext=new_x;
	Y->ptail=new_x;
}


bool is_empty(pss Y)
{
	if(Y->phead == Y->ptail)
		return true;
	else
		return false;
}


void out_queue(pss Y,BiTree & T)
{
	if(is_empty(Y))
		printf("It is empty now\n");
	else
	{
		pnod r=Y->phead->pnext;
		Y->phead->pnext=r->pnext;
		if(Y->phead->pnext==NULL)         //我就觉得这里需要注意一下  就是只剩下一个没有val的头结点和一个尾节点指向的节点的时候   没有这一步的话无法判断 is_empty
			Y->ptail=Y->phead;
		T = r->n;
		free(r);
	}
}


#endif