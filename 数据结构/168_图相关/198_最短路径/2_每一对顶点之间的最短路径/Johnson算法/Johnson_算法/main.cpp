//整个算法是建立在邻接图上的
#include <stdio.h>
#include "head.h"

#define MAX 999

typedef int PathMatrix[MAX_VEX_NUM][MAX_VEX_NUM];							//求最短路径P[][]及其带权长度D[v][w]。若P[v][w][u]为1，则u是从v到w当前求得最短路径上的顶点。
typedef int DistanceMatrix[MAX_VEX_NUM];									//这是用来记录源顶点到各个顶点的权值

//可以发现，这个Bellman_Frod算法和下面的Dijkstra算法都是求单源最短路径的  这里两者放在一起，用于求出带负权的图的每对节点之间的最短路径
bool Bellman_Ford(ALGraph G,int orig,int *h,Edge *&edge)
//h数组即为最终最短路径数组
{
	for(int i=0;i<G.vexnum;i++)
		h[i] = (i==orig?0:MAX);

	for(i=0;i<G.vexnum-1;i++)												//Bellman_Frod算法主要的理解就在于： 是循环n此将每条边都拿出来审核一遍，看这条边是否有存在的价值，即源点到a点的距离加上a到b的距离是否比源点到b点的距离短，短的话那这条边就有存在的价值，否则就没有。
		for(int j=0;j<G.arcnum;j++)
		{
			//printf("%d  %d\n",h[edge[j].m],edge[j].m);
			if(h[edge[j].m]!=MAX && h[edge[j].n] > h[edge[j].m]+edge[j].w)
				h[edge[j].n] = h[edge[j].m]+edge[j].w;
		}

	for(i=0;i<G.arcnum;i++)
		if(h[edge[i].m]!=MAX && h[edge[i].n] > h[edge[i].m]+edge[i].w)
			return false;

	return true;
}

void Dijkstra(ALGraph G,int orig,PathMatrix& P,DistanceMatrix &D)				//算法中将P这个参数最后注释掉了，因为比较烦，但如果需要的话，对于这个函数的话去掉注释就行了
{
	int *final = (int*)malloc(sizeof(int)*G.vexnum);
	for(int i=0;i<G.vexnum;i++)
	{
		final[i] = 0;
		D[i] = MAX;
//		for(int j=0;j<G.vexnum;j++)
//			P[i][j] = 0;
	}
	
	for(ArcPoint p=G.vertices[orig].firstarc;p;p=p->nextarc)
	{
		D[p->adjvex] = *p->info;
//		P[p->adjvex][orig] = 1;
//		P[p->adjvex][p->adjvex] = 1;
	}

	final[orig] = 1;
	D[orig] = 0;

	for(i=0;i<G.vexnum-1;i++)								//Dijkstra理解起来更容易些，主要就是找出最小的，加入，更新。。。循环往复
	{
		int min = MAX,k;
		for(int j=0;j<G.vexnum;j++)
			if(!final[j] && min>D[j])
			{
				min = D[j];
				k = j;
			}
		final[k] = 1;
		for(p=G.vertices[k].firstarc;p;p=p->nextarc)
			if(!final[p->adjvex] && D[p->adjvex] > min + (*p->info))
			{
				D[p->adjvex] = min + (*p->info);
//				for(int m=0;m<G.vexnum;m++)
//					P[p->adjvex][m] = P[k][m];
//				P[p->adjvex][p->adjvex] = 1;
			}
	}

}

//Johson算法可以处理带负权的值（不带权值为负的环）的图
void Johnson(ALGraph G,Edge *&edge)			
{
	ALGraph _G;
	Edge *edge_2 = CreateGraph(_G);						//首先，我们将此图默认是带有负权的图（没有负权的情况呢？以下会讲到）
	InsertVex(_G,"v9");									//既然是带负权的，而且我们要使用Dijkstra算法来一对一对的求，必定是不能存在负权的。因此我们加入一个点，尝试一些方法将负权变为正数（最后会变为来）
	for(int i=0;i<_G.vexnum-1;i++)
		InsertArc(_G,_G.vexnum-1,i,0,edge_2);		//加入一个点，且该点到每个点的距离都为 0 （注意，都为0）

	int *h = (int*)malloc(sizeof(int)*_G.vexnum);
	if(!Bellman_Ford(_G,_G.vexnum-1,h,edge_2))				//调用Bellman算法，求新增的点到每个点的最短路径（这里就有我们思考的地方了）
															//既然新增的点到每个点的距离都是0，那么如果要继续求该点到某点的最短，肯定是要存在负权了。（这里我们就解决了刚刚的一个问题，如果图中没有负权？结果会是
															//整个h数组里存的数都为0，然后呢？然后再看下面解释）。因此，最后得到的h数组，要么是0，要么是负值
	{
		printf("存在负环！\n");
		return;
	}

				//然后将图中的负权变为正数
	ArcPoint p = 0;
	for(i=0;i<G.arcnum;i++)
		for(p=_G.vertices[edge[i].m].firstarc;p;p=p->nextarc)
			if(p->adjvex == edge[i].n)
				*p->info = *p->info + h[edge[i].m] - h[edge[i].n];	//对了，就是靠这个了，h要么为0，要么为负权。为什么一定就是正的呢？。。。不知道，在深入的话看算法导论第三版，P423
	DeleteVex(_G,"v9");

				//最后，既然全是正的了，就都用Dijkstra算法计算出来最后结果
	int FD[MAX_VEX_NUM][MAX_VEX_NUM];
	for(i=0;i<_G.vexnum;i++)
	{
		PathMatrix	P;															//这里选择不处理P这个整个的路径图
		DistanceMatrix D;														//而是单独的处理最短路径结果
		Dijkstra(_G,i,P,D);
		for(int j=0;j<G.vexnum;j++)
		{
			D[j] = D[j] + h[j] - h[i];						//这里就是回到最初的值，原来是减的，先在加回来；当然原来是加的，先在就要减去
			FD[i][j] = D[j];
			FD[i][i] = 0;								//最后通过一个二元数组拿到结果			
		}
	}

	for(i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
			printf("%d ",FD[i][j]);
		puts("");
	}
}

int main()
{
	Edge *edge;
	ALGraph G;
	edge = CreateGraph(G);
	//Display(G);
	Johnson(G,edge);
	return 0;
}