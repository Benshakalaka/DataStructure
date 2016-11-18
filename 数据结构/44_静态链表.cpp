#include <stdio.h>								//静态链表以数组形式 root【0】相当于头结点 cur=1；为第一个节点 cur=0;为最后一个节点
#include <malloc.h>								//为了知道哪些节点没被用过或是被丢弃了以便于以后使用 所以定义一个space来存储这些备用的
#include <stdlib.h>								//这里的节点都可以用一个整型下标实现
typedef struct Student
{
	int data;
	int cur;
}S,*pS;

pS Init(int n)
{
	pS space = (pS)malloc(sizeof(S) * n);		//初始化将所有点设为空余space里的点 要用则调出
	for(int i=0;i<n-1;i++)
		space[i].cur = i+1;
	space[n-1].cur = 0;							//最后一个是0 说明空余的没有的时候
	return space;
}

int Canbeused(pS &space)				//提供一个可以使用的数组下标（即节点）
{
	int i = space[0].cur;				//如果i是0 那说明没有空余的点可以用了 如果非0 那返回改点下标 
	if(i)
		space[0].cur = space[i].cur;	//并且让头结点指向下一个空余点 以便于下次再调用
	space[i].cur =0;					//先令该节点作为作为最后一个节点
	return i;
}

void recover(pS &space,int n)			//n表示要回收的下标
{
	space[n].cur = space[0].cur;		//将这个废弃的放在头结点下面 下次就用这个
	space[0].cur = n;
}

int Add(pS &space,int &X,int n)			//返回一个插入的位置 方便主函数里的操作 知道最后一个节点在哪里  X为某个链表的头结点
{
	int i=Canbeused(space); 
	if(i == 0)
	{
		printf("There is no space for %d!\n",n);
		return 0;
	}
	space[i].data = n;					//从space里分配出的节点先赋好值
	int j = space[X].cur;				//找出X中cur为0的即最后一个节点
	if(j==0)							//若是为空  则在头结点操作
	{
		space[X].cur = i;	
		return i;
	}
	while(1)						//不然  则在最后一个节点操作
	{
		if(space[j].cur == 0)
			break;
		j = space[j].cur;
	}
	space[j].cur = i;
	return i;
}

void traverse(pS &space,int X)			//遍历  从头结点到最后一个cur为0 的节点
{
	int i = space[X].cur;
	if(i == 0)
		printf("NO DATA!\n");
	while(i)
	{
		printf("%d  ",space[i].data);
//		printf("[ %d ] ",i);			//这里是方便看变化后的个点的下标是什么 是否被回收的有再被利用 是否如预期一样
		i = space[i].cur;
	}
	putchar('\n');
}


//这是个小题目 ：
//A链表和B链表  先输入A链表 之后将B链表中的数据放进A中 若A中有该数据 则删掉A中的与之相同的数据 否则把该数据插入A中(两个链表都是一个一个输入判断)
int main()
{
	int n;									//要在多长的数组上操作呢
	printf("How long do you want(a number at least 2)?\n");
	scanf("%d",&n);
	if(n < 2)
	{
		printf("Fuck...\n");
		exit(1);
	}
	pS Space = Init(n);						//初始化一个空闲的长度为n的数组
	int X = Canbeused(Space);				//给 X 一个头结点便于插在第一个  X作为A的头结点下标（不是0是头结点下标吗？不不不 0是整个空数组的头结点  这里的A是独立的）
	printf("Input the size of A and B\n");
	int a,b,i,k,rear;							//a：A长度；b：B长度；i：循环变量；k：输入变量；rear:X的最后一个节点
	scanf("%d%d",&a,&b);


	printf("NOW, A first:\n");				//A建立
	for(i=0;i<a;i++)
	{
		scanf("%d",&k);
		rear =Add(Space,X,k);					//rear的位置
	}
	printf("Now, your A:\n");
	traverse(Space,X);


	
	int prev,curr;
	printf("Then B:\n");					//输入B
	for(i=0;i<b;i++)
	{
		curr = Space[X].cur;
		scanf("%d",&k);
		while(curr && k!=Space[curr].data)				//若退出则分为两种情况  一个是找到相同的一个是没找到
		{
			prev = curr;					//保存该点和该点的前面一个点的下标 方便找到相同后的删除操作
			curr = Space[curr].cur;
		}
		if(curr == 0 )
			rear=Add(Space,X,k);				//没找到  插入
		else										//找到了
		{
			Space[prev].cur = Space[curr].cur;	//删除
			recover(Space,curr);						//回收
			if(curr == rear) rear = prev;			//如果正好是最后一个 那rear就要换位置了
		}
	}
	printf("Now,your A:\n");
	traverse(Space,X);
	free(Space);
	return 0;
}
