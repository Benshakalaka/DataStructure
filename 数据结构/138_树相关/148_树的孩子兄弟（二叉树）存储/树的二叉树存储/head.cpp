#include "head.h"
#include <stdio.h>
#include <malloc.h>
#include "queue.h"



void InitTree(CSTree &T)						//构造空树
{
	T = NULL;
}

void DestroyTree(CSTree &T)							//销毁树
{
	if(T==NULL)								//既然是按照二叉树的存储方式存储的，那么销毁的时候也按照这么来
		return;
	if(T->firstchild)
		DestroyTree(T->firstchild);
	if(T->nextsibling)
		DestroyTree(T->nextsibling);
	free(T);
	T = NULL;
}

void CreateTree(CSTree &T)							//构造树
{
	//这里创建树的方式是: 输入一个根，然后输入其子树，然后一个子树一个子树询问过来是否仍然有子树  所以这里利用到了队列的概念
	CSTree TT,cur=NULL;
	pss Queue;									//新建队列
	Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	int temp;
	printf("Input the root : (0 is equal to NULL)");			//将根单独领出来   因为一棵树的根只可能有左子树 不可能有右子树（因为单独的一棵树没有兄弟除非是森林）
	scanf("%d",&temp);
	if(!temp)												//非0  说明这棵树非空
	{
		T = NULL;
		return;
	}
	T = (CSTree)malloc(sizeof(CSNode));			//为根赋予内存空间
	T->data = temp;
	T->firstchild = T->nextsibling = NULL;
	en_queue(Queue,T);
	while(!is_empty(Queue))								//这个判断条件是因为要遍历每一个已经输入的子树 询问是否还有子树要输入  如果队列空了 也就证明已经遍历结束所有子树   也就可以退出了
	{
		out_queue(Queue,TT);
		printf("Input the element %d 's childs and 0 to end : ",TT->data);
		scanf("%d",&temp);
		//这里是后来按照书上来的
		if(temp)										//意思是是否存在子树（第一个子树是否存在）  这种存储方式不可能只有右子树而没有左子树  因为左子树是存第一个子树的
		{
			cur = TT->firstchild = (CSTree)malloc(sizeof(CSNode));		//存在第一个子树 那就放在前一个节点的firsrchild的位置  需要单独领出来处理  其他节点则是往此第一个子树的右边放
			cur->data = temp;
			scanf("%d",&temp);
			while(temp)						//处理兄弟节点   
			{
				cur->nextsibling = (CSTree)malloc(sizeof(CSNode));
				en_queue(Queue,cur);				//将上一个节点存在队列中
				cur = cur->nextsibling;
				cur->data = temp;
				scanf("%d",&temp);
			}
			cur->nextsibling = NULL;			//没有兄弟了 那nextsibling=NULL;
			en_queue(Queue,cur);				//上面的循环只存上一个节点 所以存到最后第二个的时候就结束了  这里需要把最后一个补上
		}
		else
			TT->firstchild = NULL;
	}
		//这里是先前自己写的  处理的方式是一样的 但是书上的更加简洁干净
		/*if(temp)
		{
			cur = (CSTree)malloc(sizeof(CSNode));
			cur->data = temp;
			cur->firstchild = cur->nextsibling = NULL;
			TT->firstchild = cur;
			en_queue(Queue,cur);
			TT = cur;
			scanf("%d",&temp);
			while(temp)
			{
				cur = (CSTree)malloc(sizeof(CSNode));
				cur->data = temp;
				cur->firstchild = cur->nextsibling = NULL;
				TT->nextsibling = cur;
				en_queue(Queue,cur);
				TT = cur;
				scanf("%d",&temp);
			}
		}
	}*/
}

bool TreeEmpty(CSTree T)								//判断树是否为空				
{
	if(!T)
		return true;
	else
		return false;
}

int TreeDepth(CSTree T)									//树的深度	
{
	int m = 0;
	if(!T)
		return m;
	CSTree temp;
	for(temp=T->firstchild;temp;temp=temp->nextsibling)
	{
		if(m < TreeDepth(temp))
			m = TreeDepth(temp);
	}
	return m+1;
}

