#include <stdio.h>							
#include <malloc.h>
#include <stdlib.h>
#include "head.h"
//创建空的广义表
void InitGList(GList &L)
{
	L = NULL;
}

//销毁
void DestroyGList(GList &L)
{
	if(!L)									//如果是空表  就不必要Destroy了
		return;
	if(L->tag == ATOM)						//如果是原子 那就直接free了
	{
		free(L);
		L = NULL;							//切记  需要让他等于NULL
		return;
	}
	GList p1,p2;									//如果是子表  那就需要递归Destroy
	p1 = L->hp;
	p2 = L->tp;
	DestroyGList(p1);
	DestroyGList(p2);
	free(L);
	L = NULL;
}

//复制
void CopyGList(GList &T,GList L)
{
	if(!L)
	{
		T = NULL;
		return;
	}
	if(!(T=(GList)malloc(sizeof(Node))))				//这是必须的  无论是原子还是子表都表示一个节点
		return;
	T->tag = L->tag;
	if(L->tag==ATOM)
	{
		T->elem = L->elem;
		return;
	}
	CopyGList(T->hp,L->hp);						//如果不是原子 而是子表的话 说明elem是无值的  两个指针是需要赋值的  然后在想本函数的用途是复制一个表 不就是给指针赋值嘛  所以直接Copy
	CopyGList(T->tp,L->tp);
}



int GListLength(GList &L)
{
	if(!L)
		return 0;
	if(L->tag == ATOM)
		return 1;
//	if(L->tp)
		return 1+GListLength(L->tp);				//这个很好理解  这个函数是用途是得到一个表的长度  当然利用递归 假设知道子表的长度 需要返回的就是 result+1了
}
/*
//书上的
int GListLength(GList &L)
{
	int len=0;
	if(!L)
		return 0;
	if(L->tag == ATOM)
		return 1;
	while(L)							//书上写的和我的意思其实差不多   当然其实不用递归来的好（只是递归易于理解）  这个函数效率高
	{
		L = L->tp;
		len++;
	}
	return len;
}
*/



/*
int GListDepth(GList &L)				//我自己写的是错的    这个无法实现同一层的进行比较  就比如一个表里有三个子表  同一层次就有三个表需要比较  所以如下面的函数所写 利用for循环来进行比较
{
	int dep=0;
	if(!L)
		return 0;
	if(L->tag == ATOM)
		return 1;
	m = GListDepth(L->hp);
	if(m < GListDepth(L->tp))
		m = GListDepth(L->tp);
	return m+1;
}*/
int GListDepth(GList &L)						//求深度的问题需要考虑到同一层次的节点之间的比较  取较大的一个  不同层次的不能比较
{
	int dep,m;
	GList pp;
	if(!L)					//空表的深度为1
		return 1;
	if(L->tag == ATOM)
		return 0;				//原子的深度为0
	for(pp=L,m=0;pp;pp=pp->tp)					//取同一个层次的节点比较 第一个是L，第二个是L->tp.....知道最后一个NULL（ 注意 同一层!）
	{
		dep = GListDepth(pp->hp);				//得到该层的head node 的depth
		if(m<dep)								//m的意思就是这一层里面的 max depth 一个个比较取最大
			m=dep;
	}
	return m+1;									//这个本身就是一层 当然加一
}



bool GListEmpty(GList &L)					//判断是否为空
{
	if(!L)
		return true;
	return false;
}


GList GetHead(GList &L)					//得到表头  意思就是我要只有表头的一个完整节点  不要任何其他东西
{
	if(!L)
	{
		printf("么有表头！\n");
		exit(1);
	}
	GList p,h;
	InitGList(p);
	InitGList(h);
	p = L->tp;							//为了使用Copy  只能暂时把L->tp寄养在p那里
	L->tp =	NULL;						//为什么要这样做 并且GetTail的时候不需要这样呢  ①是因为一个表不会只存在尾节点却没有头结点  。。。好吧  其实没有搞懂为什么这么烦  跟GetTail一样不久可以了吗？？？？
	CopyGList(h,L);						//当然可以借用Copy
	L->tp = p;							//任务完成后  拿回来
	return h;
}
GList GetTail(GList &L)
{
	if(!L)
	{
		printf("么有表尾！\n");
		exit(1);
	}
	GList t;
	CopyGList(t,L->tp);
	return t;
}

/*				//这是我自己写的  不知道对不对 但书上的算法确实好    我是从内部考虑  要插在里面
void InsertFirst_GL(GList &L,GList e)
{
	if(!L)
	{
		L = e;
		return;
	}
	GList p;
	p = L->hp;
	L->hp = e;
	InsertFirst_GL(L->tp,p);				//插在里面的话  我是想应该是每个部分都要变一下的
}*/
//但是书上的确实从外面考虑  直接将L看作子表 
void InsertFirst_GL(GList &L,GList e)
{
	GList p;
	if(!(p=(GList)malloc(sizeof(Node))))
		exit(1);
	p->tag = LIST;
	p->hp = e;
	p->tp = L;
	L = p;
}



