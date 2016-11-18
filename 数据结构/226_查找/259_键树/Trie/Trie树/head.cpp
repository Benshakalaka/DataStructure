#include "head.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void InitDSTable(TrieTree &T)
{
	T = 0;
}

void DestroyDSTable(TrieTree &T)
{
	if(T)
	{
		for(int i=1;i<27;i++)
			if(T->bh.ptr[i])
			{
				if(T->bh.ptr[i]->kind==BRANCH)			//如果这个指针存的是另一个分支节点 则递归删除
					DestroyDSTable(T->bh.ptr[i]);
				else									//如果是叶子，直接的
				{
					free(T->bh.ptr[i]);
					T->bh.ptr[i] = 0;	//记得令空
				}
			}
	}
	free(T);
	T = 0;						//老是忘记令他等于空
}

int ord(char c)
{
	if(c>='A' && c<='Z')
		return (c-'A'+1);
	else
		return 0;
}
Record *SearchTrie(TrieTree T,KeysType K)
{
	int i=0;
	TrieTree p = T;
	while(p && p->kind==BRANCH && i<K.num)
	{
		p = p->bh.ptr[ord(K.ch[i])];
		i++;
	}
	if(p && p->kind==LEAF && EQ(p->lf.K.ch,K.ch))				//while循环退出满足两个条件即表明找到：① 找到kind为LEAF是首要的 ②其次，找到LEAF并不能就说明找到存该关键字的信息指针了，因为如果是单支【即一棵树就只有一条枝桠】，比如是CHANG的单支，我要找CHA找C的之后就找了叶子节点，但该节点指向CHANG而不是CHA
		return p->lf.infoptr;
	else											//有时候就算找到相同字符，最后还是有可能找不到存该关键字信息的叶子节点
		return 0;
}

