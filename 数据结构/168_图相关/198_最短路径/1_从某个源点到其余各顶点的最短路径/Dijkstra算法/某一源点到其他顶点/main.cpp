#include <stdio.h>
#include "MGraph.h"

typedef int PathMartic[MAX_VERTEX_NUM][MAX_VERTEX_NUM];						//这个是用来记录最短路径的 比如若P[v][w]为TRUE 则w是从v0到v当前求得最短路径上的点。
typedef int ShortPathTable[MAX_VERTEX_NUM];									//这是用来记录源顶点到各个顶点的权值

void ShortestPath_Dijkstra(MGraph G,int v0,PathMartic &P,ShortPathTable &D);

int main()
{
	PathMartic P;
	ShortPathTable D;
	MGraph G;
	CreateGraph_DN(G);
	Display(G);
	ShortestPath_Dijkstra(G,0,P,D);
	int i,j;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			printf("%d%c",P[i][j],(j+1)%(G.vexnum)==0?'\n':' ');
	return 0;
}

//必须先知道形参的意义
void ShortestPath_Dijkstra(MGraph G,int v0,PathMartic &P,ShortPathTable &D)
//用Dijkstra算法求得有向网G的v0顶点到其余顶点v的     最短路径P[v]  及其  带权长度D[v]
//若P[v][w]为TRUE 则w是从v0到v当前求得最短路径上的点。
//final[v]为TRUE 当且仅当v∈S，即已经求得从v0到v的最短路径
{
	int final[MAX_VERTEX_NUM];								//这个数组是用来记录这个顶点是否已经在最短路径的集合中 1表示在了（还表示已经找到了到达这个点的最短路径） 
	int i,j;
	for(i=0;i<G.vexnum;i++)				//记录与源顶点直接相连的点  相当于初始化整个过程 初始化所有的数组变量
	{
		D[i] = G.arcs[v0][i].adj;			//与源顶点直接相连的点的权值  不相连则用INFINITE表示
		final[i] = 0;						//最初所有点都不在最短路径集合中
		for(j=0;j<G.vexnum;j++)						//将所有路径先清扫一遍
			P[i][j] = 0;
		if(G.arcs[v0][i].adj<INFINITY)					//如果这个点与源顶点相连接 那么在路径矩阵上 顶点i的 P[i][v0]和P[i][i]都要等于1	意味着从v0出发到i的路上会经过 v0,i(当然这只是初始化 现在并没有顶点进入最短路径集合)
		{
			P[i][v0] = 1;
			P[i][i] = 1;
		}
	}
	final[v0] = 1;			//自身先进入 （不解释...）
	D[v0] = 0;					
	int min,k,q;
	for(i=0;i<G.vexnum-1;i++)								//每一个循环过程都表示有一个点进入最短路径集合（找到最短路径） 所以只要循环vexnum-1次
	{
		min = INFINITY;									//找最小 是什么的最小呢？为什么事先等于INFINITE？最小用来干嘛呢 ？  最小就是从v0到v的最短路径  因为在寻找最短路径之前总是不知道在哪里当然是无限远了  用来进行比较挑选出这条路来
		for(j=0;j<G.vexnum;j++)							//举个例子， 如果是第一次循环  那是在与源顶点相连接的点中挑选 如果是最短的，那还能找到一条路从v0到这个点最短路径吗 定然是找不到的
			if(!final[j] && min>D[j])					//前提：从 不在最短路径集合中的点 中进行挑选最小的
			{
				min = D[j];
				k = j;
			}				//找到最短的就标记 并记下min(用于下面的循环 下面的循环就是因为找到这个最短路径的点引发的改变)
		final[k] = 1;		//找到了当然要标记进如那个集合啊啊啊啊啊 
		for(j=0;j<G.vexnum;j++)									//最短路径有两种可能 一种是直接的<v0,v>的一条弧 另一种是借由已经在集合中的点而链接到的点 比如<v0,w,v>这个w就一定是已经在集合中的
			if(!final[j] && min+G.arcs[k][j].adj<D[j])			//①前提当然又是不再集合中    ②进行比较 一中是j是源顶点相连的点还有一种是与源顶点的距离是INFINITE的  如果通过这个新进的点可以到达这个j 并且这之间距离加上新进的点到v0的距离 还小于 v0到j的距离  那自然是要换的
			{
				D[j] = min+G.arcs[k][j].adj;
				for(q=0;q<G.vexnum;q++)
					P[j][q] = P[k][q];	//循环就是将到达k的路线复制到j中去，之后P[j][j] = 1;是将自己算进去
				P[j][j] = 1;						
			}
	}
}