//#include "queue.h"
#include "stack.h"
#include <stdio.h>

void InitDSTable(DLTree &DT)				//构造一个空的双链树
{
	DT = NULL;
}

void DestroyDSTable(DLTree &DT)			//双链树DT存在，将其销毁
{										//吗的  连树的destroy都不会了吗？？？？？
	if(!DT)
		return;
	if(DT->kind==BRANCH && DT->first)
		DestroyDSTable(DT->first);			//删子节点
	if(DT->next)
		DestroyDSTable(DT->next);			//删兄弟节点
	free(DT);								//删自己
	DT = 0;
}

Record *SearchDLTree(DLTree DT,KeysType K)	//搜索关键字。若搜到，则返回指向该记录的指针，否则返回空
{	//树的关键字查找
	if(!DT)
		return 0;
	int i=0;
	DLTree p = DT->first;
	while(p && i<K.num)
	{
		while(p && p->symbol!=K.ch[i])
			p = p->next;
		if(p && i<K.num)				
			p=p->first;						//上面的while是寻找相同字符的，找到最后一个的时候，虽然已经找完结束了，但是依据双链键树的结构，还需要树p往下移，得到一个叶子节点并从中取得指向该关键字的指针从而得到信息
		i++;
	}
	if(!p || p->kind==BRANCH)					//p->kind==BRANCH 就是所谓的已经存在 CHA 但要找CH的情况
		return 0;		
	else
		return p->infoptr;						//叶子节点
}


/*
void Insert(DLTree &p,int i,Record *r)
//将K中的第i个字母开始插入到p节点下面 ① 为first ② 为next
{
	DLTree one = (DLTree)malloc(sizeof(DLTNode));
	one->first = one->next = 0;
	one->symbol = r->key.ch[i];
	one->kind = BRANCH;
	if(!p->first)
		p->first = one;
	else if(r->key.ch[i] < p->first->symbol)			//取代first节点
	{
		one->next = p->first;
		p->first = one;
	}
	else									//放到兄弟节点中去
	{
		DLTree temp=p->first;
		while(temp->next && one->symbol>temp->next->symbol)
			temp = temp->next;					//找到所要插入点的前驱
		one->next = temp->next;
		temp->next = one;
	}
	DLTree next;
	while(++i<=r->key.num-1)
	{
		next = (DLTree)malloc(sizeof(DLTNode));
		next->symbol = r->key.ch[i];
		next->first = next->next = 0;
		next->kind = BRANCH;
		one->first = next;
		one = next;
	}
	next = (DLTree)malloc(sizeof(DLTNode));
	next->symbol =0;
	next->first = 0;
	next->kind = LEAF;
	next->infoptr = r;
}
void InsertDSTable(DLTree &DT,Record *r)	//若DT中不存在其关键字等于r->key的数据元素，则按顺序插入
{
	if(SearchDLTree(DT,r->key))
		return;
	DLTree p = DT->first,q;
	int i=0;
	q = DT;
	while(p)
	{
		while(p && p->symbol!=r->key.ch[i])
			p = p->next;
		if(p)
		{
			q = p;
			p=p->first;i++;
		}
	}								//找到可以插入的双亲节点 和 第i个字母需要插入 
	Insert(q,i,r);
}*/


