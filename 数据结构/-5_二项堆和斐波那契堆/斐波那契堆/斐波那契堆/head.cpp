#include <malloc.h>
#include <stdio.h>
#include "head.h"
#include "queue.h"
#include <stdlib.h>

//为一个堆的整体、参数等分配空间
void Make_Fib_Heap(FibonacciHeap &heap)
{
	heap = (FibonacciHeap)malloc(sizeof(FibonacciHeapNode));
	heap->min = 0;
	heap->keynum = 0;
			//	heap->maxdegree = 0;
}

//在堆中插入一个关键字（节点）
void fib_heap_add(Fibopnode head,Fibopnode node)
							//比较简洁的在双向链表中插入一个节点
{
	node->right = head->right;
	node->left = head;
	head->right->left = node;
	head->right = node;
}
void Fib_Heap_Insert(FibonacciHeap &heap,Fibopnode node)
{
	node->child = node->parent = 0;							//设置一些新节点的默认值
	node->degree = 0;
	node->marked = false;
							//尝试插入
	if(heap->min == 0)
	//本为空 那么直接放入
	{
		node->left = node->right = node;				//十分有必要加上这句话  不然会导致在不断插入过程中一侧出现问题
		heap->min = node;
	}
	else
	//否则，要判断关键字大小与本堆中原最小比较
	{
		fib_heap_add(heap->min,node);
		if(heap->min->key > node->key)
			heap->min = node;
	}
	heap->keynum++;
}

//将两个斐波那契堆合并(这里主要将F2释放，合并为最终的新F1)
//在执行此操作前，默认F1，F2两个堆已分配空间，只是有无关键字不明确
void fibo_heap_union(Fibopnode x,Fibopnode y)					//这里可以自己画图看的自习点  将两条根链首尾相连
{
	Fibopnode temp = x->right;		
	x->right = y->right;
	y->right->left = x;
	temp->left = y;
	y->right = temp;
}
FibonacciHeap Fib_Heap_Union(FibonacciHeap &F1,FibonacciHeap &F2)
{
	if(F1->min == 0)
	{
		free(F1);
		F1 = F2;
	}
	else if(F2->min == 0)
		free(F2);
	else
	{
		fibo_heap_union(F1->min,F2->min);						//相连后 只需做一些细微的调整
		if(F1->min->key > F2->min->key)
			F1->min = F2->min;
		F1->keynum += F2->keynum;
	}
	return F1;
}

