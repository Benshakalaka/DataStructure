#include <stdio.h>                   //简单的 栈 操作 (不明白那个类似头结点的东东要释放吗)
#include <malloc.h>
#include <stdlib.h>



typedef struct subject            //节点类型
{
	int data;
	struct subject *pnext;
}node,* pnode;



typedef struct First               //包含最顶端节点（不断变化） 和最低端节点（不变）
{
	pnode ptop;
	pnode pbottom;
}s,* ps;


void init(ps);                //初始化    与链表的头结点类似  便于对栈的操作
void traverse(ps);             //遍历  （不改变top）
bool empty(ps);                //判断为空  （遍历 和 出栈要用到）
void push(ps,int);               //入栈    
void pop(ps,int *);               //出栈
void clear(ps);                        //清空



int main(void)
{
	s X;
	int val;
	init(&X);
	push(&X,1);
	push(&X,3);
	push(&X,5);
	push(&X,7);
	traverse(&X);
	pop(&X,&val);
	printf("%d has been delete\n",val);
	traverse(&X);
	clear(&X);
	traverse(&X);
	return 0;
}



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


void push(ps S,int val)						               //入栈    
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


void traverse(ps S)							//遍历  （不改变top）
{
	if(empty(S))
	{
		printf("it is empty\n");
		exit(1);
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


bool empty(ps S)                //判断为空  （遍历 和 出栈要用到）
{
	if(S->ptop==S->pbottom)
		return true;
	else
		return false;
}



void pop(ps S,int *val)				               //出栈
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
