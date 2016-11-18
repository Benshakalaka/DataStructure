#include <stdio.h>							//用链表来存储矩阵			这里面很多输入判定都没有  并不完善
#include <malloc.h>
typedef int Elemtype;

typedef struct OLNode
{
	int m,n;								//m,n表示该元素所在行和列
	Elemtype e;								//所存value
	struct OLNode *right;					//该节点的右边的一个节点（同行）
	struct OLNode *down;					//下面一个节点（同列）
}OLNode,*OLink;
typedef struct
{
	OLink rhead;							//用这个数组（这个根据所给的行数来分配数组的长度）来总的代表一个矩阵的行(头结点)
	OLink dhead;							//同上  表示列（头结点）
	int mu,nu,tu;							//mu,nu,tu分别表示总行数 、总列数 、总非零元素
}List;

bool CreateList(List &);
void Print(List &);

int main()
{
	List M;
	CreateList(M);
	Print(M);
	return 0;
}

//这是自己写的			我写的是每个行列都有一个头结点  但相对来说较为浪费
bool CreateList(List &M)
{
	printf("The rows and lines : \n");
	scanf("%d%d%d",&M.mu,&M.nu,&M.tu);
	if(M.tu > (M.mu*M.nu))
		return false;
	if(!(M.rhead = (OLink)malloc((M.mu+1) * sizeof(OLNode))))		//创建头结点  便于插入
		return false;
	if(!(M.dhead = (OLink)malloc((M.nu+1) * sizeof(OLNode))))
		return false;
	int i;
	for(i=1;i<=M.mu;i++)					//必须令每个头结点存储的地址为NULL
	{
		M.rhead[i].right = NULL;
		M.rhead[i].down = NULL;
	}
	for(i=1;i<=M.nu;i++)								//必须令每个头结点存储的地址为NULL
	{
		M.dhead[i].down = NULL;
		M.dhead[i].right = NULL;
	}
	printf("Now,you can input elem at random.\n");
	OLink temp,current,prev;
	//可以不按照顺序随机插入
	//这里缺乏一些限制条件   比如不允许输入相同位置的值  或者可以修改代码通过覆盖来避免下面这句话提到的问题
	for(i=1;i<=M.tu;i++)				//***输入位置相同值不同的第二个并不会覆盖第一个  只会跟在后面 但是因为输出的边界限制 不会把这个值输出来 但是会导致严重的后果 因为最后一个的right或者down并不是NULL
	{
		if(!(temp = (OLink)malloc(sizeof(OLNode))))
			return false;
		scanf("%d%d%d",&temp->m,&temp->n,&temp->e);
		//因为是随机插入的 所以要对插入节点进行排序的工作   横向纵向都要排
		//横向
		if(!M.rhead[temp->m].right || M.rhead[temp->m].right->n>temp->n)		//头结点存储地址是空的或者第一个节点大于要插入的节点
		{
			temp->right = M.rhead[temp->m].right;
			M.rhead[temp->m].right = temp;		
		}
		else										//否则就寻找插入的地方（其实就是链表的插入功能）
		{
			current = M.rhead[temp->m].right;
			while(current && current->n<temp->n)
			{
				prev = current;
				current = current->right;
			}
			temp->right = prev->right;
			prev->right = temp;
		}
		//纵向
		if(!M.dhead[temp->n].down || M.dhead[temp->n].down->m>temp->m)
		{
			temp->down = M.dhead[temp->n].down;
			M.dhead[temp->n].down = temp;
		}
		else
		{
			current = M.dhead[temp->n].down;
			while(current && current->m<temp->m)
			{
				prev = current;
				current= current->down;
			}
			temp->down = prev->down;
			prev->down = temp;
		}
	}
	return true;
}

//输出
void OutR(List &M)
{
	int i;
	printf("Which row? _\b");
	scanf("%d",&i);
	OLink p = M.rhead[i].right;
	for(i=1;i<=M.nu;i++)
	{
		if(p && p->n == i)
		{
			printf("%d ",p->e);p = p->right;
		}
		else
			printf("0 ");
		
	}
	puts("");
}
void OutL(List &M)
{
	int i;
	printf("Which line? _\b");
	scanf("%d",&i);
	OLink p = M.dhead[i].down;
	for(i=1;i<=M.mu;i++)
	{
		if(p && p->m == i)
		{
			printf("%d ",p->e);p = p->down;
		}
		else
			printf("0 ");
	}
	puts("");
}
void OutA(List &M)
{
	int i,j;
	OLink p;
	for(i=1;i<=M.mu;i++)					//一行一行来
	{
		p = M.rhead[i].right;
		for(j=1;j<=M.nu;j++)			//紧接着就是一列一列来 因为0也要输出的
		{
			if(p && p->n == j)
			{
				printf("%d ",p->e);
				p = p->right;
			}
			else
				printf("0 ");
		}
		puts("");
	}
	puts("");
}
void Print(List &M)
{
	int i;
	printf("1、output some row\n2、output some line\n3、output all elem\n");
	;
	while(scanf("%d",&i)!=EOF)
	switch(i)
	{
	case 1:
		OutR(M);
		break;
	case 2:
		OutL(M);
		break;
	case 3:
		OutA(M);
		break;
	}
}

