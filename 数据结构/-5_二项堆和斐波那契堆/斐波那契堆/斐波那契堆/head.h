#ifndef HEAD_H
#define HEAD_H

//与二项堆一样，它也是由一组堆最小有序树组成，并且是一种可合并堆。
//与二项堆不同的是，斐波那契堆中的树不一定是二项树；而且二项堆中的树是有序排列的，但是斐波那契堆中的树都是有根而无序的。

typedef int Keytype;

typedef struct _FibonacciTreeNode
{
	Keytype key;							//关键字
	int degree;								//度			什么是度数呢？就是说子树的个数
	struct _FibonacciTreeNode *parent;		//双亲
	struct _FibonacciTreeNode *left;			//左兄弟
	struct _FibonacciTreeNode *right;		//右兄弟
	struct _FibonacciTreeNode *child;		//孩子
	bool marked;								//指示节点x自从上一次成为另一个节点的孩子之后，是否失去过孩子。新产生的节点是未被标记的，并且当节点x成为另一个节点的孩子时，它便成为未被标记的节点。
}FiboNode, *Fibopnode;	

typedef struct
{
	int keynum;					//堆中节点个数
					//int maxdegree;				//整个堆的最大度
	Fibopnode min;				//记录堆中的最小节点
}FibonacciHeapNode,*FibonacciHeap;

void Make_Fib_Heap(FibonacciHeap &);
void Fib_Heap_Insert(FibonacciHeap &,Fibopnode );
FibonacciHeap Fib_Heap_Union(FibonacciHeap &F1,FibonacciHeap &F2);
Fibopnode Fib_Heap_Extract_Min(FibonacciHeap &);
void FibonacciNode_Decrease(FibonacciHeap &,Fibopnode,Keytype);
void FibonacciNode_Increase(FibonacciHeap &,Fibopnode,Keytype);
void Fibonacci_Heap_Delete(FibonacciHeap &,Fibopnode &);
void Print(FibonacciHeap heap);
#endif