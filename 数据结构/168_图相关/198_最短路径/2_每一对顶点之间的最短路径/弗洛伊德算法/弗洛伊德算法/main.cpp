#include <stdio.h>											//弗洛伊德算法实现
#include "MGraph.h"

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];							//求最短路径P[][]及其带权长度D[v][w]。若P[v][w][u]为1，则u是从v到w当前求得最短路径上的顶点。
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];									//这是用来记录源顶点到各个顶点的权值

void ShortestPath_FLOYD(MGraph , PathMatrix &,DistanceMatrix &);

int main()
{
	MGraph G;
	CreateGraph_DN(G);
	Display(G);
	PathMatrix P;
	DistanceMatrix D;
	ShortestPath_FLOYD(G,P,D);
	int i,j;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			printf("%d%c",D[i][j],(j+1)%G.vexnum==0?'\n':' ');
	return 0;
}

void ShortestPath_FLOYD(MGraph G, PathMatrix &P,DistanceMatrix &D)			//这个算法看起来很简单 但理解起来其实还是挺难的 不信过几个月回来看看还记不记得
{
	//求最短路径P[][]及其带权长度D[v][w]。若P[v][w][u]为1，
	//则u是从v到w当前求得最短路径上的顶点。
	int i,j,k;
	for(i=0;i<G.vexnum;i++)					//初始化 二维和三维数组  
		for(j=0;j<G.vexnum;j++)
		{
			D[i][j] = G.arcs[i][j].adj;				//因为是对各对顶点求权  所以必须要用二维数组来记录整个图之间的权关系
			for(k=0;k<G.vexnum;k++)
				P[i][j][k] = 0;						//先置零
			if(D[i][j] < INFINITY)					//如果两点之间有弧存在（不是间接的相连） 那直接在P中存下,可以确定当前点是走的到另一个点的。(有的点不一定能走到另一个点，不一定能找到路，更别谈最短)
			{
				P[i][j][k] = 1;
				P[i][j][j] = 1;
			}
		}
	int m;
	//主要是理解以下的3个for循环
	for(k=0;k<G.vexnum;k++)															//这三个for循环就不解释了  看程序运行的过程就知道了 
															//三个for循环主要围绕 D[i][k]+D[k][j] < D[i][j] 进行   最外层是k,然后是i,然后是j；
	{
		for(i=0;i<G.vexnum;i++)
			for(j=0;j<G.vexnum;j++)
			{
				printf("The changed routes : (%d,%d) + (%d,%d) $$ (%d,%d)",i+1,k+1,k+1,j+1,i+1,j+1);		//这个printf就不删掉了 显示整个过程   要理解算法可以看这个
				if(D[i][k]+D[k][j] < D[i][j])									//其实整个过程就是① 将所有点与另外n-1个点的弧长列出来（可以是个整数 可以是个INFINTY）② 在每对点中间（比如(vi,vj)）插入v0,进行比较看是否路径变短 ③ 一整个循环后 在每对点中间(依旧(vi,vj))插
																				//入v1,再经过一整个循环 ④ 重复直到最后一个点v[n-1] 这个时候最短路径已经找到了
				{																
					printf("-------%d-----%d",D[i][j],D[i][k]+D[k][j]);
					D[i][j] = D[i][k]+D[k][j];
					for(m=0;m<G.vexnum;m++)
						P[i][j][m] = P[i][k][m] || P[k][j][m];	//这一步也要简单解释下：这里最终的P[i][j][m]是P[i][k][m]P[k][j][m]的路径相加（就是只要后两个P中有的路径最后的P都应该拥有）
				}
				puts("");															//但是  虽然算法简单  在看这个算法的时候却始终觉得不安 因为觉得有可能在找(vi,vj)最短路径(vi,v[n],vj)的时候，会不会(vi,v[n])(v[n],vj)还没有找到最短路径
			}																	//解决这个问题也花了好久。 解释是： 就拿现在这个例子来讲（创建时候直接读取的文件，当作例子） 我要找(v1,v2)的最短路径 答案是(v1,v4,v3,v2)  我会担心直到最后一个循环中 将(v1,v4)与(v4,v2)相加时(v1,v4)或(v4，v2)是否已
																				//找到了最短路径  但是回顾整个循环  (v1,v4)不可能在之后才找到最短 因为这是整个大循环的最后一个循环 就算有对(v1,v4)的比较也是(v1,v4)+(v4,v4)当然是不可能改变(v1,v4)了    同理(v4,v2)也不可能找到再短了 看这之后是(v4,v4)+(v4,v2)还可能改变吗
																				//所以  运行到最后的时候都已经是最短的了
		puts("");
	}
}