//疑问：
//	①	是不是每个非终端节点中的关键字都同时拥有左子树和右子树？
//	②  是不是非终端节点有n个关键字就一定存在n+1个指针非空？




#include <stdio.h>               //用链表实现队列
#include <stdlib.h>
#include <malloc.h>

#define m 5						//B树的阶

#define EQ(a,b) ((a)==(b))																		
#define	LT(a,b) ((a)<(b))
#define LE(a,b) ((a)<=(b))

typedef int Keytype;
 
typedef struct BTNode
{
	int keynum;						//节点中的关键字个数
	struct BTNode *parent;			//指向双亲节点
	Keytype key[m+1];				//关键字向量，0号单元未用
	struct BTNode *ptr[m+1];		//子树指针向量
	//Record *recptr[m+1];			//记录指针向量，0号未用
}BTNode, *BTree;
typedef struct
{
	BTNode *pt;					//指向找到的节点
	int i;						//1...m，在节点中的关键字序号
	int tag;					//1：查找成功。0：查找失败
}Result;


//------------------------------------------------------------------------------为了个层序遍历加上的...-----------------------------------------------------
typedef struct NODE
{
	BTree data;
	struct NODE *pnext;
}nod, * pnod;


typedef struct S
{
	pnod phead;
	pnod ptail;
}ss, * pss;


void init(pss);
void en_queue(pss,BTree );
void out_queue(pss,BTree &);
bool is_empty(pss);





void init(pss Y)
{
	Y->phead=(pnod)malloc(sizeof(nod));
	if(Y->phead == NULL)
		exit(-1);
	Y->phead->pnext=NULL;
	Y->ptail=Y->phead;
}


void en_queue(pss Y,BTree val)
{
	pnod new_x=(pnod)malloc(sizeof(nod));
	if(new_x == NULL)
		exit(-1);
	new_x->data=val;
	new_x->pnext=NULL;
	Y->ptail->pnext=new_x;
	Y->ptail=new_x;
}


bool is_empty(pss Y)
{
	if(Y->phead == Y->ptail)
		return true;
	else
		return false;
}


void out_queue(pss Y,BTree & T)
{
	if(is_empty(Y))
		printf("It is empty now\n");
	else
	{
		pnod r=Y->phead->pnext;
		Y->phead->pnext=r->pnext;
		if(Y->phead->pnext==NULL)         //我就觉得这里需要注意一下  就是只剩下一个没有val的头结点和一个尾节点指向的节点的时候   没有这一步的话无法判断 is_empty
			Y->ptail=Y->phead;
		T = r->data;
		free(r);
	}
}
//-------------------------------------------------------------------------队列到此为止------------------------------------------------------------------------------


//遍历
void Visit(Keytype K)
{
	printf("%d  ",K);
}
void Traverse(BTree T,void (*visit)(Keytype))				//实现树（并非二叉树）的中序遍历。
//照B树的存储结构中序输出的话是：中序指针0 -> 关键字1 -> 中序指针1 -> 关键字2 -> ······  这样才能按顺序大小输出
{
	int i;
	if(!T)
		return;
	if(T->ptr[0])						//因为0是指针数组中才有的(关键字数组0被抛弃了) 所以单独列出 之后就是循环了
		Traverse(T->ptr[0],visit);
	for(i=1;i<=T->keynum;i++)
	{
		visit(T->key[i]);			//先关键字，后中序指针
		if(T->ptr[i])
			Traverse(T->ptr[i],visit);
	}
}
void LevelTraverse(BTree T,void (*visit)(Keytype))				//层序遍历
{
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,T);
	int i;
	BTree temp;
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		if(temp->ptr[0])
			en_queue(Queue,temp->ptr[0]);
		for(i=1;i<=temp->keynum;i++)
		{
			visit(temp->key[i]);
			if(temp->ptr[i])
				en_queue(Queue,temp->ptr[i]);
		}
	}
}