void InsertDSTable(DLTree &DT,Record *r)	//若DT中不存在其关键字等于r->key的数据元素，则按顺序插入
{
	if(!DT)						//树本身不存在
	{
		DLTree one,temp;
		DT = (DLTree)malloc(sizeof(DLTNode));				//首先创建根节点，根节点不存字符
		DT->kind = BRANCH;
		DT->first = DT->next = 0;
		temp = DT;	
		for(int i=0;i<r->key.num;i++)					//既然是一个棵空树。那就是完全插入这个关键字，所以每个字符都是上一个字符的first子节点
		{
			one = (DLTree)malloc(sizeof(DLTNode));
			one->symbol = r->key.ch[i];
			one->next = 0;
			one->kind = BRANCH;
			temp->first = one;
			temp = one;
		}
		one = (DLTree)malloc(sizeof(DLTNode));
		one->symbol = 0;
		one->infoptr = r;						//必须设立叶子结点 叶子结点的【first不用 ，用infoptr】指向关键字信息
		one->kind = LEAF;
		one->next = 0;
		temp->first = one;
	}
	else						//已存在
	{
		DLTree p,q;
		int i=0;
		p = DT->first;
		q = DT;
		while(p && i<r->key.num)						//是存在这么一棵树的，现在要找到从这个关键字的第几个字符开始插入树中 和 在哪里插入
		{
			while(p && p->symbol < r->key.ch[i])		//寻找一个字符 看是否能找到。两种情况 ① 能找到的话就继续找下一个；② 不能找到说明要在这里插新关键字的一部分。			这里用了 < 而不是 != ，更能精确的找到插入的位置，一开始用的是!= 是因为在查找中是这样的 有些定势思维了  一定要具体情况具体分析啊
			{
				q = p;
				p = p->next;
			}
			if(p && p->symbol == r->key.ch[i])			//说明找到对应字符  找下一个 
			{
				q = p;
				p = p->first;
				i++;
				//-----------------------------------------------
				if(i==r->key.num)									//如果完全找到,则需要插入这个关键字信息的指针叶子节点			为什么加这个呢？ 比如在插入关键字为chang的信息后 如果没有这一段代码 再插cha的信息 就会找不到指向cha的信息指针 有这一段后就将最后的p指向一个存信息指针的LEAF节点了
				{
					if(p->kind==BRANCH)			//如果p指向的是BRANCH 那就得不到指向该关键字的指针了
					{
						DLTree one = (DLTree)malloc(sizeof(DLTNode));
						one->kind = LEAF;
						one->infoptr = r;
						one->symbol = 0;
						one->next = p;
						q->first = one;
					}
				}
				//----------------------------------------------
			}
			else												//一旦没找到相应字符 则需要插入
			{
				DLTree one = (DLTree)malloc(sizeof(DLTNode));
				DLTree temp;
				one->symbol = r->key.ch[i];
				one->kind = BRANCH;
				one->next = 0;
				one->first = 0;
				i++;
				if(q->first == p)					//插入一段新的子树 该子树的根节点必须找好位置  找位置又分两组情况 ①  见139行 可能在兄弟节点之间找的时候没找到这个关键字【某层 通俗的说就是找第i个字符时候在众字符间没找到】 ②  见144行 在指向某节点的子节点的时候指向了空 说明某层压根儿没有找的余地 所以插在first处
					q->first = one;
				else
					q->next = one;
				one->next = p;
				temp = one;
				for(;i<r->key.num;i++)					//每个字母都是插在first的位置【因为是棵新子树】
				{
					one = (DLTree)malloc(sizeof(DLTNode));
					one->symbol = r->key.ch[i];
					one->next = 0;
					one->kind = BRANCH;
					temp->first = one;
					temp = one;
				}
				one = (DLTree)malloc(sizeof(DLTNode));
				one->symbol = 0;
				one->infoptr = r;						//设立叶子结点 叶子结点的first不用 ，用infoptr指向关键字信息
				one->kind = LEAF;
				one->next = 0;
				temp->first = one;
			}
		}
	}
}
/*
void TraverseDSTable(DLTree DT,void (*Visit)(DLTree))	//层序遍历
{
	pss queue = (pss)malloc(sizeof(ss));
	init(queue);
	en_queue(queue,DT);
	DLTree temp;
	while(!is_empty(queue))
	{
		out_queue(queue,temp);
		if(temp->kind==BRANCH)
			Visit(temp);
		if(temp->kind==LEAF)
			printf("sssss\n");
		if(temp->first)
		{
			temp = temp->first;
			en_queue(queue,temp);
			while(temp->next)
			{
				temp = temp->next;
				en_queue(queue,temp);
			}
		}
	}
	puts("");
}*/


void TraverseDSTable(DLTree DT,void (*Visit)(Record*))		//将关键字按顺序输出【注意是关键字，不是输出字符】 说白了 就是按顺序将叶子节点输出
{										//大致思路：利用栈存储节点，因为每个节点【除了叶子】存的是字符，所以吞吞吐吐就组成了许多不同的关键字
	ps stack = (ps)malloc(sizeof(s));
	init(stack);
	DLTree p = DT;
	if(DT)
	{
		while(p->kind == BRANCH)
		{
			push(stack,p);
			p = p->first;
		}
		push(stack,p);
		Visit(p->infoptr);					//这一段代码其实跟下面那段一样 但为什么分开来写呢? 如果放进去就不行 循环里面的if看有没有兄弟，从而在兄弟里找叶子 这里是看first，看子节点，因为树的存储和双链树的first可能存叶子 从而导致如此
		while(!empty(stack))
		{
			//循环的大致过程是：把叶子节点拿出来【叶子节点不存字符，但他的兄弟节点存字符，所以把他存进来之后弄出去】
			//					看叶子节点是否有兄弟存字符 有的话就看他兄弟的树里有没有叶子节点【因为叶子节点规定是放在first的，其实就是最左边】 没有的话再pop出一个看他的兄弟节点【因为是孩子兄弟存储 二叉树 所以只考虑自己旁边的兄弟】
			pop(stack,p);
			if(p->next)			//找叶子节点
			{
				p = p->next;
				while(p->kind==BRANCH)
				{
					push(stack,p);
					p = p->first;
				}
				push(stack,p);
				Visit(p->infoptr);
			}
		}
	}
}
//这个遍历看起来复杂，但是究其核心其实很简单，下面我把Trie树【多重链表表示树】的遍历贴出来看一下，目的相同，但因为存储结构不通过而导致看起来复杂
/*void TraverseDSTable(TrieTree T,void (*Visit)(Record*))
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
}*/