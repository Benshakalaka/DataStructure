#include <stdio.h>								//寻找关节点
#include "ALGraph.h"

void FindArticul(ALGraph G);				//连通图G以邻接表作存储结构，查找并输出G上全部关节点。全局量对访问计数
void DFSArticul(ALGraph G,int v0);			//从第v0个顶点出发深度优先遍历图G 查找并输出关节点

int count;										//计数器  给每个顶点遍历的顺序排序做辅助
int low[MAX_VEX_NUM];							//看每个顶点所能连接到的最祖宗（生成树中所能依靠到的最上面的节点 因为这个顶点C如果能连接B， 又能连接A， 假设A是B的双亲 那删去B也不会使C脱离整个图 否则假设C连不到A 那删去B就能把C脱离掉 使B成为关节点）
int visit_order[MAX_VEX_NUM];					////遍历顺序  用来跟low比较  假设C的low为1  C的双亲B的visit_order为2 说明c能连接B的祖宗（或双亲） 那样B就不是关节点 否则如果C的low>=2  就会受B的影响 一旦B脱离 C也随之脱离 使B成为关节点

int main()
{
	int i;
	ALGraph G;
	CreateGraph(G);
	Display(G);
	printf("Output the articulation point : \n");
	FindArticul(G);													//寻找关节点函数
	/*printf(" i  G.vex[i].data  visit[i]  low[i]\n");
	for(i=0;i<G.vexnum;i++)
		printf("%d  %s  %d  %d",i,G.vertices[i].data,visit[i],low[i]);
	puts("");*/
	return 0;
}

void FindArticul(ALGraph G)				//连通图G以邻接表作存储结构，查找并输出G上全部关节点。全局量 count 对访问计数
{
	count = 0;					//置零
	int i;
	for(i=0;i<G.vexnum;i++)
		visit_order[i] = 0;								//排序前置零  并作为标记 如果visit_order[v]==0 表明尚未访问这个点  否则不必在访问
	low[0] = visit_order[0] = ++count;					//处理整个生成树的根  排序为1 当然low也是最小的（没有更小的了）
	ArcPoint p = G.vertices[0].firstarc;
	DFSArticul(G,p->adjvex);								//对根的第一个孩子进行处理
	if(count<G.vexnum)				//如果count<G.vexnum  表明count计数尚未到头  还有顶点等待访问  需要从根的另一个孩子出发
	{
		printf("%d   %s\n",0,G.vertices[0].data);		//根有两个以及两个以上的孩子  就能表明A是个关节点了 因为一旦删去A 就会导致产生两个或两个以上的分量
		p = p->nextarc;
		while(p)
		{
			if(!visit_order[p->adjvex])
				DFSArticul(G,p->adjvex);			//遍历所有根的孩子
			p = p->nextarc;
		}
	}
}

void DFSArticul(ALGraph G,int v0)			//从第v0个顶点出发深度优先遍历图G 查找并输出关节点
{
	int min = visit_order[v0] = ++count;						//从每一个顶点开始   	v0的low暂时由min存  
	ArcPoint p;
	for(p=G.vertices[v0].firstarc;p;p=p->nextarc)				//该节点与每一个与之相关的节点（所有与这个点产生边关系的点）比较  ①得到自身的low值②判断是否是关节点
	{
		if(!visit_order[p->adjvex])			//未访问过 说明是被此顶点影响的 是他的孩子节点
		{
			DFSArticul(G,p->adjvex);			//处理他。。。可以得到这个点的low值
			//下面两个判断是至关重要的  是否理解这个算法的关键就在这
			if(min>low[p->adjvex])				//v0顶点的low如果比孩子节点的low大  那么就可以改变v0顶点的low为较小的low 因为孩子节点可以连接到达v0的上面	v0顶点就可以借助这个点达到他的上面的节点  这个判断赋值是为了v0作为其他节点的孩子节点时做准备			
				min = low[p->adjvex];
			if(low[p->adjvex]>=visit_order[v0])	//孩子节点的low值比v0的visit_order遍历序号大  表明存在孩子节点凭借自身是连接不到B的上面（双亲或祖宗）的，所以一旦B被删掉 那么这个孩子就被影响删掉  造成B是关节点 因此输出
				printf("%d   %s\n",v0,G.vertices[v0].data);
		}
		else													//如果已经被访问过了 那表明虽然与这个点相连 但可能是祖宗节点或是与这个顶点无关的点（无关指的是这个顶点是否被删并不影响这个点）
			if(min>visit_order[p->adjvex])
				min = visit_order[p->adjvex];			//虽然无关  但毕竟与这个函数讨论的顶点是有关联的  这个点可以连接到的地方那么顶点也可以通过这个点链接到  所以顶点的low可以与这个点的low比较、得到
	}
	low[v0] = min;
}

//对于结果输出两次b 书上说是因为删去顶点b将使连通图分割成3个连通分量 所以b输出两次