//查找操作
int Search(BTree p,Keytype K)
{										//关键字和指针个数是不想等的，关键字数组0号不用，而指针数组0号是用的，所以查找时有一些小小的注意的地方
	int i=0,j;
	for(j=1;j<=p->keynum;j++)
		if(K>=p->key[j])
			i = j;
	return i;
}
Result SearchBTree(BTree T,Keytype K)
//在m阶B树T上查找关键字K，返回结果(pt,i,tag).若查找成功，则特征值tag=1，指针pt所指
//节点中第i个关键字等于K；否则特征值tag=0，等于K的关键字应该插入在指针pt所指节点中
//第i和第i+1个关键字之间
{
	BTree p = T,q = NULL;
	bool found = false;
	int i=0;
	Result R;
	while(p && !found)							//判断条件为p 和 found，找到则found=true 找不到则 p=NULL
	{
		i = Search(p,K);					//在该节点中查找关键字，返回的i有两种情况：① 为0 ② 不为0 但是 p->key[i] <= K < p->key[i+1]
		if(i>0 && p->key[i]==K)
			found = true;
		else
		{
			q = p;					//记录之前的节点，若没找到则返回新关键字要插入的地方
			p = p->ptr[i];
		}
	}
	if(found)
	{
		R.pt = p;
		R.i = i;
		R.tag = 1;				
	}
	else
	{
		R.pt = q;
		R.i = i;
		R.tag = 0;
	}
	return R;
}







//插入操作
void insert(BTree &p,int i,Keytype K,BTree ap)
//将K和ap分别插入到p->key[i+1]和p->ptr[i+1]
//为什么是插在i+1处呢？（画图更易理解）		假设该节点有关键字：9,18,30  现在插入5；i的值此时为0 ，那么关键字部分5插在i+1(即1，0为空，废弃)位置上，指针也要插在1上（指针0位置也是有用的，为什么不放在0上呢？因为要插入的5是子节点（假设有子节点，就算没有子节点那ap也是NULL，插哪都一样...当然也是有规律的）的最中间的一个关键字，即左边小于5，右边大于5，现在子节点被分成三份，左边一份，5一份，右边一份。此时0位置的指针指向左边那份，所以现在新增的指针（右边那份）应该在1位置上，放在5的右边，符合构造规律）
{
	int j;
	for(j=p->keynum+1;j!=i+1;j--)		//空下i+1的位置给新的
	{
		p->key[j] = p->key[j-1];
		p->ptr[j] = p->ptr[j-1];					//一起搬迁的时候居然把指针落下了
	}
	p->key[i+1] = K;
	p->ptr[i+1] = ap;
	p->keynum++;
}
void split(BTree &p,int s,BTree &ap)					//少个引用要人命啊
//将p->key[s+1...m],p->ptr[s...m]和p->recptr[s+1...m]移入新节点*ap
{
	int i;
	ap = (BTree)malloc(sizeof(BTNode));
	ap->keynum = m-s;
	p->keynum = s-1;
	ap->ptr[0] = p->ptr[s];
	if(ap->ptr[0])
		ap->ptr[0]->parent = ap;
	for(i=s+1;i<=m;i++)
	{
		ap->key[i-s] = p->key[i];
		ap->ptr[i-s] = p->ptr[i];
		if(ap->ptr[i-s])
			ap->ptr[i-s]->parent = ap;
	}
	ap->parent = p->parent;
}
void NewRoot(BTree &T,Keytype K,BTree ap)
//生成含信息(T,x,ap)的新的根节点*T,原T和ap为子树指针
{
	BTree root = (BTree)malloc(sizeof(BTNode));
	root->ptr[0] = T;
	T = root;
	if(T->ptr[0])
		T->ptr[0]->parent = T;
	T->ptr[1] = ap;
	if(ap)
		T->ptr[1]->parent = T;
	T->keynum = 1;
	T->key[1] = K;
	T->parent = NULL;									//千万不能忘..
}
void InsertBTree(BTree &T,Keytype K,BTree &p,int i)
//在m阶B树T上节点*p的key[i] 与 key[i+1]之间插入关键字k。
//若引起节点过大，则沿双亲链进行必要的节点分裂调整，使T仍是m阶B树
{
	int s;
	Keytype x = K;
	BTree ap = NULL;
	bool finished = false;
	//整个函数着重于 节点中关键字个数是否超过 m-1
	while(p && !finished)								//看到问题时候想到了递归，但如果递归的话要传递太多数据 索性循环。处理完这个节点后，再判断双亲节点是否满足条件 用p指代双亲节点 
	//循环结束有两种情况：①双亲节点为空，即经过一再分裂后，到了根节点，根节点也需要分裂但没有双亲了，只好结束循环利用NewRoot函数。 ② 完成插入，完成所有所需分裂
	{
		insert(p,i,x,ap);								//将K和ap分别插入到p->key[i+1]和p->ptr[i+1]
		if(p->keynum>=m)
		{
			s = (m+1)/2;
			split(p,s,ap);								//将p->key[s+1...m],p->ptr[s...m]和p->recptr[s+1...m]移入新节点*ap
			x = p->key[s];			//记录下从节点中分离出来要插入双亲节点的关键字
			p = p->parent;
			if(p)
				i = Search(p,x);			//找到插入的位置
		}
		else							//个数不超过m-1则完成插入
			finished = true;
	}
	if(!finished)
		NewRoot(T,x,ap);								//生成含信息(T,x,ap)的新的根节点*T,原T和ap为子树指针
}