/*			//自己写的是错的   这种结构是一个表由表头和表尾构成的  我怎么能删掉了表头留了个表尾在那里呢 前面说过  一个表不会是只有表尾没有表头的
void DeleteFirst_GL(GList &L)
{
	GList p;
	p = L->hp;
	L = L->tp;
	free(p);
}*/
//			书上的
void DeleteFirst_GL(GList &L,GList &e)		//书上的要求用一个e来保留住表头
{
	GList p;
	e = L->hp;
	p = L->tp;
	free(L);					//因为L本身是一个表 所以表头表尾交代后 就可以把这个L 给Destroy掉了
	L = p;
}

void visit(GList p)
{
	if(p->tag==ATOM)
		printf("mark=%d  %c\n",p->mark,p->elem);
	else if(p->tag==LIST)
		printf("mark=%d list\n",p->mark);
}
void Traverse_GL(GList &L,void (*visit)(GList))
{
	if(!L)
		return;
	if(L->tag == ATOM)
		visit(L);
	else
	{
		visit(L);
		Traverse_GL(L->hp,visit);
		Traverse_GL(L->tp,visit);
	}
}

//这个函数着重介绍下
void sever(String &str,String &hstr)					//首先知道这个函数的用途后  这个函数是在脱去最外层括号的情况下使用的
{
	int i=1,k=0;	
	int len = StrLength(str);				//先知道要处理的广义表的长度
	String c,c1,c2,c3;
	StrAssign(c1,",");							//本来想是不用这样直接','的 ，但这样就类型不一样了 所以这是必须的
	StrAssign(c2,"(");
	StrAssign(c3,")");
	SubString(c,str,i,1);						//首先弄一个是为了下面的判断通过  取整个广义表的第一个字符
	for(i=1;(i<=len&&StrCompare(c,c1)) || k!=0;i++)		//这里的i不能从2开始虽然前面已经有1了 但是上面的1是用来通过循环的判断的 这里的1是用来k++的（括号匹配）
	{
		SubString(c,str,i,1);
		if(!StrCompare(c,c2))			//这里的括号匹配判断是必须的，因为头表里面不一定只有一个元素 ，既然可能有多个元素，那肯定有逗号出现，但这个逗号不是我们想要的逗号   所以在括号没有匹配的情况下，这种逗号是需要跳过的
			k++;
		else if(!StrCompare(c,c3))		//满足后，那么k==0，整个循环的判断条件 (i<=len&&StrCompare(c,c1)) || k!=0  也就相当于  i<=len&&StrCompare(c,c1)
			k--;
	}
	//上面这个循环的意义是：在整个要处理的广义表中，（不含最外层括号），要寻找最外层的逗号（第一个逗号或者整个没有逗号），以得到hstr
	if(i<=len)					//这里是指处理的广义表不止一个头表  那么就需要分配头表 和 尾表
	{
		SubString(hstr,str,1,i-2);				//再次注意  现在处理的是不含最外层括号的表  所以用这个函数来得到头
		SubString(str,str,i,len-i+1);			//得到尾（一个子表）
	}
	else						//这里是指找不到那个我们需要的逗号
	{
		StrCopy(hstr,str);						//既然只有一个元素（可能是子表也有可能是原子） 可以直接Copy
		ClearString(str);						//既然没有尾表 那就Clear
	}
}

void CreateGList(GList &L,String S)					//创建广义表
{
	GList p,q;
	InitGList(q);
	InitGList(p);
	String emp,str,hstr;
	StrAssign(emp,"()");
	if(!StrCompare(S,emp))							//如果String单单是（），那就是空表
	{
		L = NULL;
		return;
	}
	int len = StrLength(S);								
	if(!(L=(GList)malloc(sizeof(Node))))					//既然不是空的 那就malloc一个
		exit(1);
	if(len==1)									//如果是一个连括号都没有的 那就是单独的一个元素
	{
		L->tag = ATOM;
		L->elem = S[1];
		L->mark = 0;
		return;
	}
	/*SubString(str,S,2,len-2);
	L->tag = LIST;
	p = L;
	sever(str,hstr);
	CreateGList(p,hstr);
	while(!StrEmpty(str))
	{
		if(!(q=(GList)malloc(sizeof(Node))))
			exit(1);
		q->tag = LIST;
		sever(str,hstr);
		CreateGList(p,hstr);
		p->tp = q;
	}
	p->tp = NULL;*/
	L->tag = LIST;							//既然不是单独的一个元素  那就是一个表
	L->mark = 0;
	p = L;
	SubString(str,S,2,len-2);
	do
	{
		sever(str,hstr);
		CreateGList(p->hp,hstr);					//每次创建就相当于在创建一个表  所以每次都是创建表头的形式
		q = p;
		if(!StrEmpty(str))
		{
			if(!(p=(GList)malloc(sizeof(Node))))
				exit(1);
			p->tag = LIST;
			p->mark = 0;
			q->tp = p;
		}
	}while(!StrEmpty(str));
	q->tp = NULL;					//到最后自然是只有表头没有表尾了
}
