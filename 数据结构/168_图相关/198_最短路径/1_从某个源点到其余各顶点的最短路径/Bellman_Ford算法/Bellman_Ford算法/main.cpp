#include <stdio.h>
#include "MGraph.h"

#define MAX 999

int main()
{
	MGraph G;
	Edge *edge;
	CreateGraph_DN(G,edge);
	Display(G);
	if(!Bellman_Ford(G,0,dist,edge))
//		printf("存在负环 因此不能寻找最短路径\n");
	return 0;
}

bool Bellman_Ford(MGraph G,int orig,int *dist,Edge *edge)
{
	for(int i=0;i<G.vexnum;i++)						//每个点到本身距离为0
		G.arcs[i][i].adj = 0;
	for(i=0;i<G.vexnum;i++)							//先初始化整个dist数组，初始为MAX，那么以下的循环就要执行vexnum-1次，如果初始化为arc[][]，那么只需vexnum-2次
		dist[i] = (i==orig?0:MAX);
	//这里的循环次数必须要达到一定的数量，那么一定要这么多次吗？不一定，可以提前结束的！那为什么这么指定呢？因为可能一次遍历后，源点到某点的缩短一条边的距离，然而最短路径最多只包含|v|-1 条边，所以是这样
	for(i=0;i<G.vexnum-1;i++)
		//这里将所有边都遍历一遍		拿(u,v)边来说，权值为w，如果(u,v)这条边的存在可以使得源点到v的距离缩短 即dist[edge[j].v] > dist[edge[j].u] + edge[j].w，那么将此边算进去
		for(int j=0;j<G.arcnum;j++)
			if(dist[edge[j].u] != MAX && dist[edge[j].v] > dist[edge[j].u] + edge[j].w)
				dist[edge[j].v] = dist[edge[j].u]+edge[j].w;

	//这里检测整个图中是否存在负环。什么是负环呢？即存在环的前提条件下，环中所有边加起来为负的。比如 a->b 2; b->c 3; c->b -4;  第一遍（disc数组中）：b为2，c为5；第二遍：b为1，c为4；第三遍：b为0。。。。永不停止
	//整个算法过程中一旦有一个点值变小。就可能会影响其指向的点的值，然后被影响的点的值变小又影响到指向这个点的值(正是通过这一点，才有了优化这个算法的另一个算法，SPFA算法)，这样周而复始，永远得不到结果
	
	for(i=0;i<G.arcnum;i++)
		if(dist[edge[i].u!=MAX && dist[edge[i].v] > dist[edge[i].u]+edge[i].w)
			return false;			//所以在若干变后，如果还会发生变化那说明存在负环，寻找最短路径失败
	return true;
}
