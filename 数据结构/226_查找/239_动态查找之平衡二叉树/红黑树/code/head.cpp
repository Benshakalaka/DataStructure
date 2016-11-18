#include <stdio.h>
#include <malloc.h>
#include "head.h"
#include "queue.h"

/*满足的5个性质
	1） 每个节点要么是红的，要么是黑的
	2） 根节点是黑的
	3） 每个叶节点，即空节点（NIL）是黑的
	4） 如果一个节点是红的，那么它的两个儿子都是黑色的
	5） 对每个节点，从该节点到其所有子孙节点的所有路径上包含相同数目的黑节点
*/


RBTree RBSearch(RBTree T,Key x)							//查找
{
	RBTree p = T;
	while(p && p->key!=x)
	{
		if(x<p->key)
			p = p->Lchild;
		else
			p = p->Rchild;
	}
	
	if(p)
		return p;
	else
		return 0;
}


//这里的旋转操作和平衡树里的旋转类似 所以不多说明
void LEFT_ROTATE(RBTree &T,RBTree x)								//左旋
{
	RBTree y = x->Rchild;
	x->Rchild = y->Lchild;
	if(y->Lchild)
		y->Lchild->Parent = x;
	if(!x->Parent)
		T = y;
	else if(x==x->Parent->Lchild)
		x->Parent->Lchild = y;
	else
		x->Parent->Rchild = y;
	y->Parent = x->Parent;
	y->Lchild = x;
	x->Parent = y;
}

void RIGHT_ROTATE(RBTree &T,RBTree y)								//右旋
{
	RBTree x = y->Lchild;
	y->Lchild = x->Rchild;
	if(x->Rchild)
		x->Rchild->Parent = y;
	if(!y->Parent)
		T = x;
	else if(y==y->Parent->Lchild)
		y->Parent->Lchild = x;
	else
		y->Parent->Rchild = x;
	x->Rchild = y;	
	RBTree temp = y->Parent;
	//printf("\n%p\n%p\n%p\n",&x->Parent,&y,temp);
	x->Parent = temp;
	y->Parent = x;
}

void RB_INSERT(RBTree &T,Key x)								//节点插入
{
															//找出要插入的双亲节点
	RBTree temp = T,pre = 0;
	while(temp)
	{
		pre = temp;
		if(x < temp->key)
			temp = temp->Lchild;
		else
			temp = temp->Rchild;
	}
														//为了尽量避免对树的调整，所以尽可能加入红结点
	RBTree one = (RBTree)malloc(sizeof(RBNode));
	one->color = Red;
	one->key = x;
	one->Lchild = one->Rchild = 0;
	one->Parent = pre;
	//printf("\n%p\n%p\n",&one->Parent,&pre);
	//以下是粗略的将简单的情况直接解决 复杂的情况则归纳到一个函数中去	
	if(!pre)										//情况1：插入的是根结点[根节点的双亲节点为空]。所以只需改颜色
	{
		one->color = Black;
		T = one;
	}
	else
	{
		if(pre->key>x)
			pre->Lchild = one;
		else
			pre->Rchild = one;
												//情况2：插入的结点的父结点是黑色 什么也不做
	}
	RB_INSERT_FIXUP(T,one);						//复杂情况处理
}