Type Value(CSTree T)										//返回p所指的点的值	
{
	return T->data;
}

Type Root(CSTree T)										//返回T的根
{
	if(T)
		return Value(T);
	else
		return NULL;
}

CSTree Point(CSTree T,Type e)									//	返回树中值为s的节点的指针	
//这里我利用了先序遍历的便捷性  来寻找 
{
	if(!T)
		return NULL;
	if(T->data == e)
		return T;
	CSTree temp;
	temp = Point(T->firstchild,e);
	if(temp)
		return temp;
	temp = Point(T->nextsibling,e);
	if(temp)
		return temp;
	return NULL;
	
}

bool Assign(CSTree &T,Type cue,Type value)									//将元素cue改为value
{
	if(!T)
		return false;
	CSTree temp = Point(T,cue);
	if(temp)
	{
		temp->data = value;
		return true;
	}
	else
		return false;
}

Type Parent(CSTree T,Type cue)									//若非根，则返回双亲								
{												//广度优先搜索
	if(!T || T->data==cue)
		return NULL;
	CSTree p,t;
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,T);
	while(!is_empty(Queue))
	{
		out_queue(Queue,p);
		if(p->firstchild)
		{
			if(p->firstchild->data == cue)
				return p->data;
			en_queue(Queue,p->firstchild);
			t = p;
			p = p->firstchild;
			while(p->nextsibling)
			{
				if(p->nextsibling->data == cue)
					return t->data;
				en_queue(Queue,p->nextsibling);
				p = p->nextsibling;
			}
		}
	}
	return NULL;
}

Type LeftChild(CSTree T,Type cue)										//若为非叶子节点 则返回左孩子  否则空
{
	CSTree temp = Point(T,cue);
	if(temp && temp->firstchild)
		return temp->firstchild->data;
	else
		return NULL;
}

Type RightSibling(CSTree T,Type cue)								//若有右兄弟 则返回右兄弟 否则为空		
{
	CSTree temp = Point(T,cue);
	if(temp && temp->nextsibling)
		return temp->nextsibling->data;
	else
		return NULL;
}

void InsertChild(CSTree &T,Type p,int i,CSTree c)									//插入c为T中p节点的第i棵子树		
{
	if(!T)
		return;
	CSTree temp = Point(T,p);							//首先这个点要存在
	if(temp)	
	{
		if(i==1)										//如果要插入为第一个点
		{
			if(!temp->firstchild)
				temp->firstchild = c;
			else
			{
				c->nextsibling = temp->firstchild;		//插入操作
				temp->firstchild = c;
			}
		}
		else											//不是要成为第一个点
		{
			int j=2;
			CSTree temp_2 = temp->firstchild;
			while(temp_2 && i!=j)							//寻找插入位置
			{
				temp_2 = temp_2->nextsibling;
				j++;
			}
			if(i!=j)								//没有搜索到所要求的位置（输入错误）
			{
				printf("Wrong Input!\n");
				return;
			}
			c->nextsibling = temp_2->nextsibling;			//插入操作
			temp_2->nextsibling = c;
		}
	}
}

void DeleteChild(CSTree &T,int i,Type p)									//删除T中p节点的第i棵子树			
{
	if(!T)
		return;
	CSTree temp = Point(T,p);							//首先这个点要存在
	if(temp)
	{
		if(i==1)						
		{
			CSTree temp_2 = temp->firstchild;
			temp->firstchild = temp_2->nextsibling;
			temp_2->nextsibling = NULL;					//****这一步是必要的  否则Destroy的时候会出错的！！！！！
			DestroyTree(temp_2);
		}
		else
		{
			int j=2;
			CSTree temp_3 = temp->firstchild;
			CSTree temp_4;							//用来装要删的子树
			while(temp_3 && i!=j)							//寻找删除位置的前一个节点
			{
				temp_3 = temp_3->nextsibling;
				j++;
			}
			if(i!=j)								//没有搜索到所要求的位置（输入错误）
			{
				printf("Wrong Input!\n");
				return;
			}
			temp_4 = temp_3->nextsibling;
			temp_3->nextsibling = temp_4->nextsibling;
			temp_4->nextsibling = NULL;					//****这一步是必要的  否则Destroy的时候会出错的！！！！！
			DestroyTree(temp_4);
		}
	}
}


