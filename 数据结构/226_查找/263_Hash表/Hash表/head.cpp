#include "head.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

int m=0;					//表长 

int hashsize[]={11,19,29,37};				//哈希表容量递增表，一个合适的素数序列

void InitHashTable(HashTable &H)
{
	H.count = 0;
	H.sizeindex = 0;
	m = hashsize[0];
	H.elem = (Elemtype *)malloc(sizeof(Elemtype)*m);
	if(!H.elem)
		exit(1);
	for(int i=0;i<m;i++)								//每个先置为NULLKEY	
		H.elem[i].key = NULLKEY;

}

void DestroyHashTable(HashTable &H)
{
	H.count = 0;
	H.sizeindex = 0;
	if(H.elem)
		free(H.elem);
	H.elem = 0;
}

unsigned Hash(Keytype K)				//所谓的哈希函数,当然这里只是其中很简单的一种  
{
	return K%m;
}
int collision(int &p,int c)			//所谓的解决冲突的办法
{
	return (p+c)%m;
}

int SearcHash(HashTable H,Keytype K,int &p,int &c)
//在开放定址哈希表H中查找关键码为K的元素，若查找成功，以p指示待查数据
//元素在表中位置，并返回SUCCESS；否则，以p指示插入位置，并返回UNSUCCESS，
//c用以计冲突次数，其初值置0
{
	
	p = Hash(K);int q=p;
	while(H.elem[q].key!=NULLKEY && !EQ(H.elem[q].key,K))			//搜索时如果发现不相等，则表明发生冲突，不仅插入的时候需要用到冲突函数，搜索的时候也需要用到
	{
		c++;
		if(c<m)										//c有限制条件
			q = collision(p,c);
		else
			break;
	}p = q;
	if(EQ(H.elem[p].key,K))
		return SUCCESS;
	else
		return UNSUCCESS;
	
}

void RecreateHashTable(HashTable &H)
//这里的重新分配内存较为复杂了，并不是单单扩个容，而是重新分配后，全部置空，之后全部重新插入
{
	//printf("Ok!I am here\n");
	Elemtype *p,*elem = (Elemtype *)malloc(sizeof(Elemtype) * H.count);
	int i,count=H.count;
	p = elem;
	for(i=0;i<m;i++)					//暂存
		if(H.elem[i].key!=NULLKEY)
			*p++ = H.elem[i];					//这里的++ 的优先级大于 *，所以如果是 *++p这样的话 ，就是先p移向下一个然后解引用
	H.sizeindex++;
	m = hashsize[H.sizeindex];
	H.count = 0;
	H.elem = (Elemtype *)realloc(H.elem,sizeof(Elemtype)*m);			//realloc	新增
	if(!H.elem)
		exit(1);
	for(i=0;i<m;i++)							//全部置空
		H.elem[i].key = NULLKEY;
	for(p=elem;p<elem+count;p++)				//全部重新插入
		InsertHash(H,*p);
}
int InsertHash(HashTable &H,Elemtype e)
//查找不成功时插入数据元素e到开放定址哈希表中，若冲突次数过大则重建哈希表
{
	int c = 1;
	int p;
	if(SearcHash(H,e.key,p,c))					//没搜到就插入 这里的p返回的就是插入的位置
		return DUPLICATE;
	else if(c<hashsize[H.sizeindex]/2)			//	据说这是一个阀值，可调					-------------------------------------------------？？？？？？？？？？？？？？？？？？？？
	{
		H.elem[p] = e;
		H.count++;
		return SUCCESS;
	}
	else
	{
		RecreateHashTable(H);					//重新分配内存
		InsertHash(H,e);
	}
	return SUCCESS;
}


void TraverseHash(HashTable H,void (*Visit)(Elemtype))
{
	int i;
	for(i=0;i<m;i++)
		if(H.elem[i].key!=NULLKEY)
			Visit(H.elem[i]);
}

int Find(HashTable H,Keytype K,int &p)						//其实就是Search
{
	
	p = Hash(K);int c=1,q=p;
	while(H.elem[q].key!=NULLKEY && !EQ(H.elem[q].key,K))			//搜索时如果发现不相等，则表明发生冲突，不仅插入的时候需要用到冲突函数，搜索的时候也需要用到
	{
		c++;
		if(c<m)										//c有限制条件
			q = collision(p,c);
		else
			return UNSUCCESS;
	}
	p = q;
	if(EQ(H.elem[p].key,K))
		return SUCCESS;
	else
		return UNSUCCESS;
}