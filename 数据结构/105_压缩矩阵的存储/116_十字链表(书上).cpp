#include <stdio.h>							//用链表来存储矩阵			跟自己写的差别在第14、15行
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
	OLink *rhead;	//注意  书上和自己的不同就在这里						//用这个数组（这个根据所给的行数来分配数组的长度）来总的代表一个矩阵的行(指针)
	OLink *dhead;															//同上  表示列（指针）
	int mu,nu,tu;							//mu,nu,tu分别表示总行数 、总列数 、总非零元素
}List;

bool CreateList(List &);				//创建链式矩阵
bool AddNode(List &,List &);				//实现加法		
void Print(List &);						//输出
//矩阵乘法 但是没实现  因为这个并不难实现
//矩阵乘法： 因为这里是每行每列都明确知道的 并不像前面的顺序存储(需要知道每行非零元素在数组中的确切位置) 所以乘法可以通过M的每一行乘以N的每一列来实现，任何一个没有数据或没有对应
//位置上的数据则表示结果矩阵对应位置没有数据  否则就添加一个（就像创建的时候一样的）
//void MulNode(List &,List &);				
	
int main()
{
	List M,N;
	if(!CreateList(M))
		return 0;
	if(!CreateList(N))
		return 0;
	Print(M);
	Print(N);
	if(AddNode(M,N))
		Print(M);
	return 0;
}


//这是书上的				每行列都有一个头指针   书上的比较好 节省空间   配套的还有结构体的不同
//当然这之间的算法还是差不多的  (算法讲解在另一个上面（自己写的那个）)
bool CreateList(List &M)
{
	printf("The rows and lines and elements: \n");
	scanf("%d%d%d",&M.mu,&M.nu,&M.tu);
	if(M.tu > (M.mu*M.nu))
		return false;
	if(!(M.rhead = (OLink *)malloc((M.mu+1) * sizeof(OLink))))		//我写的和书上的差别就在这里
		return false;
	if(!(M.dhead = (OLink *)malloc((M.nu+1) * sizeof(OLink))))		//当然还有这里
		return false;
	int i;
	for(i=1;i<=M.mu;i++)
		M.rhead[i] = NULL;
	for(i=1;i<=M.nu;i++)
		M.dhead[i] = NULL;
	printf("Now,you can input elem at random.\n");
	OLink temp,q;
	//这里缺乏一些限制条件   比如不允许输入相同位置的值  或者可以修改代码通过覆盖来避免下面这句话提到的问题
	for(i=1;i<=M.tu;i++)			//***输入位置相同值不同的第二个并不会覆盖第一个  只会跟在后面 但是因为输出的边界限制 不会把这个值输出来 但是会导致严重的后果 因为最后一个的right或者down并不是NULL
	{
		if(!(temp = (OLink)malloc(sizeof(OLNode))))	return false;
		scanf("%d%d%d",&temp->m,&temp->n,&temp->e);
		//横向
		if(!M.rhead[temp->m] || M.rhead[temp->m]->n>temp->n){temp->right = M.rhead[temp->m];M.rhead[temp->m] = temp;	}
		else
		{
			for(q=M.rhead[temp->m];q->right && q->right->n < temp->n;q=q->right);		//书上的这个比较好  因为我那个用到了prev节点  而这个直接就是用next来判断的
			temp->right = q->right;
			q->right = temp;
		}
		//纵向
		if(!M.dhead[temp->n] || M.dhead[temp->n]->m>temp->m)
		{
			temp->down = M.dhead[temp->n];
			M.dhead[temp->n] = temp;
		}
		else
		{
			for(q=M.dhead[temp->n];q->down && q->down->m < temp->m;q=q->down);
			temp->down = q->down;
			q->down = temp;
		}
	}
	return true;
}

