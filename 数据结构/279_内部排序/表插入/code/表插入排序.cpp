//本程序的数组0号元素不用
#include <stdio.h>				//改变数组存储的方式 使用静态链表
#include <malloc.h>

#define SIZE 100				//限定

typedef struct
{
	int key;					//记录项
	int next;					//指针项
}SLNode;
typedef struct
{
	SLNode r[SIZE];			//0号为头结点
	int length;				//链表当前长度
}SLinkListType;				//静态链表类型名称

void Init(SLinkListType* &SLL)
{
	SLL = NULL;
}
void Create(SLinkListType* &SLL,int *a,int len)				//1、2、3、...、len
{
	SLL = (SLinkListType*)malloc(sizeof(SLinkListType));
	SLL->length = len;
	SLL->r[0].key = 99999;
	SLL->r[0].next = 1;
	SLL->r[1].key = a[1];
	SLL->r[1].next = 0;
	int i,p,q;
	for(i=2;i<=len;i++)											//相当于静态链表的插入
	{
		p = 0;
		q = SLL->r[p].next;
		while(q!=0 && a[i] >= SLL->r[q].key)
		{
			p = q;
			q = SLL->r[q].next;
		}
		SLL->r[i].key = a[i];
		SLL->r[i].next = SLL->r[p].next;
		SLL->r[p].next = i;
	}
}

void Swap(SLNode &a,SLNode &b)
{
	SLNode temp;
	temp = a;
	a = b;
	b = temp;
}
void Arrange(SLinkListType* &SLL)
//根据静态链表SL中各节点的指针值调整记录位置，使得SL中记录按关键字非递减有序顺序排列
{
	int temp = SLL->r[0].next;
	int p,i=1;
	for(i=1;i<=SLL->length;i++)							//注意---这里不需要第8次调整 一旦有了第八次 就不正确了 前七次都已经把每一个数放到正确的位置了，最后以为当然也已经归位了
	{
		p = SLL->r[temp].next;
		if(temp!=i)												//如果已经在要求的位置上了就不需要动  增加一个if判断 可以减少一些不必要的步骤
		{
			Swap(SLL->r[i],SLL->r[temp]);
			SLL->r[i].next = temp;		//交换后使得可以通过第i个节点间接得到想要得到的点
		}
		temp = p;
		while(temp<=i)										//这里注意了，不是if就可以的 需要用到while切记！！！！！！
			temp = SLL->r[temp].next;
	}
}

int main()
{
	int a[9]={0,49,38,65,97,76,13,27,52};			//0号不用
	SLinkListType *SLL;
	Init(SLL);
	Create(SLL,a,8);	
	int i;
	for(i=0;i<=8;i++)
		printf("%d  %d\n",SLL->r[i].key,SLL->r[i].next);
	puts("");
	Arrange(SLL);
	for(i=0;i<=8;i++)
		printf("%d  %d\n",SLL->r[i].key,SLL->r[i].next);
	puts("");
	return 0;
}