//抽取整个堆的最小节点（取出 = 删掉 + 返回）
void fibo_heap_remove(FibonacciHeap heap,Fibopnode parent,Fibopnode node)
//将一个节点从一条双向链表中删去
{
	//首先将此节点拿出来
	node->right->left = node->left;
	node->left->right = node->right;
	//拿出来之后做一些调整
	//	此时分为是根链还是普通双链两种，如果是根链，那么应该处理的是min
	if(node->right == node)
	{
		if(parent == 0)
			heap->min = 0;
		else
			parent->child = 0;
	}
	else														//如果还有节点存在，那么将指针指向下一个节点
	{
		if(parent == 0)
			heap->min = node->right;
		else
			parent->child = node->right;
	}
}
void fib_heap_link(FibonacciHeap &heap,Fibopnode &x,Fibopnode &y)
//将y插入到x的child的双向链表中去
{
										//先将y从原先链中删去(这里可以肯定y是在根链中的)
	if(x->child == 0)
	{
		x->child = y;
		y->left = y->right = y;				//这一步必须要注意啊    因为在插入的时候如果没有净身的话 将来将节点继续插在这个节点后面 就无法组成双向链表 无法组成环了
	}
	else
		fib_heap_add(x->child,y);
	y->parent = x;
	x->degree ++;
	y->marked = false;											//首先请看关于mark的定义。    这里满足定义中的“当节点x成为另一个节点的孩子时，它便成为未被标记的节点”
}
void fib_heap_restruct(FibonacciHeap &heap)
////这个很重要！！！！！利用了散列表（哈希）的方法来对度数相同的堆进行合并
{
	int D = heap->keynum+1;
	Fibopnode *A = (Fibopnode *)malloc(sizeof(Fibopnode) * (D));//分配哈希空间
	for(int i=0;i<D;i++)
		A[i] = 0;
	Fibopnode temp,x,y;
	int d = 0;
	int remove_count = 0;
	while(heap->min)											//将根链上所有的都放到这个哈希表上去
	{
		x = heap->min;
		d = x->degree;
		fibo_heap_remove(heap,0,x);								//从原来的里面移除  最后再还回去		
		
		while(A[d] != 0)										//一旦发现该位置已经被占据了，那么处理冲突的办法就是将这两个合并 移至下一个位置 这样循环递归
		{
			y = A[d];
			//合并的这一部分 比较复杂    在合并拆成一个度为2的树后，如果再与一个相同度的树合并 那么这个树是放在第一个孩子旁边 而非第二个孩子后面，这样看起来就并不是二项堆中二项树的样子了  不过因为是双向链表 所以所以换个方向就又是二项树的样子了
			if(x->key > y->key)									//这里保证x的关键字是小的（因为最小堆的性质），这样不仅可以省空间，还可以确保每次处理的都是x
			{
				temp = x;
				x = y;
				y = temp;
				if(!remove_count)								//为什么有这个变量呢？因为合并的话可能不止一次 但是从原来的链表中删去点只能进行一次
					fibo_heap_remove(heap,0,y);
			}
			else
				if(!remove_count)
					fibo_heap_remove(heap,0,x);						//*******************************************这里把fibo_heap_remove提出来分情况是有必要的。因为一旦x和y交换后 要从原链中删去的就是y  然而不交换的话 删掉的是x
			fib_heap_link(heap,x,y);							//这里的link将y连到x身上，一并处理了一些细节
			A[d] = 0;
			d ++;												//两个节点合并，会引起度的增加，当然对应的处理哈希表对象也要变化
			remove_count++;
		}
		remove_count = 0;
		A[d] = x;
	}

	
	for(int j=0;j<D;j++)										//将哈希表中的所有节点都返回堆中
		if(A[j] != 0)
		{
			if(heap->min == 0)
			{
				heap->min = A[j];
				heap->min->left = heap->min->right = heap->min;					//这句话很有必要  不然导致一侧无法构成环
			}
			else
			{
				fib_heap_add(heap->min,A[j]);
				if(heap->min->key > A[j]->key)
					heap->min = A[j];
			}
		}
	
}
Fibopnode Fib_Heap_Extract_Min(FibonacciHeap &heap)
{
	if(heap->min == 0)
		return 0;
	Fibopnode min = heap->min;
	Fibopnode child = 0;
	while(min->child)
	{
		child = min->child;
		fibo_heap_remove(heap,min,child);
		fib_heap_add(heap->min,child);			//在这里的时候 我想为什么不用Union呢？ 这里就可以简化了，因为普通堆有一条根链，而我要加进去的堆是一个根节点（就是说只有一个节点的链），这样的话还要用Union吗 不用了，直接当成节点插进去 但也用不到Insert 内容已经配置好 只要add就行了
		child->parent = 0;
	}
	fibo_heap_remove(heap,0,min);
	if(heap->min != 0)
		fib_heap_restruct(heap);				//这一步是在将最小节点删除后对整个堆进行的一次重新整合
	heap->keynum --;
	return min;
}

