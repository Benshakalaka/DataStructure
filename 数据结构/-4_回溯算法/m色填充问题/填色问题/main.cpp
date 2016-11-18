#include <stdio.h>
#include "head.h"

int x[20];							//用于存储每个顶点的颜色
int sum=0;							//最终试探出sum种方法

bool is_OK(MGraph G,int vex)					//判断此时的点的颜色是否与相邻点的颜色冲突
{
	int i;
	for(i=0;i<vex;i++)
		if(G.arcs[vex][i].adj==1 && x[vex]==x[i])
			return false;
	return true;
}

void BackTrade(MGraph G,int vex,int m)			//采用回溯法试探出每一种方法  从顶点vex开始		m为可着色种类
{
	//for(int k=vex+1;k<G.vexnum;k++)					//每一个之后的都要清零 这样才能不被上一次试探影响
	//	x[k] = 0;
	if(vex>=G.vexnum)				//这里说明已经走到最后了	可以算作一种方案
	{
		sum++;
		printf("The %dth kind : \n",sum);
		for(int j=0;j<G.vexnum;j++)
			printf("%d ",x[j]);
		puts("");
	}
	else							//没走到最后就走下去
	{
		int i;
		for(i=1;i<=m;i++)						//进行深度优先遍历的方式进行试探
		{
			x[vex] = i;
			if(is_OK(G,vex))
				BackTrade(G,vex+1,m);
		}
	}
}

int main()
{
	MGraph G;
	CreateGraph_UDG(G);

	int i;
	for(i=0;i<G.vexnum;i++)
		x[i] = 0;					//初始化每个顶点现在的颜色是 0 ，即无颜色

	int m;
	printf("Input the number of colors : \n");
	scanf("%d",&m);					//输入m种颜色

	BackTrade(G,0,m);
	return 0;
}

