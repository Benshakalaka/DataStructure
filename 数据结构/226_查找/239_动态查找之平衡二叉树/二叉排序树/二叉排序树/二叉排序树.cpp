#include <stdio.h>
#include <malloc.h>

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

typedef int Keytype;
typedef struct Elem
{
	Keytype key;
}Elemtype;
typedef struct Node
{
	Elemtype data;
	struct Node *LN;
	struct Node *RN;
}BiTreeNode,*BiTree;

bool SearchBST(BiTree T,Keytype key,BiTree prev,BiTree &temp)
{
	//在根指针T所指的二叉排序树中递归查询其关键字等于key的数据元素，若查找成功
	//则指针temp指向该数据元素节点，并返回true；否则指针temp指向查找路径上访问的最后一个节点
	//并返回false。指针prev指向T的双亲，初始值为NULL；
	if(!T)												//这个点有两种可能 ①本身是空树，prev本身是NULL，那么temp到最后也是NULL ②递归到一定程度后依旧未有找到 那么此时prev指向这个空指针的双亲 令temp等于它 之后利用insert函数插入或为左或为右
	{
		temp = prev;
		return false;
	}
	else if(EQ(key,T->data.key))						//找到后返回true	令temp指向这个节点的
	{
		temp = T;
		return true;
	}
	else if(LT(key,T->data.key))						//依旧在寻找的路上，比根节点小 那么到根节点左边去找
		return SearchBST(T->LN,key,T,temp);//这里的T即为记录双亲的作用
	else												//往右边找
		return SearchBST(T->RN,key,T,temp);		
}

void InsertBST(BiTree &T,Elemtype e)
{
	//当二叉树中不存在等于e.key的元素时，插入e
	BiTree p = NULL;
	if(SearchBST(T,e.key,NULL,p))							//返回false后插入
		return;
	BiTree one = (BiTree)malloc(sizeof(BiTreeNode));		//构造一个节点 作为叶子节点
	one->LN = one->RN = NULL;
	one->data = e;
	if(!p)										//p为空意味着树本身是空的 那么直接插在T上
		T = one;
	else if(LT(e.key,p->data.key))					//比p小 放左边
		p->LN = one;
	else											//否则放右边
		p->RN = one;
}


bool  Delete(BiTree &p)						//从二叉排序树中删除节点p，并重接它的左或者右子树
{
	BiTree temp = p;
	if(!p->LN && p->RN)					//删除一个节点分3种情况 看图
		p = p->RN;
	else if(p->LN && !p->RN)
		p = p->LN;
	else if(!p->LN && !p->RN)
		p = NULL;
	else								//主要在于解决删除有左右孩子的节点  只能删节点 保留孩子  因为本身树的中序是有序的 所以删起来稍烦
	{
		/*
		p = p->LN;
		while(p->RN)
			p = p->RN;
		p->RN = temp->RN;
		*/

		BiTree s;						//本函数删节点算法来自图 （d） 第二种删除方法  即在不破坏中序顺序的情况下，将p的前驱取代p 之后解决残留问题
		temp = p;
		s = p->LN;						//s为p的前驱，temp为s的双亲节点  要用到s的双亲节点是因为：s会被移到p的地方去，但s有自己的孩子节点。如果要找p的前驱，肯定是往p的左孩子的最右边走，所以s只会有左孩子而不会有右孩子。因此只要照看左孩子，
		while(s->RN)					//将左孩子移到s的双亲节点的右边就行了，因为一直是往最右边找的 s肯定是双亲的右孩子
		{
			temp = s;
			s = s->RN;
		}					//找到s 并记下其双亲
		p->data = s->data;			//将s取代p  这里是直接数据swap 所以最后需要删去原s节点
		if(p==temp)				//这个if需要考虑周全。 可能p的前驱就是p的左孩子 而并没有移到左孩子的最右边
			p->LN = s->LN;							//那么是将p的左孩子数据给p  之后将p的左孩子的左孩子（不一定有）赋给改变后的p的左孩子
		else					//这里是正常的 移到了左孩子的最右边
			temp->RN = s->LN;						//之前所说的处理s节点的左孩子（可能不存在）
		temp = s;
		s = NULL;
	}
	free(temp);			//删除
	return true;
}


bool DeleteBST(BiTree &T,Keytype key)					//若二叉排序树T中存在关键字等于key的数据元素，则删除该数据元素节点。否则退出
{
	if(!T)											//同上，会出现两种情况 ①树本空②未找到					
		return false;
	if(EQ(T->data.key,key))					//找到点后 删除 调用函数
		return Delete(T);
	else if(LT(key,T->data.key))
		return DeleteBST(T->LN,key);
	else
		return DeleteBST(T->RN,key);
}


void Destroy(BiTree &T)							//销毁
{
	if(T)
	{
		if(T->LN)
			Destroy(T->LN);
		if(T->RN)
			Destroy(T->RN);
		free(T);
		T=NULL;
	}
}

void Traverse(BiTree T)					//中序遍历
{
	if(T)
	{
		if(T->LN)
			Traverse(T->LN);
		printf("%d ",T->data.key);
		if(T->RN)
			Traverse(T->RN);
	}
}


int main()
{
      BiTree dt,p,a=NULL;
   int i;
   Keytype j;
   Elemtype r[10]={{45},{12},{53},{3},{37},{24},{100},{61},{90},{78}};
   dt = NULL;
   for(i=0;i<10;i++)
     InsertBST(dt,r[i]); // 依次插入数据元素
   Traverse(dt);
   printf("\n请输入待查找的值: ");
   scanf("%d",&j);
   i = SearchBST(dt,j,a,p);
   if(i)
   {
     printf("表中存在此值。");
     DeleteBST(dt,j);
     printf("删除此值后:\n");
     Traverse(dt);
     printf("\n");
   }
   else
     printf("表中不存在此值\n");
   Destroy(dt);
	return 0;
}