//将heap堆中node节点中的关键字降至x
void fibo_heap_cut(FibonacciHeap &heap,Fibopnode node,Fibopnode parent)
//这个函数是用来将某个节点从双链表中删去，然后将此节点加入根链表，并且处理marked这个变量
{
	fibo_heap_remove(heap,parent,node);
	fib_heap_add(heap->min,node);
	node->parent = 0;
	node->marked = false;
}
void fibo_heap_cascading(FibonacciHeap &heap,Fibopnode parent)
//级联切断操作	如果非根链表中节点被删去一个子节点后就被标记为true了，之后如果再次被删去一个子节点，那么该节点本身就被删去并加入根链表了
{
	Fibopnode pp = parent->parent;
	if(pp != 0)													//如果是根链表中的节点，那么就退出级联操作
	{
		if(parent->marked == false)
			parent->marked = true;
		else
		{
			fibo_heap_cut(heap,parent,pp);
			fibo_heap_cascading(heap,pp);
		}
	}
}
void FibonacciNode_Decrease(FibonacciHeap &heap,Fibopnode node,Keytype x)
{
	if(node==0 || node->key < x)											//在操作前首先看替换的关键字是否满足函数的目的
		return;
	node->key = x;
	Fibopnode parent = node->parent;
	if(parent && node->key < parent->key)						//如果是根链里的节点被decrease 那么就不必进行种种操作了
	{
		fibo_heap_cut(heap,node,parent);
		fibo_heap_cascading(heap,parent);						//这个过程里可能有许许多多节点被移到根链中去，但是不需要与min进行比较，因为根据堆的性质 又没有新的关键字进来 所以最终最小的依旧是原来的min。当然，这个操作的本意是decrease某个关键字 所以就需要与min比较 就是下面两行
	}
	if(heap->min->key > x)									//因为被换了关键字 所以要进行比较。
		heap->min = node;		
}

//将heap堆中node节点中的关键字增至x			(Increase的程序和Decrease的程序类似  不过是Increase的程序里需要将该节点的所有子树都放到根链中去)
void FibonacciNode_Increase(FibonacciHeap &heap,Fibopnode node,Keytype x)
{
	if(node==0 || node->key > x)
		return;
	node->key = x;
	Fibopnode child = 0;
	while(node->child)							//将所有节点都放到根链中去
	{
		child = node->child;
		fibo_heap_remove(heap,node,child);
		fib_heap_add(heap->min,child);
		child->parent = 0;
	}
	node->degree = 0;
	Fibopnode parent = node->parent;				//然后将该节点Cut以及Cascading-cut
	if(parent != 0)
	{
		fibo_heap_cut(heap,node,parent);
		fibo_heap_cascading(heap,parent);
	}
	if(heap->min == node)							//如果正好这个点是最小的点 那么需要更新以下这个min的指向
	{
		Fibopnode temp = node->right;
		while(temp != node)
		{
			if(temp->key < heap->min->key)
				heap->min = temp;
			temp = temp->right;
		}
	}
}

//删除某个节点，与二项堆里的一样 很简单 利用到了decrease 和　extract		当然 有个free没有写下来。。。
void Fibonacci_Heap_Delete(FibonacciHeap &heap,Fibopnode &node)
{
	FibonacciNode_Decrease(heap,node,0);					//降到最小  这里的0代表无穷小 当然可以用-999之类的
	Fib_Heap_Extract_Min(heap);
}

//输出斐波那契堆
void Print(FibonacciHeap heap)
{
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	Fibopnode temp = heap->min,temp2 = 0,temp3 = 0;
	
	do
	{
		en_queue(Queue,temp);
		while(!is_empty(Queue))
		{
			out_queue(Queue,temp2);
			if(temp2->parent != 0)
				printf("%d is %d's child \n",temp2->key,temp2->parent->key);
			else
				printf("%d is a root\n",temp2->key);
			if(temp2->child)
			{
				temp3 = temp2 = temp2->child;
				do
				{
					en_queue(Queue,temp2);
					temp2 = temp2->right;
				}while(temp2!=temp3);
			}
		}
		temp = temp->right;
	}while(temp!=heap->min);
	puts("That's all-------------------------------------------\n");
}