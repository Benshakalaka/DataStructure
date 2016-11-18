#include <stdio.h>
#include <malloc.h>

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

typedef int Keytype;
#define LH 1						//左高		指的是左子树的深度大于右子树的深度，以下两个同理
#define EH 0						//等高
#define RH -1						//右高

typedef struct
{
	Keytype key;
}Type;
typedef struct BiTNode												//数据类型
{
	Type x;									//所存数据
	int BF;									//平衡因子
	struct BiTNode *LN;						//左子
	struct BiTNode *RN;						//右子
}BSTNode,*BSTree;

void R_Rotate(BSTree &p)
//对以*p为跟的二叉排序树作右旋处理，处理后p指向新的根节点，
//即旋转处理之前的左子树的根节点。
{
	BSTree B = p->LN;		//右旋的意思就是原本A的左子节点是B，经过右旋，将B作为根节点取代A，而A成为B的右子节点
	p->LN = B->RN;
	B->RN = p;
	p = B;
}

void L_Rotate(BSTree &p)
//对以*p为跟的二叉排序树作左旋处理，处理后p指向新的根节点，
//即旋转处理之前的右子树的根节点。
{
	BSTree B = p->RN;		//左旋的意思就是原本A的右子节点是B，经过左旋，将B作为根节点取代A，而A成为B的左子节点
	p->RN = B->LN;
	B->LN = p;
	p = B;
}

//此平衡函数是用于插入节点的函数中，BF都是已有的且经过变化后的				即此时的T->BF=2     【看图“平衡二叉树大致”之 “旋转处理”部分】
void LeftBalance(BSTree &T)
//对以指针T所指节点为根的二叉树作左平衡旋转处理，指针T指向新的根节点
							//左平衡旋转的意思就是利用左旋转和右旋转处理发生在左子树上的不平衡 
							//分为两种情况：① 左子树的左边增加节点后导致不平衡，则只需要右旋就可以处理
							//				② 左子树的右边增加节点后导致不平衡，则需要先左旋左子树后右旋根
{
	BSTree B = T->LN;
	BSTree C = NULL;
	//按照上面的归纳 ，首相将左子树分为两种情况
	switch(B->BF)
	{
	case LH:									//若B->BF为LH，意味着是因为插入在左子树的左边而导致的不平衡，此种情况只需要右旋即可解决(可看图)
		T->BF = B->BF = EH;						//同时改变旋转后的BF值
		R_Rotate(T);
		break;
	case RH:									//若B->BF为RH，意味着是因为插入在左子树的右边导致不平衡，此时不能仅仅右旋解决，而需要先左旋后右旋(可看图)
		C = B->RN;
		switch(C->BF)					//此时需要改变旋转后的每个节点中的BF值 根据插入在左子树的；右边的；左边还是右边；进行讨论（可看图，并非随意）
		{
		case LH:	
			C->BF = B->BF = EH;
			T->BF = RH;
			break;
		case EH:									//这里空着，不懂	//问过老师后来懂了。是我少考虑了一种情况，只顾着想这个C节点本身就存在，在这个已经存在的树上考虑新增点的问题终究没有想明白，对的啊，C上新增一个点却达到了平衡EH，若是这样之前不是应该已经处理掉了嘛，怎么会有这种情况的出现。原来要考虑这C本来不存在，就是新增出来的，所以C是新的，BF当然是EH。旋转后另外两个点的BF就都为EH了，可看图“未考虑情况”
			T->BF = B->BF = EH;
			break;
		case RH:
			B->BF = LH;
			C->BF = T->BF = EH;
			break;
		}
		L_Rotate(T->LN);
		R_Rotate(T);
		break;
	}
}

//此平衡函数是用于插入节点的函数中，BF都是已有的且经过变化后的				 即此时的T->BF=-2
void RightBalance(BSTree &T)
//此右平衡旋转与左平衡旋转是相似的，这里不作详述。
{
	BSTree B = T->RN;
	BSTree C = NULL;
	switch(B->BF)
	{
	case RH:
		T->BF = B->BF = EH;
		L_Rotate(T);
		break;
	case LH:
		C = B->LN;
		switch(C->BF)
		{
		case LH:
			T->BF = C->BF = EH;
			B->BF = RH;
			break;
		case EH:									//这里空着，不懂		问过老师后来懂了。是我少考虑了一种情况，只顾着想这个C节点本身就存在，在这个已经存在的树上考虑新增点的问题终究没有想明白，对的啊，C上新增一个点却达到了平衡EH，若是这样之前不是应该已经处理掉了嘛，怎么会有这种情况的出现。原来要考虑这C本来不存在，就是新增出来的，所以C是新的，BF当然是EH。旋转后另外两个点的BF就都为EH了，可看图“未考虑情况”
			T->BF = B->BF = EH;
			break;
		case RH:
			T->BF = LH;
			B->BF = C->BF = EH;
			break;
		}
		R_Rotate(T->RN);
		L_Rotate(T);
		break;
	}
}

