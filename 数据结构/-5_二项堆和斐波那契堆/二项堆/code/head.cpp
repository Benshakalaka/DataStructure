#include <stdio.h>
#include <malloc.h>
#include "queue.h"
#include "head.h"

BinoTree MAKE_BINOMIAL_HEAP()								//创建一个新的二项堆
{
	return 0;
}

BinoTree BINOMIAL_HEAP_MINIMUN(BinoTree H)					//寻找最小关键字
//因为二项堆是最小堆有序的 故最小根节点必存在每棵二项树根节点中
{
	Key min = H->key;
	BinoTree Sib = H->sibling;
	BinoTree Res = H;
	while(Sib)
	{
		if(min > Sib->key)
		{
			min = Sib->key;
			Res = Sib;					//因为二项堆是由二项树一个个连起来的 
		}
		Sib = Sib->sibling;
	}
	return Res;
}

void BINOMIAL_LINK(BinoTree y,BinoTree z)			//使得节点y成为节点z的子女链表的新头
//因为每颗二项树的左孩子、右兄弟表示与树的排序性质正好匹配，在一棵 Bk 树中，根的最左孩子是一棵Bk-1 树的根
{
	y->sibling = z->firstchild;
	z->firstchild = y;
	y->parent = z;
	z->degree++;
}

BinoTree BINOMIAL_HEAP_MERGE(BinoTree H1,BinoTree H2)			//将H1 和 H2 的根表（根以及其所有孩子）
//使用Merge  难道H1 和H2 都已经排好序了吗？  对的 这里就要看是怎么插入的 插入是新增一个节点 当作一个二项树 使用Union 那么一来说明整棵树构建的过程都是使用的Merge 当然是满足排好序的
{
	BinoTree H = MAKE_BINOMIAL_HEAP();
	BinoTree x1 = H1, x2 = H2, x3 = 0,pre_x3 = 0;
	while(x1 && x2)
	{
		if(x1->degree <= x2->degree)
		{
			x3 = x1;
			x1 = x1->sibling;
		}
		else
		{
			x3 = x2;
			x2 = x2->sibling;
		}
		if(!H)
			H = x3;
		else
			pre_x3->sibling = x3;
		pre_x3 = x3;
	}
	if(!H)
		H = H2;
	else
	{
		if(x1)
			x3->sibling = x1;
		if(x2)
			x3->sibling = x2;
	}
	return H;
}

BinoTree BINOMIAL_HEAP_UNION(BinoTree H1,BinoTree H2)				//合并两个二项堆
{
	BinoTree H = MAKE_BINOMIAL_HEAP();
	H = BINOMIAL_HEAP_MERGE(H1,H2);
	BinoTree current = H;
	while(current)
	{
		printf("%d  ",current->key);
		current = current->sibling;
	}puts("");
	BinoTree prev=0,x=H,next=H->sibling;
	while(next)
	{
		if((x->degree != next->degree) || ((next->sibling) && (next->sibling->degree==x->degree)))
																//情况1和情况2 都在这个if判断中   情况1：x的度与next的度不同 则移向下一个		情况2：连续3个节点的度相同（只需判断x和next的next相同 因为merge已经排好序） 则将后两个合并【即将情况移到情况3或4】
		{
			prev = x;
			x = next;
		}
		else
		{
			if(x->key <= next->key)					//情况3：两节点度相同，既然要合并 就要找出关键字较小的根作为合并后的根 情况4与情况3相同
			{
				x->sibling = next->sibling;
				BINOMIAL_LINK(next,x);
			}
			else									//情况4
			{
				if(!prev)
					H = next;
				else
					prev->sibling = next;			//我原本在想 要不要把x的parent给next  答案是不要 因为这里处理的都是二项树的根  二项树的根都是空
				BINOMIAL_LINK(x,next);
			}
			x = next;						//此时的prev不变  因为根节点合并 少了个节点后prev还是原来的点 只是x和next要变一下
		}
		next=x->sibling;
	}
	return H;
}

void BINOMIAL_HEAP_INSERT(BinoTree& H,Key x)					//插入一个节点
//将新节点视作一个单独的二项堆 利用合并
{
	
	BinoTree node = (BinoTree)malloc(sizeof(BinoNode));
	node->degree = 0;
	node->firstchild = node->parent = node->sibling = 0;
	node->key = x;
	H = BINOMIAL_HEAP_UNION(H,node);
}

void Reverse(BinoTree &H,BinoTree &temp)			//将H中的所有二项树逆置(看不懂的话看 c文件夹中的“单链表逆置”)
{
	if(temp && !temp->sibling)
		H = temp;
	else
	{
		Reverse(H,temp->sibling);
		temp->sibling->sibling = temp;
		temp->sibling = 0;
	}
}
BinoTree BINOMIAL_HEAP_EXTRACT_MIN(BinoTree H)					//抽取具有最小关键字的节点 并 返回指针
{
	BinoTree min = H, current = H;
	BinoTree prev_c = 0, prev_m = 0;
	while(current->sibling)					//找到最小节点 和 其前驱先将该点所代表的整棵二项树删除
	{
		prev_c = current;
		current = current->sibling;
		if(min->key > current->key)
		{
			prev_m = prev_c;
			min = current;
		}		
	}
	prev_m->sibling = min->sibling;					//现在将整个带min节点的二项树都删掉了  之后要利用剩下的和去掉min后的新生的二项堆进行合并
													//在编写过程中 我想找到temp的最小的节点当作根节点 这个想法是错误的  因为这是新生的二项堆 没有必要第一个节点是最小的点 只需要第一个（根）节点是度最小的就行 最小关键字的节点在众根中
	BinoTree temp = min->firstchild;				//因为这个新生的二项堆原本是二项树 所以min的第一个孩子节点到其最后一个兄弟的度是递减的   然而我们的标准二项堆则是从左往右度是递增的  所以我们需要将这里的新生的堆的众兄弟颠倒 让度为0的二项树放在最左边
	BinoTree temp_2 = temp;
	Reverse(temp,temp_2);
	temp->parent = 0;
	BINOMIAL_HEAP_UNION(temp,H);
	return min;
}

void BINOMIAL_HEAP_DECREASE_KEY(BinoTree H,BinoTree x,Key k)					//减小关键字的值
{
	if(x->key < k)					//不合题意
		return;
	x->key = k;
	BinoTree y = x;
	BinoTree z = x->parent;
	Key temp;
	while(z && y->key < z->key)					//如果不是根节点减小 那么根据二项树二项堆的性质  根应该比子小 这样逐渐往上调整
	{
		temp = y->key;
		y->key = z->key;
		z->key = temp;
		y = z;
		z = y->parent;
	}
}

void BINOMIAL_HEAP_DELETE(BinoTree H,BinoTree x)					//删除某关键字
{
	BINOMIAL_HEAP_DECREASE_KEY(H,x,-999);				//这里是将要删除的点调整为最小（调整过程中如果该点不是某根也会变成根） 
	BinoTree temp = BINOMIAL_HEAP_EXTRACT_MIN(H);		//然后就可以通过EXTRACT_MIN来去除这个点
	free(temp);
}



void BinoTraverse(BinoTree T)							//层序遍历		程序检验
{
	pss Queue;
	Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,T);
	BinoTree temp=0;
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		if(temp)
		{
			printf("%d ",temp->key);
			if(temp->firstchild)
				en_queue(Queue,temp->firstchild);
			if(temp->sibling)
				en_queue(Queue,temp->sibling);
		}
	}
	puts("");
}