#include <stdio.h>							//这里主要通过一组地址连续的存储单元依次自上而下 从左至右存储完全二叉树的节点
#include <math.h>					//建立在完全二叉树的基础上 有一些存在的必然性质 比如某行的元素个数  第几个数的准确位置（line,order）
#include <stdlib.h>
#define MAXSIZE 100							//既然是顺序的存储  那就会有一个MAX				存储方式可看本文件夹的图片

typedef int SqBiTree[MAXSIZE];				//SqBiTree【0】用于存储根节点

struct position										//在函数中用到  用于定位
{
	int level;					//所在层
	int order;					//所代表该行的序号（按照完全二叉树的序号）
};

void InitBiTree(SqBiTree &T);						//构造空二叉树
void CreateBiTree(SqBiTree &T);						//按层序次序输入二叉树中节点的值 构造顺序存储二叉树
bool BiTreeEmpty(SqBiTree T);						//若二叉树为空 则true 否则false
int BiTreeDepth(SqBiTree T);						//二叉树的深度
bool Root(SqBiTree,int &);								//当不空，用e返回T的根
int Value(SqBiTree T,struct position e);							//返回位置e的节点的值
bool Assign(SqBiTree T,struct position e,int value);							//给处于位置e的节点赋值
int Parent(SqBiTree,int e);							//若e是T的非根节点  则返回双亲 否则返回空
int LeftChild(SqBiTree T,int e);						//返回e的左孩子 若无 则返回空
int RightChild(SqBiTree T,int e);							
int LeftSibling(SqBiTree T,int e);						//返回e的左兄弟 若e是T的左孩子或无左兄弟 则返回空
int RightSibling(SqBiTree T,int e);						//返回e的右兄弟 若e是T的右孩子或无右兄弟 则返回空
void Move(SqBiTree &T,SqBiTree q,int i,int j);								//把从q的j节点开始的子树移为从T的i节点开始的子树
void InsertChild(SqBiTree &T,int p,int b,SqBiTree c);						//根据LR为0或1 插入c为T中p节点的左或者右子树 p节点原有的左或者右子树则成为c的右子树
void DeleteChild(SqBiTree &T,position e);						//根据LR为1或0 删除T中p所指节点的左或者右子树
void PreTreaverse(SqBiTree T,int e);								//先序准备
void PreOrderTreaverse(SqBiTree T);				//先序遍历
void InTreaverse(SqBiTree T,int e);								//中序准备
void InOrderTraverse(SqBiTree T);					//中序遍历
void PostTraverse(SqBiTree T,int e);								//后序准备
void PostOrderTraverse(SqBiTree T);				//后序遍历
void LevelOrderTraverse(SqBiTree T);				//层序遍历二叉树
void Print(SqBiTree T);
void ClearBiTree(SqBiTree T);								//清空树


