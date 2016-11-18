#include <stdio.h>               //初级静态循环队列        这个程序里有两个地方需要考虑 一个是如何循环 一个是如何判断为空为满
#include <malloc.h>            
#include <stdlib.h> 
typedef struct Array                     //构建数组所需的元素
{
	int *p;
	int front;
	int rear;
}Arr,* pArr;


bool init(pArr,int);        // 初始化数组   新建数组分配内存
bool is_empty(pArr);        //为空
bool is_full(pArr,int);       //为满
bool en_queue(pArr,int,int);    // 入队
bool out_queue(pArr,int);       //出队
void traverse(pArr,int);             //遍历



int main()
{
	int len=6;
	Arr X;
	init(&X,len);
	en_queue(&X,2,len);
	en_queue(&X,4,len);
	en_queue(&X,5,len);
	en_queue(&X,6,len);
	traverse(&X,len);
	out_queue(&X,len);
	traverse(&X,len);
	en_queue(&X,20,len);
	traverse(&X,len);
	out_queue(&X,len);
	out_queue(&X,len);
	out_queue(&X,len);
	out_queue(&X,len);
	traverse(&X,len);
	free(X.p);
	return 0;
}


bool init(pArr S,int l)
{
	S->p=(int *)malloc(sizeof(int)*l);
	if(S!=NULL)
	{	S->front=S->rear=0;
		return true;
	
	}
	else
		return false;
}

bool is_empty(pArr S)              //为空
{
	if(S->front==S->rear)
		return true;
	else
		return false;
}

bool is_full(pArr S,int l)					//为满
{
	if(((S->rear+1)%l)==S->front)
		return true;
	else
		return false;
}

bool en_queue(pArr S,int val,int l)
{
	if(is_full(S,l))
	{
		printf("It is full now!\n");
		return false;
	}
	else
	{
		S->p[S->rear]=val;
		S->rear=(S->rear+1)%l;
		return true;
	}
}

bool out_queue(pArr S,int l)
{
	if(is_empty(S))
	{
		printf("It is empty now!\n");
		return false;
	}
	else
	{
		S->front=(S->front+1)%l;
		return true;
	}

}

void traverse(pArr S,int l)
{
	if(is_empty(S))
		printf("no values\n");
	else
	{
		int i;
		for(i=S->front;i!=S->rear;i=(i+1)%l)
			printf("%d   ",S->p[i]);
		putchar('\n');
	}
}