bool InsertAVL(BSTree &T,Type e,bool &taller)
//在平衡的二叉排序树T中不存在和e有相同关键字的节点，则插入一个元素
//为e的新节点，并返回1，否则返回0.若因插入而使二叉排序树失去平衡，
//则做平衡旋转处理，bool变量taller反映T长高与否
{
	if(!T)															//为空有两种情况：①该树本身是空，则直接插入新元素，且返回true，taller=1 ；②根据插入规则，走到了某个节点的子节点，且该子节点本身为NULL，则正好将此节点插在此处，返回true，本身为空，则深度为0，插入后变为1，则taller=1。
	{
		T = (BSTree)malloc(sizeof(BSTNode));
		T->x = e;
		T->BF = 0;
		T->LN = T->RN = NULL;						//按照平衡树的插入规则，未找到的节点肯定是接在叶子节点上。
		taller = true;
	}
	else															//不为空，说明可以在这棵树上做文章。。。
	{
		if(EQ(e.key,T->x.key))								//在树中找到与该关键字相同的key，说明已经存在，则无需插入，返回false。
		{
			taller = false;
			return 0;
		}
		//有时候会疑惑想：改变一个深度后，所有都会改变的，那怎么一下改掉所有呢？  那就是在递归之后处理
		//---------------------------------------------------------------------左边处理与右边处理是相似的，只讨论左边处理——————————————————
		if(LT(e.key,T->x.key))								//根据排序树的创建规则，e中关键字小于根节点关键字，则往该根节点的左边寻找		
		{
			if(!InsertAVL(T->LN,e,taller))		//执行插入操作。左子树插入失败意思是在左子树中存在关键字相同的关键字无需插入，直接退出。否则，成功插入，并在下面判断是否破坏了平衡
				return 0;
			if(taller)				//插入节点成功是一定会导致深度发生改变的。(为什么呢？有时候节点A左子树存B在，右子树C为空。插在右节点C 深度哪里变了？的确，但是节点A右子树C本身是树，但为空，深度为0，插入后C深度为1，但A深度不变，A的BF值为1，此刻变为0，不需要旋转，下面switch即为讨论这个)
			{
				//此处会疑惑：我怎么知道插入节点的双亲节点的双亲节点呢，我怎么知道它是否不平衡了呢？ 依旧是递归后处理，递归的一层一层出栈后考虑对之前节点的影响
				//插入节点后，可能会导致双亲节点发生变化，之后该层递归出栈，导致双亲的双亲节点不平衡，此时再处理这个双亲的双亲节点
				switch(T->BF)			//if(taller)处已解释过为什么需要switch 即改变BF值，并判断是否需要旋转
				{
				//这种情况出现在插入点的双亲的双亲
				case LH:					//若根节点本身是左高，此时又是插入在左边，则会导致不平衡，则需要平衡处理，处理后BF值已在平衡函数中改变，不影响深度(或是其他点的BF)。(此处不解可看图的旋转处理的最后一段话)
					LeftBalance(T);
					taller = false;
					break;
				//这种情况出现在插入点的双亲
				case EH:					//若本身是等高，则插入左边后左边变高，taller将需要传入上一层函数（递归出栈继续运行上一层函数）
					T->BF = LH;
					taller = true;			//**************************//
					break;
				case RH:					//本身是右边高，插左边后等高，不影响什么。
					T->BF = EH;
					taller = false;
					break;
				}
			}
		}
		//————————————————————————————————————————————————————————————————————————-
		else												//根据排序树的创建规则，e中关键字大于根节点关键字，则往该根节点的右边寻找		
		{
			if(!InsertAVL(T->RN,e,taller))
				return 0;
			if(taller)
			{
				switch(T->BF)
				{
				case LH:
					T->BF = EH;
					taller = false;
					break;
				case EH:
					T->BF = RH;
					taller = true;
					break;
				case RH:
					RightBalance(T);
					taller = false;
					break;
				}
			}
		}
		//——————————————————————————————————————————————————————————————————————————
	}
	return true;
}

//写时常漏掉： 对于taller的赋值和判断。 平时写程序需要注意不能落下一个变量。变量多不要紧，每一个都有其重要性，切记。
//switch 时切不可忘记break。
//InsertAVL 函数时，对参数taller忘记使用引用，导致在主函数中对taller的赋值影响整个程序。因为是传值，若taller一开始为false,那以后调用InsertAVL时taller一直是false.  切记传值调用和传址调用


//----------------------------------------------------------------------------------------------------------------------------------------------------------