int main()
{
	bool i;
	int j,e;
	position p;
	SqBiTree T,s;
	InitBiTree(T);
	CreateBiTree(T);
	printf("建立二叉树后，树空否？ %d (1：是 0：否) 树的深度= %d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i = Root(T,e);
	if(i)
		printf("树的根为：%d\n",e);
	else
		printf("空树\n");
	printf("层序遍历二叉树：\n");
	LevelOrderTraverse(T);
	printf("先序遍历二叉树：\n");
	PreOrderTreaverse(T);
	printf("中序遍历二叉树：\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树：\n");
	PostOrderTraverse(T);
	printf("Input the exact one that you want to remedy : \n");
	scanf("%d%d",&p.level,&p.order);
	e = Value(T,p);
	printf("the previous value is %d\nPleasae input the new value:\n",e);
	scanf("%d",&e);
	Assign(T,p,e);
	printf("先序遍历二叉树：\n");
	PreOrderTreaverse(T);
	printf("该节点的双亲为%d,左右孩子分别为%d，%d,左右兄弟分别为%d，%d\n\n",Parent(T,e),LeftChild(T,e),RightChild(T,e),LeftSibling(T,e),RightSibling(T,e));
	Print(T);
	InitBiTree(s);
	printf("Set up a new tree without right son\n");
	CreateBiTree(s);
	printf("将s插入到T中，请输入T中树s的双亲节点，s为左(0)或者右(1)节点\n");
	scanf("%d%d",&e,&j);
	InsertChild(T,e,j,s);
	printf("层序输出T\n");
	Print(T);
	printf("删除子树，请输入待删除节点（整个子树）的层号 本层序号\n");
	scanf("%d%d",&p.level,&p.order);
	DeleteChild(T,p);
	Print(T);
	ClearBiTree(T);
	printf("二叉树已被清除？ %d  树的深度= %d \n",BiTreeEmpty(T),BiTreeDepth(T));
	i = Root(T,e);
	if(i)
		printf("根为= %d\n",e);
	else
		printf("无根\n");
	return 0;
}






void InitBiTree(SqBiTree &T)						//构造空二叉树
{
	for(int i=0;i<MAXSIZE;i++)
		T[i] = NULL;
}

void CreateBiTree(SqBiTree &T)						//按层序次序输入二叉树中节点的值 构造顺序存储二叉树
//这里所存的是整数  即数据类型是整数数组
{
	printf("you can input line after line and one by one: (0 as NIL & 999 as the end)\n");
	int i = 0;
	while(1)
	{
		scanf("%d",&T[i]);
		if(T[i] == 999)
			break;
		if(i!=0 && T[i]!=0 && T[(i-1)/2]==0)
			exit(1);
		i++;
	}
	while(i<MAXSIZE)
		T[i++] = 0;
}

bool BiTreeEmpty(SqBiTree T)						//若二叉树为空 则true 否则false
{
	if(T[0] == NULL)										//只需要判断根节点是否存在
		return true;
	return false;
}

int BiTreeDepth(SqBiTree T)						//二叉树的深度
{
	for(int i=MAXSIZE-1;i>=0 && (!T[i]);i--);					//得到在顺序数组中的位置
	i++;															//因为是从0开始的  所以加一后便于计算
	for(int j=0;pow(2,j)<=i;j++);										//通过位置得到深度
	return j;
}

bool Root(SqBiTree T,int &e)								//当不空，用e返回T的根
{
	if(BiTreeEmpty(T))
		return false;
	e = T[0];
	return true;
}

int Value(SqBiTree T,struct position e)							//返回位置e的节点的值
{
	int m = (int)pow(2,e.level-1)+e.order-2;					//整个顺序表是从0开始的 所以写方程式的时候要仔细  举例验证
	return T[m];
}

bool Assign(SqBiTree T,struct position e,int value)							//给处于位置e的节点赋值
{														//给赋值  相当于改变二叉树了  所以要考虑的地方比返回（上个函数）要多
	int m = (int)pow(2,e.level-1)+e.order-2;					//找到相应的位置	
	if(T[(m+1)/2-1]==NULL && value!=0)					//判断如果parent节点是空的并且value不为空 那么这个节点的存在是不合法的
		return false;
	else if(value==0 && (T[2*m+1]!=NULL || T[2*m+2]!=NULL))		//判断如果value为空 那么这个节点下面的两个节点如果是存在的话 就是不合理的
		return false;
	T[m] = value;
	return true;
}

int Parent(SqBiTree T,int e)							//若e是T的非根节点  则返回双亲 否则返回空
{
	if(T[0]==e)									//既然是返回parent节点 那就要考虑是否为根节点
		return NULL;
	int i;
	for(i=1;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==e)
			return T[(i+1)/2-1];
	return NULL;							//找不到
}

int LeftChild(SqBiTree T,int e)						//返回e的左孩子 若无 则返回空
{
	if(T[0]==0)									//考虑是否为空树
		return NULL;
	int i;
	for(i=1;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==e)
			return T[2*i+1];
	return NULL;		
}

int RightChild(SqBiTree T,int e)						//返回e的右孩子 若无 则返回空
{
	if(T[0]==0)									//考虑是否为空树
		return NULL;
	int i;
	for(i=1;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==e)
			return T[2*i+2];
	return NULL;
}

int LeftSibling(SqBiTree T,int e)						//返回e的左兄弟 若e是T的左孩子或无左兄弟 则返回空
{
	if(T[0]==0)									//考虑是否为空树
		return NULL;
	int i;
	for(i=1;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==e && e%2==0)						//考虑是否为右节点
			return T[i-1];
	return NULL;
}

int RightSibling(SqBiTree T,int e)						//返回e的右兄弟 若e是T的右孩子或无右兄弟 则返回空
{
	if(T[0]==0)									//考虑是否为空树
		return NULL;
	int i;
	for(i=1;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==e && e%2!=0)						//考虑是否为右节点
			return T[i+1];
	return NULL;
}

void Move(SqBiTree &T,SqBiTree q,int i,int j)								//把从q的j节点开始的子树移为从T的i节点开始的子树
{
	if(q[j]==NULL)
		return;
	T[i] = q[j];
	q[j] = NULL;
	Move(T,q,2*i+1,2*j+1);
	Move(T,q,2*i+2,2*j+2);
}

void InsertChild(SqBiTree &T,int p,int b,SqBiTree c)			//根据b为0或1 插入c为T中p节点的左或者右子树 p节点原有的左或者右子树则成为c的右子树
{			
	int i;
	for(i=0;i<MAXSIZE;i++)							//依次寻找
		if(T[i]==p)
			break;
	if(i==MAXSIZE)
		return;
	i = 2*i+1+b;
	/*if(T[i]!=NULL)						//书上是将这个点移动为这个点原本位置的右子节点  但如果这个位置已经有了呢 有点巧合  所以我这里就是直接溢出那个原本存在的点 还有一种办法就是不允许在有点的地方插入  除非先删除
		Move(T,T,2*i+2,i);			// 将T的i节点移到i的右子节点上*/
	Move(T,c,i,0);
}

int count(int n)									//作用是直至某行所有节点数
{
	int sum=0;
	for(int i=n-1;i>=0;i--)
		sum+=(int)pow(2,i);
	return sum;
}
void DeleteChild(SqBiTree &T,position e)						// 删除T中e所指节点的左或者右子树  玉树上略有不同的功能
{
	int m = (int)pow(2,e.level-1)+e.order-2;
	if(!T[m])
		return;
	T[m] = NULL;
	e.level ++;
	e.order = 2*m+1-count(e.level-1)+1;
	DeleteChild(T,e);
	e.order = 2*m+2-count(e.level-1)+1;
	DeleteChild(T,e);
}

void PreTreaverse(SqBiTree T,int e)								//先序准备
{
	if(T[e])
		printf("%d ",T[e]);
	if(T[2*e+1])
		PreTreaverse(T,2*e+1);
	if(T[2*e+2])
		PreTreaverse(T,2*e+2);
}
void PreOrderTreaverse(SqBiTree T)				//先序遍历
{
	if(!T[0])
		return;
	PreTreaverse(T,0);
	puts("");
}

void InTreaverse(SqBiTree T,int e)								//中序准备
{
	if(T[2*e+1])
		InTreaverse(T,2*e+1);
	if(T[e])
		printf("%d ",T[e]);
	if(T[2*e+2])
		InTreaverse(T,2*e+2);
}
void InOrderTraverse(SqBiTree T)					//中序遍历
{
	if(!T[0])
		return;
	InTreaverse(T,0);
	puts("");
}

void PostTraverse(SqBiTree T,int e)								//后序准备
{
	if(T[2*e+1])
		PostTraverse(T,2*e+1);
	if(T[2*e+2])
		PostTraverse(T,2*e+2);
	if(T[e])
		printf("%d ",T[e]);
}	
void PostOrderTraverse(SqBiTree T)				//后序遍历
{
	if(!T[0])
		return;
	PostTraverse(T,0);
	puts("");
}

void LevelOrderTraverse(SqBiTree T)				//层序遍历二叉树
{
	int i = MAXSIZE-1;
	while(!T[i])
		i--;
	int j;
	for(j=0;j<=i;j++)
		if(T[j])
			printf("%d ",T[j]);
	puts("");
}

void Print(SqBiTree T)
{
	int i = BiTreeDepth(T);
	int k=0,m=0;
	for(int j=1;j<=i;j++)
	{
		while(m<(int)pow(2,j-1))
		{
			if(T[k+m])
				printf("%d ",T[k+m]);
			m++;
		}
		k += m;
		m = 0;
		puts("");
	}
}

void ClearBiTree(SqBiTree T)
{
	for(int i=0;i<MAXSIZE;i++)
		T[i] =NULL;
}