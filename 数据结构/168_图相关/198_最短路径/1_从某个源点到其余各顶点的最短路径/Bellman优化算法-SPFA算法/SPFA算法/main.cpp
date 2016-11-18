#include <stdio.h>
#include "queue.h"
#include "head.h"

int MAX = 999;

struct Occupied
{
	bool occupied;
	int counts;
};
int main()
{
	return 0;
}

//这个算法使用邻接表可能更直接点
//整个算法是对Bellman算法的优化升级
bool SPFA(ALGraph G,int orig,int *dist)
{
	Occupied *occupied = (Occupied * )malloc(sizeof(Occupied)*G.vexnum);
	for(int i=0;i<G.vexnum;i++)					//初始化
		dist[i] = (i==orig?0:MAX);
	for(i=0;i<G.vexnum;i++)					
	{
		occupied[i].occupied = 0;					//判断该点是否存在于队列中
		occupied[i].counts = 0;						//如何判断一个图是否存在负环呢？那就是如果一个点进入队列G.vexnum次，那么就表明整个存在负环，因为最短路径经过的边最多也就vexnum-1条
	}
	
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	en_queue(Queue,orig);
	occupied[orig].occupied = 1;

	int temp;ArcPoint p;
	//如何产生优化Bellman算法的想法呢？ 通过一个点的改变会影响另一个点的值  这一点而来  即然每个点的值的改变来源于指向他的点的值的改变，那我们可以只针对那些改变的点来进行维护
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		for(p=G.vertices[temp].firstarc;p;p=p->nextarc)				//该点指向的所有点都有调整的可能性
		{
			if(dist[p->adjvex] > dist[temp]+*p->info)
				dist[p->adjvex] = dist[temp]+*p->info;
			if(!occupied[p->adjvex])					//本身没有在队列中那么就加入队列
			{
				occupied[p->adjvex] = 1;
				occupied[p->adjvex].counts++;
				if(occupied[p->adjvex].counts==G.vexnum)				//存在负环则退出
					return false;
				en_queue(Queue,p->adjvex);				//导致一个点的改变后，有可能会导致下一个点的改变，亦将其放入队列中去
			}
		}
	}

	return true;
}