void RB_INSERT_FIXUP(RBTree &T,RBTree x)						//节点插入后调整回复红黑树性质
//与平衡二叉树确实十分相似 比如word文档里举得例子就是两次旋转可以调整一个点。只不过这里并没有单独的函数把两次旋转合并在一起
{
	RBTree uncle=0;
	while(x->Parent && x->Parent->color==Red)
	{
		if(x->Parent == x->Parent->Parent->Lchild)		//因为涉及祖父节点的旋转 和 叔节点 所以分开
		{
			uncle = x->Parent->Parent->Rchild;
			if(uncle && uncle->color==Red)						//情况3：当前结点的父结点是红色且祖父结点的另一个子结点（叔叔结点）是红色
				//对策：将当前节点的父节点和叔叔节点涂黑，祖父结点涂红，把当前结点指向祖父节点，从新的当前节点重新开始算法。
			{
				uncle->color = x->Parent->color = Black;
				x->Parent->Parent->color = Red;							//这里为什么可以直接将祖父节点的颜色涂成红色呢？是因为 如果祖父节点本身是红的，那么父节点和叔节点一定要是黑的 不然早就不满足红黑树的性质
				x = x->Parent->Parent;				//可能这个祖父节点就是根节点呢？ 那么就被必须将此涂成黑色　增加整棵树的黑高度
			}
			else
			{
				if(x==x->Parent->Rchild)						//情况4：当前节点的父节点是红色,叔叔节点是黑色，当前节点是其父节点的右子
					//对策：当前节点的父节点做为新的当前节点，以新当前节点为支点左旋。
				{
					x = x->Parent;
					LEFT_ROTATE(T,x);
					
				}
				else											//情况5：当前节点的父节点是红色,叔叔节点是黑色，当前节点是其父节点的左子
					//解法：父节点变为黑色，祖父节点变为红色，在祖父节点为支点右旋
				{
				//	printf("\n%p\n%p\n",&x->Parent,x->Parent);
					x->Parent->color = Black;
					x->Parent->Parent->color = Red;			//这里未改变所指要调整节点
					RIGHT_ROTATE(T,x->Parent->Parent);
				}
			}
		}
		else											//以下类似
		{
			uncle = x->Parent->Parent->Lchild;
			
			if(uncle && uncle->color==Red)
			{
				uncle->color = x->Parent->color = Black;
				x->Parent->Parent->color = Red;	
				x = x->Parent->Parent;
			}
			else
			{
				if(x==x->Parent->Lchild)
				{
					x = x->Parent;
					RIGHT_ROTATE(T,x);
				}
				else
				{
					x->Parent->color = Black;
					x->Parent->Parent->color = Red;
					LEFT_ROTATE(T,x->Parent->Parent);
				}
			}
		}
	}
	T->color = Black;							//对应情况3里的如果祖父节点是根节点
}


void RB_DELETE(RBTree &T,Key x)								//删除节点
{
	RBTree node;
	node = RBSearch(T,x);								//首先利用Search函数在树中搜寻这个点 找到则可以进行删除
	if(!node)
	{
		printf("Not Found!\n");
		return;
	}
	
	int side=0;										//*****************************（0 为左 1 为右）因为存在叶子节点【叶子节点不记录关键字】，所以在树中等于空 但是有时候却需要用到这些叶子 比如这个叶子取代了删除的点 我们通过这个点来知道这个叶子的兄弟以及其他信息【有了side就可以避免将这个点真正引入这棵树 只要将这个点隔离在树外 利用一些有用的信息即可 若引入树中 会导致很多不测】)   这个理解很重要
	
	RBTree child=0;
	RBTree old = node;
	if(!node->Lchild || !node->Rchild)					//左右只存在一个或是都不存在，这种情况的话只要将这个要删除的点的孩子（如果存在的话）取代这个点的位置
	{
		if(node->Lchild)							//先将孩子找出来（不存在的话也要找出来）
			child = node->Lchild;
		else
			child = node->Rchild;
		if(!node->Parent)					//如果要删除的点正好是根节点 那么孩子直接为根
			T = child;
		else									//否则的话 孩子放在双亲节点的位置
		{
			if(node==node->Parent->Lchild)			//找位置
			{
				node->Parent->Lchild = child;
				side = 0;
			}
			else
			{
				node->Parent->Rchild = child;
				side = 1;
			}
		}
		
		if(child)								//将孩子节点中的parent部分处理好
			child->Parent = node->Parent;
	}
	else												//左右孩子都存在 这样的话需要找出要删除节点的前驱 或者 后继来将此节点中的内容取代（并非节点取代节点），之后删除用来替换的点【因为这样的话要删除的点就变成只有一个孩子节点的节点了】（替罪羔羊、、、）
	{
		node = node->Rchild;
		while(node->Lchild )						//这里找的是后继  后继就是要删除节点的右孩子的最左孩子 
			node=node->Lchild;
		old->key = node->key;
		child = node->Rchild;
		if(node->Parent==old)						//如果最后要删除的节点有孩子，那么需要将其孩子挂到要删除节点的双亲节点下面（不一定有）
		{
			old->Rchild = child;
			side = 1;
		}
		else
		{
			node->Parent->Lchild = child;
			side = 0;
		}
		if(child)
			child->Parent = node->Parent;
	}
	if(!child)
	{							//如果发现child是空的 那么必须给其赋予一个内存 因为真正的红黑树叶子节点就是一个个没有关键字但是是黑色的节点  这样才能调整红黑树 使其满足性质
								//但是，但是，你看，我并没有把它挂到树上去。 child这个变量好像是我自己弄出来的，和side一起（因为child没挂在树上，所以需要用一种方式来判断是左子还是右子，如果child是空的，那么side也是默认左边（因为取的是后继））。 既然用了side这个变量，所以调整函数干脆就用它来判断左右了
		child = (RBTree)malloc(sizeof(RBNode));
		child->Lchild = child->Rchild = 0;
		child->Parent = node->Parent;
		child->color = Black;			//颜色一定要是黑的
		child->key = -1;			//不存key
	}
	if(node->color==Black)				//node是要删的 child是取代的
		RB_DELETE_FIXUP(T,child,side);
	free(node);
}


