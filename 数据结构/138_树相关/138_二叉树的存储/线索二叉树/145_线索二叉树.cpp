//这里是线索二叉树的存储
//什么是线索二叉树呢？ 若节点有左子树 则其LN指示其左孩子，否则令LN指其前驱；相同，若有右子树，则RN指向其右孩子，否则指向其后继
//什么时候用这种线索二叉树呢?  如果在某程序中二叉树经常遍历或查找节点在遍历所得线性序列中的前驱和后继，则应采用线索链表做存储结构
#include <stdio.h>		
#include <malloc.h>

typedef int Type;								//存储结构里所存储的数据类型规定
enum PointerTag{Link,Thread};					//可读性提高Link(0) 指向左右孩子  Thread(1)指向前驱或者后继(线索)
typedef struct	BiThrNode						//结构体
{
	Type data;						//数据
	PointerTag LTag,RTag;			//用于判断其左右孩子指针指向的到底是左右孩子还是前驱后继
	struct	BiThrNode *LN,*RN;			//指向左右孩子或者前驱后继
}BiThrNode,*BiThrTree;
/*void Pre(BiThrTree T)
{
	printf("%d ",T->data);
	if(T->LN&&T->LTag==Link)
		Pre(T->LN);
	if(T->RN&&T->RTag==Link)
		Pre(T->RN);
}*/
void CreateBiThrTree(BiThrTree &);						//按先序输入二叉树节点值
void InThreding(BiThrTree );							//中序线索化
void InOrderThreading(BiThrTree &,BiThrTree );						//中序遍历(并不是输出  而是利用遍历线索化)二叉树（中序线索化，Thrt指向头结点）
void InOrderTraverse(BiThrTree ,void (*Visit)(BiThrTree));							//非递归 中序遍历
void Print(BiThrTree T)
{
	if(T)
		printf("%d ",T->data);
}


int main()				
{
	BiThrTree T,Thrt;
	CreateBiThrTree(T);
	InOrderThreading(Thrt,T);
	printf("输出：\n");
	//Pre(T);
	InOrderTraverse(Thrt,Print);puts("");
	return 0;
}


void CreateBiThrTree(BiThrTree &T)					//大致的创建过程与一般的二叉树创建类似 只有Tag部分不同需要增加
{
	int temp;
	scanf("%d",&temp);
	if(!temp)
	{
		T = NULL;
		return;
	}
	T = (BiThrTree)malloc(sizeof(BiThrNode));
	T->data = temp;
	T->LTag = T->RTag = Thread;
	CreateBiThrTree(T->LN);						//这是书上的  我自己想的是令这个函数有一个返回值 返回0，1来确定连接的分别是Link 还是Thread  这样也可以  当然书上的更简洁
	if(T->LN)
		T->LTag = Link;							//我本来想在设置线索/孩子标志（Tag）的同时设置线索指针  可是后来才明白标志是确定的 但是指针确实不一定的（随着遍历的方式不同而改变）
	CreateBiThrTree(T->RN);
	if(T->RN)
		T->RTag = Link;
}

BiThrTree pre;
void InOrderThreading(BiThrTree &Thrt,BiThrTree T)				//具体线索化   为什么需要这个头结点呢  看文件的图中文字解释"为什么要头结点"或者树上P146
{
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	Thrt->RN = Thrt;				//这个右指针是指向最后一个节点的 但是还没有找到呢  之所以这样是为了防止树T是空的 
	Thrt->RTag = Thread;					//必是线索
	Thrt->LTag = Link;
	if(!T)
		Thrt->LN = Thrt;
	else
	{
		Thrt->LN = T;
		pre = Thrt;
		InThreding(T);					//这时候pre就指向最后一个节点了  也就是找到最后一个节点了
		pre->RTag = Thread;
		pre->RN = Thrt;
		Thrt->RN = pre;
	}
}
void InThreding(BiThrTree T)						//线索化  也就是给空节点赋予前驱后继  需要遍历一边才知道（因为不同的遍历方法有不同的前驱后继）
{
	if(!T)
		return;
	InThreding(T->LN);						//为什么这里一个 最下面一个呢？ 因为是中序遍历  夹在中间的就是此刻访问的节点
	if(!T->LN)								//这里if加上下面的if为什么呢 为什么要考虑pre呢？ 因为一个节点的后继和后一个节点的前驱有可能就是互相的呀
	{
		T->LTag = Thread;
		T->LN = pre;						//这个递归  当没有左孩子的时候也就意味着已经到了树的最左边  所以初始化的pre=Thrt
	}
	if(!pre->RN)					//如果没有右孩子（为什么强调右呢）因为右边是后继  同理上面是考虑前驱  
	{
		pre->RTag = Thread;
		pre->RN = T;
	}	
	pre = T;						//考虑过后就移到下一个
	InThreding(T->RN);
}




//写这个非递归函数我是先看了书上的 然后自己仿照写 写的时候画图 一步一步来  ①哪一步需要干嘛一个个写上去②考虑多种情况 
void InOrderTraverse(BiThrTree T,void (*Visit)(BiThrTree))
{
	BiThrTree p = T->LN;						//存在一个头结点 便于双向遍历 主要信息看文件夹中的截图  LN指向根节点
	while(p != T)				//只有第一个节点的前驱和最后一个节点的后继才等于这个头结点 所以可以那这个当作判定条件
	{
		while(p->LTag==Link)				//这个是中序遍历  最先的必须是最左边的 自己画个图来演示就知道为什么需要这个循环了
			p = p->LN;
		Visit(p);	
		//为什么需要下面这个循环呢？  看那个线索二叉树（运算）的图的时候自然想不到要用这个循环 一个if足矣  但是如果等于一个线索后这个线索没有右孩子 又是线索 那一个if运行下去就会出错了（自己演示）
		while(p->RTag==Thread && p->RN!= T)				//为什么这个while需要判断是否等于T呢 因为上面循环是往左的&&等于Link才循环 不会到T； 然而这里是向右的&&是线索  可能到最后一个的右线索是T 所以需要这个判定 
		{
			p = p->RN;
			Visit(p);
		}
		p = p->RN;					//这一步是必要的   就算没有上面一个循环 某种情况下还是能运行 但没有这一部 就不行了
	}
}


//这个我最后调试的时候也出问题 觉得怎么也找不出来bug  但最后一步一步缩小问题发生的范围 才发现是判断的时候出错  原本是 != 的写成了 ==