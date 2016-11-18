#include <stdio.h>							//这里是针对无向网的最小生成树
#include "MGraph.h"

void MiniSpanTree(MGraph G,VexType v);						//普里姆算法

int main()
{
	MGraph G;
	CreateGraph_UDN(G);					//为了方便 这个程序的输入为文本读入
	Display(G);
	MiniSpanTree(G,G.vexs[0]);			//最小生成树
	return 0;
}

//主要是看图自己演示
//这个程序是自己大致看了写的 
/*void MiniSpanTree(MGraph G,VexType v)					//普里姆算法求最小生成树		这个过程是建立在INFINIT=0基础上
{
	int k = LocateVex(G,v);
	struct													//需要临时数组在挑选最短路径时候起作用
	{
		VexType adjvex;					//存储生成树里的某个顶点
		int weight;						//权值
	}closedge[MAX_VERTEX_NUM];					//主要用来存在已有的最短生成树集（并非最终）中的顶点与剩余顶点之间的路径关系（比如已有生成树中已经存了v1,v3两个点，都与v2有干系，<v1,v2>的权为6 <v2,v3>的权为3 最后存在这个数组里的是<v2,v3>这条弧 方便最后的挑选最短路）
	int i,j;
	for(i=0;i<G.vexnum;i++)							//从这个点开始的(这个点是现在（刚开始）仅有的一个存下的点）
		if(i!=k)
		{
			strcpy(closedge[i].adjvex,v);
			closedge[i].weight = G.arcs[k][i].adj;
		}
	closedge[k].weight = -1;				//将所有的点和这个已存的点建立关系（当然 这里数组的adjvex都是存v的 以后增加点了再改）  -1的意思是已被存了 以后就不防问了
	int m,min=0;
	for(i=1;i<G.vexnum;i++)												//这个循环是将所有点存入
	{
		for(j=0;j<G.vexnum;j++)
			if(closedge[j].weight>0)
			{
				m = j;
				break;
			}
		//printf("%d   %s ===== %s    %d\n",m,closedge[m].adjvex,G.vexs[m],closedge[m].weight);
		for(j=0;j<G.vexnum;j++)					//找到closedge数组中权值最小的一个
			if(closedge[j].weight>0 && closedge[j].weight<closedge[m].weight)
				m = j;														//这个循环加上上面一个循环是找到最短路径（在与已存点有联系的所有边中挑选）
		printf("%d  %s ----- %s    %d\n",m,closedge[m].adjvex,G.vexs[m],closedge[m].weight);		//输出此刻找到的最短路径
		for(j=0;j<G.vexnum;j++)							//找到一条新的路径后，就要存入一个点 并将与这个点有关的所有边与临时数组里存的边比较（若临时的更大 则替换） 这样以后在找最短路径的时候就可以省掉更多比较
			if((G.arcs[m][j].adj&&(closedge[j].weight>G.arcs[m][j].adj)) || (!closedge[j].weight&&G.arcs[m][j].adj))
			{
				strcpy(closedge[j].adjvex,G.vexs[m]);
				closedge[j].weight = G.arcs[m][j].adj;
			}
		closedge[m].weight = -1;			//变成-1   以后不再接触这个点
	}
}*/





//这个是完全按照书上抄的，但在上面的自己写的之后抄上的，上面的一些解释可用于这里
typedef struct								//这个过程是建立在INFINIT=1000的基础上
{
	VexType adjvex;
	int weight;
}p,*pN;
int mininum(pN closedge,MGraph G)									//这个函数用来在已有的closeedge中寻找最短的那条边，以用来成为最短路径中的一条
{
	int i=0,j,k,min;
	while(!closedge[i].weight)				//本来就存在于最小生成树集合中的顶点到自身的距离是0，不能参与比较；否则最小的就是0了，找不出最短
		i++;
	min = closedge[i].weight;
	k = i;
	for(j=i+1;j<G.vexnum;j++)
		if(closedge[j].weight>0)			//在非0中寻找最短
			if(min>closedge[j].weight)
			{
				min = closedge[j].weight;
				k = j;
			}											//也是两个循环 跟上面的差不多
	return k;
}
void MiniSpanTree(MGraph G,VexType v)								//寻找最小生成树的顶点集合
{
	p closedge[MAX_VERTEX_NUM];
	int k = LocateVex(G,v);
	int j;
	for(j=0;j<G.vexnum;j++)								//先初始化(函数形参提供的点到各顶点之间的距离)，之后进行比较挑选
		if(j!=k)
		{
			strcpy(closedge[j].adjvex,v);
			closedge[j].weight = G.arcs[k][j].adj;
		}	
	closedge[k].weight = 0;											//自身距离为0。
	for(int i=1;i<G.vexnum;i++)										//最小树当然要经过每一个点(形参提供的不算进去)，所以循环以此为依据
	{
		k = mininum(closedge,G);
		printf("%s --- %s\n",closedge[k].adjvex,G.vexs[k]);
		closedge[k].weight = 0;
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[k][j].adj<closedge[j].weight)								//加入新的点后，更新closeedge的数据。选择相较之前更小的数据取代之。
			{
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].weight = G.arcs[k][j].adj;
			}
	}
}