//删除操作
void Delete(BTree &p,int i)
//删除p节点中的第i个关键字。
//这里单纯的删除关键字 并没有涉及指针  因为删除某个关键字并不意味着就把该子树一并删掉 但又不能留在原树上了  所以就单独拿出来处理了
{
	int j;
	for(j=i;j<p->keynum;j++)
		p->key[j] = p->key[j+1];
	p->keynum--;
}
void Union(BTree &p,BTree &q,Keytype parent)
//两个节点中的关键字和一个双气节点的关键字合并	p是依旧存在的节点 q是要释放掉的
{
	p->keynum++;
	p->key[p->keynum] = parent;
	p->ptr[p->keynum] = q->ptr[0];
	p->keynum += q->keynum;
	for(int i=1;i<=q->keynum;i++)
	{
		p->key[p->keynum-q->keynum+i] = q->key[i];
		p->ptr[p->keynum-q->keynum+i] = q->ptr[i];
	}
}
void DeleteBTree(BTree &T,BTree &p,int i)			//所删关键字为p中第i个
{
	int j;
	int limit = (m+1)/2 - 1 ;						//这个limit是最少limit个关键字  最m-1个关键字
	if(p->ptr[0])
	{
		BTree temp = p->ptr[i];					//将要删关键字的后继来取代这个关键字的位置，并且将删除操作移至叶子节点中进行
		while(temp->ptr[0])
			temp = temp->ptr[0];
		p->key[i] = temp->key[1];		//替换
		p = temp;				
		i = 1;
	}
	int p_posi = 0;
	while(p != p->parent->ptr[p_posi])				//找到这个被删关键字所在的节点在其双亲节点中的指针序号，以方便找前驱后继
		p_posi++;

	//接下来就是着手删除在叶子节点中的某个关键字

	Delete(p,i);						//找到要删的关键字所在的节点后  立刻将其删除（因为这里是叶子节点中关键字删除 所以关于指针的删除就掠过【因为本身就是空的】）
	//查看删除后的节点是否还满足B树的性质
	//若满足 则可以直接结束了
	while(p->keynum<limit)					//不满足则继续分情况讨论
	{
		if(p_posi!=p->parent->keynum && p->parent->ptr[p_posi+1]->keynum>limit)		//这里是大于 不能等于  因为这里考虑的是右兄弟可以分一个关键字出来
		//这种情况是存在右兄弟且右兄弟有多余的关键字的情况
		//从这里看来 是偏向右兄弟的（因为这个判断放在前面的话就是说就算左右兄弟都够分 那么还是选择拿右兄弟的）
		//具体操作是：
		//		① 先将双亲节点中的那个关键字放到有需求的节点中的最后一个关键字位置上
		//		② 将右兄弟中的第一个关键字作为弥补放到双亲节点中最后一个关键字位置上
		//		③ 将右兄弟的第一个关键字删掉
		{
			p->keynum++;
			p->key[p->keynum] = p->parent->key[p_posi+1];						
			p->ptr[p->keynum] = p->parent->ptr[p_posi+1]->ptr[0];
			p->parent->key[p_posi+1] = p->parent->ptr[p_posi+1]->key[1];
			Delete(p->parent->ptr[p_posi+1],1);
			for(j=0;j<=p->parent->ptr[p_posi+1]->keynum;j++)			//之前Delete里面keynum已经减一了  所以用到等号
				p->parent->ptr[p_posi+1]->ptr[j] = p->parent->ptr[p_posi+1]->ptr[j+1];
		}
		else if(p_posi!=0 && p->parent->ptr[p_posi-1]->keynum>limit)				//向左兄弟询问
		//这种情况是正好该节点是最后一个就没有右兄弟只能有左兄弟了（且必定有左兄弟，因为B树的性质）或者说是 有右兄弟且右兄弟关键字不够分出来那么问一下左兄弟
		//具体操作是：
		//		① 将双亲节点中的某关键字放到有需求节点中的第一个关键字位置上
		//		② 将左兄弟的最后一个关键字放到双亲的第一个关键字位置上
		//		③ 删掉左兄弟的最后一个关键字
		{
			p->keynum++;
			for(j=p->keynum;j>1;j--)
				p->key[j] = p->key[j-1];
			for(j=p->keynum;j>0;j--)
				p->ptr[j] = p->ptr[j-1];
			p->ptr[0] = p->parent->ptr[p_posi-1]->ptr[p->parent->ptr[p_posi-1]->keynum];
			p->key[1] = p->parent->key[p_posi];
			p->parent->key[p_posi] = p->parent->ptr[p_posi-1]->key[p->parent->ptr[p_posi]->keynum];
			p->parent->ptr[p_posi-1]->keynum--;
		}
		else																	//两兄弟都供不来   只能采取合并操作
		{
			BTree bro;							//存在兄弟节点 但因为处理节点的位置不固定 所以兄弟节点的位置也不固定 能在左能在右
		
			if(p_posi!=0)						//但这里偏向与左兄弟合并
			//大致过程就是  将两个节点和一个双亲节点中的关键字合并
			//				然后将双亲中的关键字删掉（注意这里Union里处理了以下指针的去处  删除关键字必定会减少一个指针 但是并不意味着这个指针就要被删掉 而是要被移到别的地方去）
			//这里将处理节点和左兄弟和一个双亲中的关键字合并 最终得到左兄弟
			{	
				bro = p->parent->ptr[p_posi-1];
				Union(bro,p,p->parent->key[p_posi]);
				Delete(p->parent,p_posi);
				for(j=p_posi;j<=p->parent->keynum;j++)				//这里必须要处理指针
					p->parent->ptr[j] = p->parent->ptr[j+1];
			}
			else
			//这里本来是将处理节点和右兄弟合并最后总得到右兄弟的  但是为了方便 就将右兄弟合并进了处理节点  然后将bro转移为p（哪里方便了呢？因为右边节点合并进入左边节点 是将右边节点中的关键字接在左节点关键字的后面 ； 但是如果要将左节点合并进入右节点 就又要换一种方式 索性这里简单点）
			{
				bro = p->parent->ptr[p_posi+1];
				Union(p,bro,p->parent->key[p_posi+1]);
				Delete(p->parent,p_posi+1);
				for(j=p_posi+1;j<=p->parent->keynum;j++)
					p->parent->ptr[j] = p->parent->ptr[j+1];
				bro = p;
			}
			if(T->keynum==0)
			{
				T = bro;
				return;
			}
			p = bro->parent;
			p_posi = 0;	
			while(p != p->parent->ptr[p_posi])	
				p_posi++;
		}	
	}
}





