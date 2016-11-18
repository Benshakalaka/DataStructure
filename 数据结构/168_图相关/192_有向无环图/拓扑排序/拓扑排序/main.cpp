#include <stdio.h>								//实现拓扑排序 （邻接表）
#include "ALGraph.h"
#include "stack.h"

void FindInDegree(ALGraph G,int *indegree);			//find each vertex's indegree.
void TopologicalSort(ALGraph G);					//拓扑排序

int main()
{
	ALGraph G;
	CreateGraph(G);
	Display(G);
	TopologicalSort(G);
	return 0;
}

void FindInDegree(ALGraph G,int *indegree)				//计算每一个顶点的度
{
	int i;
	ArcPoint p;
	for(i=0;i<G.vexnum;i++)				//因为是有向图 所以可以从每一个顶点开始遍历 并不会有重复的 
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->adjvex]++;			//所指向的顶点的入度加一
			p = p->nextarc;
		}
	}
}

void TopologicalSort(ALGraph G)					//利用栈来实现拓扑
{
	int indegree[MAX_VEX_NUM];
	int i;
	ps Stack = (ps)malloc(sizeof(s));	//创建一个栈
	init(Stack);
	for(i=0;i<G.vexnum;i++)
		indegree[i] = 0;
	FindInDegree(G,indegree);			
	int temp;
	for(i=0;i<G.vexnum;i++)					//从没有入度的顶点开始（没有入度表明是最基础的 应该是最先开始的）
	{
		if(!indegree[i])
			push(Stack,i);
	}
	ArcPoint p;
	while(!empty(Stack))	//是否为空作为循环的依据
	{
		pop(Stack,temp);
		printf("%d   %s\n",temp,G.vertices[temp].data);
		for(p=G.vertices[temp].firstarc;p;p=p->nextarc)		//另一种意义上来讲是将栈中的顶点删去（形式上并非实际） 理所当然该顶点作为尾的弧的头顶点的入度需要减一
		{
			indegree[p->adjvex]--;
			if(!indegree[p->adjvex])			//减一后如果为入度为0  则之后就轮到这个点 将其放入栈中
				push(Stack,p->adjvex);
		}
	}
	for(i=0;i<G.vexnum;i++)				//到最后应该是所有顶点的入度都为0   不然的话  就是图有错（即不能从图中的点指向这个点 ）
		if(indegree[i])
		{
			printf("Error!\n");
			break;
		}
}