bool DeleteBST(BSTree &T,Keytype key);
void Destroy(BSTree &T);
void Traverse(BSTree T);
void PreOrderTraverse(BSTree T);

BSTree SearchBST(BSTree T,Keytype key)
{
	if((!T) || EQ(T->x.key,key))
		return T;
	if(LT(key,T->x.key))
		return SearchBST(T->LN,key);
	else
		return SearchBST(T->RN,key);
}
int main()
{	
	BSTree dt,p;
   bool k=false;
   int i;
   Keytype j;
   //Type r[5]={{13},{24},{37},{90},{53}}; 
   Type r[3]={{24},{13},{17}}; 
   dt = NULL;
   for(i=0;i<3;i++)
     InsertAVL(dt,r[i],k); // 建平衡二叉树
   //printf("%d \n",dt->x.key);
   
   printf("先序遍历平衡二叉树\n");
   PreOrderTraverse(dt); // 先序遍历平衡二叉树
   puts("");
   Traverse(dt); // 按关键字顺序遍历二叉树
   printf("根节点左孩子%d： %d",dt->LN->x,dt->LN->BF);
   
   printf("\n请输入待查找的关键字: ");
   scanf("%d",&j);
   p = SearchBST(dt,j); // 查找给定关键字的记录
   if(p)
     printf("%d\n",p->x.key);
   else
     printf("表中不存在此值\n");
   Destroy(dt);
	return 0;
}




//------------------------------------------------------------以上为平衡二叉树的构造，以下为基本操作(公用)------------------------------------------------------------------------------------------
bool  Delete(BSTree &p)						//从二叉排序树中删除节点p，并重接它的左或者右子树
{
	BSTree temp = p;
	if(!p->LN && p->RN)					//删除一个节点分3种情况 看图
		p = p->RN;
	else if(p->LN && !p->RN)
		p = p->LN;
	else if(!p->LN && !p->RN)
		p = NULL;
	else								//主要在于解决删除有左右孩子的节点  只能删节点 保留孩子  因为本身树的中序是有序的 所以删起来稍烦
	{
		/*
		p = p->LN;
		while(p->RN)
			p = p->RN;
		p->RN = temp->RN;
		*/

		BSTree s;						//本函数删节点算法来自图 （d） 第二种删除方法  即在不破坏中序顺序的情况下，将p的前驱取代p 之后解决残留问题
		temp = p;
		s = p->LN;						//s为p的前驱，temp为s的双亲节点  要用到s的双亲节点是因为：s会被移到p的地方去，但s有自己的孩子节点。如果要找p的前驱，肯定是往p的左孩子的最右边走，所以s只会有左孩子而不会有右孩子。因此只要照看左孩子，
		while(s->RN)					//将左孩子移到s的双亲节点的右边就行了，因为一直是往最右边找的 s肯定是双亲的右孩子
		{
			temp = s;
			s = s->RN;
		}					//找到s 并记下其双亲
		p->x = s->x;			//将s取代p  这里是直接数据swap 所以最后需要删去原s节点
		if(p==temp)				//这个if需要考虑周全。 可能p的前驱就是p的左孩子 而并没有移到左孩子的最右边
			p->LN = s->LN;							//那么是将p的左孩子数据给p  之后将p的左孩子的左孩子（不一定有）赋给改变后的p的左孩子
		else					//这里是正常的 移到了左孩子的最右边
			temp->RN = s->LN;						//之前所说的处理s节点的左孩子（可能不存在）
		temp = s;
		s = NULL;
	}
	free(temp);			//删除
	return true;
}


bool DeleteBST(BSTree &T,Keytype key)					//若二叉排序树T中存在关键字等于key的数据元素，则删除该数据元素节点。否则退出
{
	if(!T)											//同上，会出现两种情况 ①树本空②未找到					
		return false;
	if(EQ(T->x.key,key))					//找到点后 删除 调用函数
		return Delete(T);
	else if(LT(key,T->x.key))
		return DeleteBST(T->LN,key);
	else
		return DeleteBST(T->RN,key);
}


void Destroy(BSTree &T)							//销毁
{
	if(T)
	{
		if(T->LN)
			Destroy(T->LN);
		if(T->RN)
			Destroy(T->RN);
		free(T);
		T=NULL;
	}
}

void Traverse(BSTree T)					//中序遍历
{
	if(T)
	{
		if(T->LN)
			Traverse(T->LN);
		printf("%d ",T->x.key);
		if(T->RN)
			Traverse(T->RN);
	}
}

void PreOrderTraverse(BSTree T)			//先序遍历
{
	if(T)
	{
		printf("%d ",T->x.key);
		if(T->LN)
			PreOrderTraverse(T->LN);
		if(T->RN)
			PreOrderTraverse(T->RN);
	}
}