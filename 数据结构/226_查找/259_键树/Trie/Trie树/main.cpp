#include <stdio.h>
#include "head.h"

#define N 16 // 数据元素个数
#define LENGTH 27 // 结点的最大度+1(大写英文字母)

void V(Record *r)
{
	printf("%s",r->key.ch);				//如果后来加的结束符不是空格 那就用for循环输出字符串 忽略最后一个结束字符
	puts("");
}

#define Nil ' ' // 定义结束符为空格(与教科书不同)

int main()
{
	TrieTree T;
	int i;
	Record *p;
	Record r[N] = {{"CAI",3},{"CAO",3},{"LI",2},{"LAN",3},{"CHANG",5},{"CHA",3},{"WEN",3},{"CHAO",4},{"YUN",3},{"YANG",4},{"LONG",4},{"WANG",4},{"ZHAO",4},{"LIU",3},{"WU",2},{"CHEN",4}};
	InitDSTable(T);
	for(i=0;i<N;i++)
	{
		r[i].key.ch[r[i].key.num]=' '; // 在关键字符串最后加结束符		为什么加个结束符呢？ 先看void ord()函数，字母返回其字母表顺序，否则返回0，这里加的结束符返回的就是0 。为什么返回0呢？因为每个指针数组有27个指针【26+1】，第一个指针【下标是0】指向一个关键字信息。比如是CHANG的单支，我要找CHA找C的之后就找了叶子节点，但该节点指向CHANG而不是CHA，0号就是用来存CHA的不然没地方存了
		r[i].key.num++;
		p=SearchTrie(T,r[i].key);
		if(!p)
			InsertDSTable(T,&r[i]);
   }
	TraverseDSTable(T,V);
	return 0;
}