//这里有个假设出来的思想：【书上】
	//在删除节点后，原红黑树的性质可能被改变，如果删除的是红色节点，那么原红黑树的性质依旧保持，此时不用做修正操作；如果删除的节点是黑色节点，原红黑树的性质可能会被改变，我们要对其做修正操作。
	//那么哪些树的性质会发生变化呢，如果删除节点不是树唯一节点，那么删除节点的那一个支的到各叶节点的黑色节点数会发生变化，此时性质5被破坏。如果被删节点的唯一非空子节点是红色，而被删节点的父节点也是红色，那么性质4被破坏。如果被删节点是根节点，而它的唯一非空子节点是红色，则删除后新根节点将变成红色，违背性质2		
	//下面我们用一个分析技巧：我们从被删节点后来顶替它的那个节点开始调整，并认为它有额外的一重黑色。这里额外一重黑色是什么意思呢，我们不是把红黑树的节点加上除红与黑的另一种颜色，这里只是一种假设，我们认为我们当前指向它，并且空有额外一种黑色，可以认为它的黑色是从它的父节点被删除后继承给它的，它现在可以容纳两种颜色，如果它原来是红色，那么现在是红+黑，如果原来是黑色，那么它现在的颜色是黑+黑。有了这重额外的黑色，原红黑树性质5就能保持不变。
	//现在只要花时是恢复其它性质就可以了
	//做法还是尽量向根移动和穷举所有可能性
