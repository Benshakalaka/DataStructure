#include <stdio.h>
#include "head.h"

typedef struct Node								//树的节点（孩子兄弟的链表结构类型）
{
	VexType x;
	struct Node *Lechild;			//第一个（最左）孩子
	struct Node *Ribro;				//兄弟
}Tree,*CSTree;

void DFSForest(ALGraph , CSTree &);					//建立无向图G的深度优先森林(孩子兄弟的链表结构类型)
void DFSTree(ALGraph ,int , CSTree &);				//从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
void PreOrderTraverse(CSTree,void (*Visitfun)(VexType) );						//先序遍历森林

int main()
{
	ALGraph G;
	CSTree T=NULL;
	CreateGraph(G);						//为了程序快速检查 另写了一个txt文本输入 便于纠错以免重读输入例子
	Display(G);									
	DFSForest(G,T);									//建立森林
	printf("Pre Order Traverse the tree.\n");
	PreOrderTraverse(T,Visitfun);											//先序
	return 0;
}

int has_visited[MAX_VEX_NUM];										//另起了一个mark数组  因为在用头文件中的数组的时候遇到 external symbol这种问题不知如何解决
void DFSForest(ALGraph G, CSTree &T)								//建立无向图G的深度优先森林(孩子兄弟的链表结构类型)
//T是森林的第一个孩子
{
	int i;
	CSTree p,temp;
	for(i=0;i<G.vexnum;i++)												//标记清零										
		has_visited[i]=0;
	for(i=0;i<G.vexnum;i++)	//必须每一个试过去 看是否已经被访问过  如果出现第二个未被访问过的顶点 说明在前一个树中未出现这个点 且这个点与前一个图无关 所以这个点是另一个极大连通分量中的点
	{
		if(!has_visited[i])											//因为是将图转化成树 所以不能重复（不仅因为无向而且是图）
		{
			p = (CSTree)malloc(sizeof(Tree));					//顶点赋值
			strcpy(p->x,GetVex(G,i));
			p->Lechild = p->Ribro = NULL;
			if(!T)
				T = p;
			else
				temp->Ribro = p;
			temp = p;
			DFSTree(G,i,p);										//根据顶点开始建树
		}
	}
}

void DFSTree(ALGraph G,int v, CSTree &T)							//从第v个顶点出发深度优先遍历图G，建立以T为根的生成树 （整个过程就是遍历）
{
	has_visited[v] = 1;								//只要这里记录这个顶点被遍历就可以了因为每递归一个点一次就要调用一次这个函数 多了也是冗余
	int w;
	printf("%s  ",GetVex(G,v));
	CSTree temp,new_one;
	int is_First=1;													//这个实在是必要的 因为存储结构的特殊性 必须考虑是否是第一个孩子节点 如果是就放在left 否则放在第一个孩子节点的右侧
	ArcPoint p = G.vertices[v].firstarc;
	while(p)
	{
		w = p->adjvex;
		if(!has_visited[w])													//一旦是被访问过的点 就无需在访问
		{
			new_one = (CSTree)malloc(sizeof(Tree));				//建立树的一个新节点
			new_one->Lechild = new_one->Ribro = NULL;
			strcpy(new_one->x,GetVex(G,w));
		/*if(is_First)								//这个是自己写的 因为跟下面一个其实是一样的  只是形式上有点差别
		{
			T->Lechild = new_one;
			temp = T->Lechild;
			is_First = 0;
		}
		else
		{
			temp->Ribro = new_one;
			temp = temp->Ribro;
		}*/
			if(is_First)								//是则放在左侧
			{
				T->Lechild = new_one;
				is_First = 0;
			}
			else										//否则在孩子右侧
				temp->Ribro = new_one;
			temp = new_one;
			DFSTree(G,w,new_one);
		}
		p = p->nextarc;
	}
}

void PreOrderTraverse(CSTree T,void (*Visitfun)(VexType))									//先序遍历森林
{
	if(T)
	{
		Visitfun(T->x);
		if(T->Lechild)
			PreOrderTraverse(T->Lechild,Visitfun);
		if(T->Ribro)
			PreOrderTraverse(T->Ribro,Visitfun);
	}
}