void Print(List &M)
{
	OLNode *p ;
	for(int i=1;i<=M.mu;i++)
	{
		p = M.rhead[i];
		for(int j=1;j<=M.nu;j++)
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

//相加的话就不弄个新的结果矩阵了  原本的M变成新的
bool AddNode(List &M,List &N)
{
	if(M.mu!=N.mu || M.nu!=N.nu)
		return false;
	OLink p,q;											//p代表M， q代表N。
	OLink x,y,z;
	int temp;
	for(int i=1;i<=M.mu;i++)
	{
		p = M.rhead[i];
		q = N.rhead[i];
		while(q)								//一行一行来进行
		{
			//主要分为三种情况
			//①、p是空的但q不空或者p的列数大于q的列数所以要把q插入到p中来 
			//②、p的列数小于q的列数  所以p指向下一个
			//③、相同的位置 就相加 如果是0 就要把把这个节点删掉  不是0就不要动 同时p,q都指向下一个
			if(!p || (p->n > q->n))
			{
				//①把N中的节点移到M中去			②就相当于上面的创建过程的增加一个节点 
				y = q->right;							//提前让y记住下一个节点   否则就找不到了 
				//从122 到 135行是没必要的 可有可无  因为N中的节点只需要从一行 一个一个来  跟纵向无关
				/*if(N.rhead[i] == q)		
					N.rhead[i] = q->right;
				else
				{
					for(x=N.rhead[i];x->right && x->right->n!=q->n;x=x->right);
					x->right = q->right;
				}
				if(N.dhead[q->n] == q)
					N.dhead[q->n] = q->down;
				else
				{
					for(x=N.dhead[q->n];x->down && x->down->m!=q->m;x=x->down);
					x->down = q->down;
				}*/
				if(!M.rhead[i] || M.rhead[i]->n>q->n)
				{
					q->right = M.rhead[i];
					M.rhead[i] = q;	
				//	printf("%d\n",M.rhead[1]->right->e);
				}
				else
				{
					for(x=M.rhead[i];x->right && x->right->n<q->n;x=x->right);
					q->right = x->right;
					x->right = q;
				}
				if(!M.dhead[q->n] || M.dhead[q->n]->m>q->m)
				{
					q->down = M.dhead[q->n];
					M.dhead[q->n] = q;
				}
				else
				{
					for(x=M.dhead[q->n];x->down && x->down->m<q->m;x=x->down);
					q->down = x->down;
					x->down = q;
				}
				
				q = y;												//让q向右移一个
			}
			else if(p->n < q->n)
				p = p->right;												//让p向右移一个
			else if(p->n == q->n)
			{
				temp = p->e+q->e;
				if(temp!=0)
				{
					p->e = temp;
					p = p->right;
				}
				else
				{
					//把M中的节点free  且p向右移
					z = p->right;
					if(M.rhead[i] == p)
						M.rhead[i] = p->right;
					else
					{
						for(x=M.rhead[i];x->right && x->right->n!=p->n;x=x->right);
						x->right = p->right;
					}
					if(M.dhead[p->n] == p)
						M.dhead[p->n] = p->down;
					else
					{
						for(x=M.dhead[p->n];x->down && x->down->m!=p->m;x=x->down);
						x->down = p->down;
					}
					free(p);
					p = z;
				}
				//把N中的节点free  且q向右移
				z = q->right;
				//从196 到 209行是没必要的 可有可无  因为N中的节点只需要从一行 一个一个来  跟纵向无关
				/*if(N.rhead[i] == q)		//这一步本来就是没必要的，但是我的本意是把N中的q移掉 却出错了想来想去应该影响不到M的啊 比如在M：【0 1】N：【1 2】的情况的时候  但是却忘了
					N.rhead[i] = q->right;
				else
				{
					for(x=N.rhead[i];x->right && x->right->n!=q->n;x=x->right);
					x->right = q->right;
				}
				if(N.dhead[q->n] == q)
					N.dhead[q->n] = q->down;
				else
				{
					for(x=N.dhead[q->n];x->down && x->down->m!=q->m;x=x->down);
					x->down = q->down;
				}*/
				free(q);
				q = z;
			}//else if
		}//while
	}//for
	return true;
}