int main()
{
	//Keytype r[15] = {24,45,53,12,37,50,61,90,100,70,3,30,26,85,7};
	//Keytype r[9] = {24,45,53,12,37,50,61,90,100};
	//Keytype r[3] = {24,45,53};
	Keytype r[20] = {3,14,7,1,8,5,11,17,13,6,23,12,20,26,4,16,18,24,25,19};
	BTree T = NULL;
	Result s;									//这里的插入删除示例均来自 B树文件夹中的插入和删除示例
	for(int i=0;i<5;i++)
	{
		s = SearchBTree(T,r[i]);
		if(!s.tag)
			InsertBTree(T,r[i],s.pt,s.i);
	}
	LevelTraverse(T,Visit);
	puts("");
	s = SearchBTree(T,3);
	if(s.tag)
		DeleteBTree(T,s.pt,s.i);
	else
		printf("No such data!\n");
	LevelTraverse(T,Visit);puts("");
	s = SearchBTree(T,20);
	if(s.tag)
		DeleteBTree(T,s.pt,s.i);
	else
		printf("No such data!\n");
	LevelTraverse(T,Visit);puts("");
	s = SearchBTree(T,18);
	if(s.tag)
		DeleteBTree(T,s.pt,s.i);
	else
		printf("No such data!\n");
	LevelTraverse(T,Visit);
	puts("");
	s = SearchBTree(T,5);
	if(s.tag)
		DeleteBTree(T,s.pt,s.i);
	else
		printf("No such data!\n");
	LevelTraverse(T,Visit);
	puts("");
	return 0;
}


//学会将一个重要且复杂的函数拆分成众多函数的组合
//学会抓住函数的重点关注点 the point