/*
以下是自己根据情况分析自己写的，虽然大致是实现了，但是一些细节没有处理好 比如num这个变量，不过好像书上的也没有顾及这个变量。。。直接抛弃了。。。
//通过这个过程，大致一些方法
	//		首先必须自己分析，把各种情况分别列出来
	//		接着要把各种情况归类【分出个大致的 if else 来】 许多情况虽然看起来不同，但是处理的方式却是一样的
	//		然后敲代码 
	//		如果某一步骤实现某一功能且代码较多，建议另起函数 子函数 这样虽然效率变低了 但是代码的可读性大大增强了
void InsertDSTable(TrieTree &T,Record *r)
{
	if(!T)
	{
		T = (TrieTree)malloc(sizeof(TrieNode));
		T->kind = BRANCH;
		for(int i=0;i<27;i++)
			T->bh.ptr[i] = 0;
		T->bh.num = 1;
		TrieTree p;
		p = T->bh.ptr[ord(r->key.ch[0])] = (TrieTree)malloc(sizeof(TrieNode));
		p->kind = LEAF;
		p->lf.infoptr = r;
		p->lf.K = r->key;
	}
	else
	{
		int i=0;
		TrieTree p = T->bh.ptr[ord(r->key.ch[i])],q=T;
		i++;
		while(p && p->kind==BRANCH && i<r->key.num)
		{
			
			q = p;
			p = p->bh.ptr[ord(r->key.ch[i])];
			i++;
		}
		i--;

		if(p && p->kind==LEAF && EQ(p->lf.K.ch,r->key.ch))					//找到具有相同关键字的叶子指针，无需插入
			return;

		if(!p)
		{
			p = q->bh.ptr[ord(r->key.ch[i])] = (TrieTree)malloc(sizeof(TrieNode));
			p->kind = LEAF;
			p->lf.K = r->key;
			p->lf.infoptr = r;
			q->bh.num++;
		}
		else if(p->kind==LEAF && !EQ(p->lf.K.ch,r->key.ch))
		{
			Record *temp;
			temp = p->lf.infoptr;
			free(p);
			p = q->bh.ptr[ord(r->key.ch[i])] = (TrieTree)malloc(sizeof(TrieNode));
			for(int j=0;j<27;j++)
				p->bh.ptr[j] = 0;
			p->bh.num = 1;
			p->kind = BRANCH;
			p = p->bh.ptr[ord(r->key.ch[++i])] = (TrieTree)malloc(sizeof(TrieNode));
			p->kind = LEAF;
			p->lf.infoptr = r;
			p->lf.K = r->key;
			InsertDSTable(T,temp);
		}
	}
}
*/
//这是书上的代码   与我写的差别就在最后一段  我用了递归插入 省力但效率低下 这里用循环 复杂一点点但是更好
 void InsertDSTable(TrieTree &T,Record *r)
 { // 初始条件：Trie键树T存在，r为待插入的数据元素的指针
   // 操作结果：若T中不存在其关键字等于(*r).key.ch的数据元素，则按关键字顺序插r到T中
   TrieTree p,q,ap;
   int i=0,j;
   KeysType K1,K=r->key;
   if(!T)											// 树本身为空 直接插入 无需顾虑
   {
     T=(TrieTree)malloc(sizeof(TrieNode));
     T->kind=BRANCH;
     for(i=0;i<27;i++) // 指针量赋初值NULL
       T->bh.ptr[i]=NULL;
     p=T->bh.ptr[ord(K.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
     p->kind=LEAF;
     p->lf.K=K;
     p->lf.infoptr=r;
   }
   else												// 为非空树			需要考虑几种情况
   {
     for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;++i)
     {
       q=p;
       p=p->bh.ptr[ord(K.ch[i])];											//一直按着关键字的字符走下去，直到p为空或者为叶子
     }
     i--;																	//i的选择至关重要		讲不清 需要自己去看  或按着程序走寻找i所需在的位置
     if(p&&p->kind==LEAF&&p->lf.K.num==K.num&&EQ(p->lf.K.ch,K.ch))			// T中存在该关键字  则直接退出
       return;
     else																	// T中不存在该关键字，插入之  按我的考虑的情况 看图
       if(!p)							// 分支空 则直接插入
       {
	 p=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
	 p->kind=LEAF;
	 p->lf.K=K;
	 p->lf.infoptr=r;
       }
       else if(p->kind==LEAF)			// 有不完全相同的叶子		则需要多设立一个BRANCH节点 用来装这两个叶子
       {
         K1=p->lf.K;
         do												//新建一个BRANCH节点
         {
           ap=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
           ap->kind=BRANCH;
           for(j=0;j<27;j++) // 指针量赋初值NULL
             ap->bh.ptr[j]=NULL;
	   q=ap;
           i++;
         }while(ord(K.ch[i])==ord(K1.ch[i]));			//这个while是什么呢？	举个例子 比如是CHA为叶子连在C上 现在插CHANG 新建一个存第二个字符的节点 发现还是不够 第三个字符还是相等 就还要建一个 因为叶子就是叶子 不存任何BRANCH指针 只存Record信息指针
         q->bh.ptr[ord(K1.ch[i])]=p;			//将原有的叶子接上去	我自己写的是删掉了叶子 然而叶子是没有必要删掉的 所以自己写的还是存在很多缺陷
         p=q->bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));		//将新的叶子创建
         p->kind=LEAF;	
         p->lf.K=K;
         p->lf.infoptr=r;
       }
   }
 }





void TraverseDSTable(TrieTree T,void (*Visit)(Record*))
{
	if(T)
	{
		if(T->kind==LEAF)								//是叶子的话直接输出
			Visit(T->lf.infoptr);
		else
		{
			for(int i=0;i<27;i++)						//这个不跟树的孩子兄弟存储一样复杂  一个个按顺序问过来是否为空就可以
				if(T->bh.ptr[i])						//其实仔细看，孩子兄弟的遍历就跟这个一样，只是因为存储方式的不同而造成遍历起来的复杂
					TraverseDSTable(T->bh.ptr[i],Visit);
		}
	}
}