void Print(CSTree T)
{
	printf("%d ",T->data);
}
void PreOrderTraverse(CSTree T,void (*Visit)(CSTree))				//先序
//既然每个节点可以看作一个树 那遍历起来就跟二叉树遍历一样
{
	if(T)
	{
		Visit(T);
		PreOrderTraverse(T->firstchild,Visit);
		PreOrderTraverse(T->nextsibling,Visit);
	}
	/*if(!T)					//这个就是忽略的繁琐方法
		return;
	Visit(T);
	PreOrderTraverse(T->firstchild,Visit);
	if(T->firstchild)
	{
		CSTree temp = T->firstchild->nextsibling;
		while(temp)												//每个右子节点（兄弟节点）都是一棵树（递归）
		{
			PreOrderTraverse(temp,Visit);					
			temp = temp->nextsibling;
		}
	}*/
}

void PostOrderTraverse(CSTree T,void (*Visit)(CSTree))								//后序	
//乍看为什么这个后序遍历怎么会这么繁琐呢  不是跟二叉树一样吗？ 为什么先序遍历可以这么简单呢?(当然 也有繁琐的（就写在下面用/**/忽略了） 不过当然简单的更好 不过不易理解)
//原因是  ①先序  这种遍历是先根节点 然后左 然后右 一颗树和一颗二叉树并不是完全一样的 举个例子： 一个根节点 有两个子节点 二叉树的存储方式是左边挂一个 右边挂一个；然而树的存储方式是根节点左边挂一个子节点 然后在这个【子节点】右边挂一个  
//虽然是这样  但是先序遍历总是最后访问最右边的 所以遍历时候不受太大影响 。然而 后序遍历则不一样  按树的存储 先遍历左子节点，在遍历左子节点右子节点 最后根节点这就跟二叉树有了差别
						//后来发现树的后序遍历即为转化的二叉树的中序遍历  即本cpp最后几行 函数PostOrderTraverse2
{
	if(!T)
		return;
	PostOrderTraverse(T->firstchild,Visit);				//前两步与二叉树类似  第一步后序遍历左子节点
	if(T->firstchild)							//左子节点存放的是第一个子节点  如果存在 那么就把这个子节点的右子节点（所有） 统统后序遍历
	{
		CSTree temp = T->firstchild->nextsibling;
		while(temp)												//每个右子节点（兄弟节点）都是一棵树（递归）
		{
			PostOrderTraverse(temp,Visit);					
			temp = temp->nextsibling;
		}
	}
	Visit(T);								//最后访问根节点
}

void LevelOrderTraverse(CSTree T,void (*Visit)(CSTree))						//层序	
//之前也有谢过类似的了  用到队列（先进先出）				
{
	if(!T)
		return;
	pss Queue;
	Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,T);
	CSTree temp;
	while(!is_empty(Queue))						//首先将根节点放入  并且将有无空作为判断依据
	{
		out_queue(Queue,temp);	
		Visit(temp);
		if(temp->firstchild)					//如果存在第一个节点  那就继续判断受否还有兄弟节点
		{
			temp = temp->firstchild;
			en_queue(Queue,temp);
			while(temp->nextsibling)
			{
				temp = temp->nextsibling;
				en_queue(Queue,temp);
			}
		}
	}
}

void PostOrderTraverse2(CSTree T,void (*Visit)(CSTree))
{
	if(T)
	{
		if(T->firstchild)
			PostOrderTraverse2(T->firstchild,Visit);
		Visit(T);
		if(T->nextsibling)
			PostOrderTraverse2(T->nextsibling,Visit);
	}
}