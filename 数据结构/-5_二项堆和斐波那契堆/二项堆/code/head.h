#ifndef HEAD_H
#define HEAD_H

typedef int Key;

typedef struct Node
{
	struct Node *parent;
	struct Node *firstchild;
	struct Node *sibling;
	Key key;
	int degree;
}BinoNode, *BinoTree;

BinoTree MAKE_BINOMIAL_HEAP();						//创建一个新的二项堆

BinoTree BINOMIAL_HEAP_MINIMUN(BinoTree);					//寻找最小关键字

void BINOMIAL_LINK(BinoTree,BinoTree);

BinoTree BINOMIAL_HEAP_MERGE(BinoTree,BinoTree);

BinoTree BINOMIAL_HEAP_UNION(BinoTree,BinoTree);				//合并两个二项堆

void BINOMIAL_HEAP_INSERT(BinoTree &,Key);					//插入一个节点

BinoTree BINOMIAL_HEAP_EXTRACT_MIN(BinoTree);					//抽取具有最小关键字的节点 并 返回指针

void BINOMIAL_HEAP_DECREASE_KEY(BinoTree ,BinoTree,Key);					//减小关键字的值

void BINOMIAL_HEAP_DELETE(BinoTree,Key);					//删除某关键字

void BinoTraverse(BinoTree T);
	
#endif