void RB_DELETE_FIXUP(RBTree &T,RBTree x,int side)							//删除节点后回复红黑树性质
//这里的 x 指的是后来代替被删节点的节点
{
	RBTree bro=0;//printf("%d\n",x->key);
	while(x->Parent && x->color==Black)						
	//这一个循环判断和循环外的最后一句代码就处理了两种情况 
	//		情况1：x->Parent不存在，即x为根【既然x是根了，那么之前删除的节点肯定就是根，且只有一个孩子，那么x为黑就什么都不做】，那么处理只需在x为红的时候【破坏性质2】将颜色改为黑    
	//		情况2：x原本为红色（x的移动不影响性质5） 但是删除节点是黑色 破坏了性质5  对策是 直接将其染成黑色
	{
		if(!side)			//通过side来进行不同的兄弟赋值和旋转
		{
			bro = x->Parent->Rchild;
			printf("%d\n",bro->key);
			if(bro && bro->color==Red)							//情况3 ：当前节点是黑且兄弟节点为红色【主要是过渡作用 将兄弟节点在不破坏性质5的情况下变成黑色】
														//对策：把父节点染成红色，把兄弟结点染成黑色，以双亲节点进行左转。之后重新进入算法（这里是其父节点左孩子时的情况）。此变换后原红黑树性质5不变，而把问题转化为兄弟节点为黑色的情况
			{
				x->Parent->color = Red;				//既然原本bro是红色的 说明双亲节点是黑色的（性质4）
				bro->color = Black;
				LEFT_ROTATE(T,x->Parent);
				bro = x->Parent->Rchild;					//经过旋转后 兄弟节点已经更换
			}
//			else	//这个else是不需要的 因为情况3是为情况4、5、6做铺垫
//			{
				if((!bro->Lchild || bro->Lchild->color==Black) && (!bro->Rchild || bro->Rchild->color==Black))				//情况4：当前节点是黑色，且兄弟是黑色，且兄弟节点的两个子节点全为黑色。【是一次旋转】
							//注意 这里为什么要有两个为空的条件呢？ 因为该兄弟节点可能什么都没有 这就意味着两个黑孩子 但是下面就用不到他的孩子 所以这里为空就可以等价为两黑
																						//对策：把当前节点和兄弟节点中抽取一重黑色追加到父节点上，把父节点当成新的当前节点，重新进入算法。（x去掉一层黑后还是原来颜色【因为本就有两层】兄弟节点本是黑 去掉后变成了红）
				{
					bro->color = Red;					//如果情况4是由情况3转来的 那么此时 ① 不符合性质4  ② 因为原来双亲节点是红色的，所以现在x指向的节点就是红黑的。但是表现出来的是红色 所以会在while循环的时候退出循环 之后最后一句将此节点改为黑色
					x = x->Parent;							
					if(x->Parent && x==x->Parent->Lchild)		//程序有一个信念。。。就是把节点往上走，走到根节点的时候就需要判定是否存在双亲节点
						side = 0;
					else
						side = 1;
				}
				else 				
				{
					if(bro->Lchild->color==Red && (!bro->Rchild || bro->Rchild->color==Black))				//情况5：当前节点颜色是黑+黑，兄弟节点是黑色，兄弟的左子是红色，右子是黑色【主要是过渡作用 过度到情况6】			令： 凡是要求子节点是黑色的  都必须包含一种情况：该节点是叶子节点（或该节点不存在，因为这树里由于叶子节点不存数据省去了叶子节点）
																							////对策：把兄弟结点染红，兄弟左子节点染黑，之后再在兄弟节点为支点解右旋，之后重新进入算法。此是把当前的情况转化为情况6，而性质5得以保持
					{	
						Color color = bro->color;
						bro->color = bro->Lchild->color;
						bro->Lchild->color = color;
						RIGHT_ROTATE(T,bro);
						bro = x->Parent->Rchild;				//一系列步骤在不破坏性质5的情况下将兄弟节点的右孩子调成为红色
					}

					bro->color = x->Parent->color;						////情况6：当前节点颜色是黑-黑色，它的兄弟节点是黑色，但是兄弟节点的右子是红色，兄弟节点左子的颜色任意。【和情况5合起来就是先右转后左转 二次旋转】								
					x->Parent->color = Black;							////把兄弟节点染成当前节点父节点的颜色，把当前节点父节点染成黑色，兄弟节点右子染成黑色，之后以当前节点的父节点为支点进行左旋，此时算法结束，红黑树所有性质调整正确。
					bro->Rchild->color = Black;
					LEFT_ROTATE(T,x->Parent);
					x = T;
				}
		}
		else														//以下是节点在双亲节点右边的 情况
		{
			bro = x->Parent->Lchild;
			printf("%d\n",bro->key);
			if(bro && bro->color==Red)
			{
				bro->color = Black;
				x->Parent->color = Red;
				RIGHT_ROTATE(T,x->Parent);
				bro = x->Parent->Lchild;
			}
			if((!bro->Lchild || bro->Lchild->color==Black) && (!bro->Rchild || bro->Rchild->color==Black))
			{
				bro->color = Red;
				x = x->Parent;									
				if(x->Parent && x==x->Parent->Lchild)
					side = 0;
				else
					side = 1;
			}
			else 
			{
				if((!bro->Lchild || bro->Lchild->color==Black) && bro->Rchild->color==Red)
				{
					bro->Rchild->color = Black;
					bro->color = Red;
					LEFT_ROTATE(T,bro);
					bro = x->Parent->Lchild;
				}

				bro->color = x->Parent->color;
				x->Parent->color = Black;
				bro->Lchild->color = Black;
				RIGHT_ROTATE(T,x->Parent);
				x = T;
			}
		}
	}
	x->color = Black;
}


void RBTraverse(RBTree T)							//层序遍历		程序检验
{
	pss Queue;
	Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,T);
	RBTree temp=0;
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		if(temp)
		{
			printf("%d ",temp->key);
			if(temp->Lchild)
				en_queue(Queue,temp->Lchild);
			if(temp->Rchild)
				en_queue(Queue,temp->Rchild);
		}
	}
	puts("");
}