//******************************************************************有向图的十字链表*****
#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


#define MAX_VEX_NUM 20									//最大顶点数
typedef char Infotype;									//关于弧的信息指针
typedef char VexType[10];								//顶点名字类型

typedef struct ArcBox								//存储弧的类型
{
	int tailvex,headvex;					//分别存储该弧的头和尾
	struct ArcBox *hlink,*tlink;			//分别指向弧头相同 和 弧尾相同的链域
	Infotype *info;							//弧信息
}ArcBox;
typedef struct VexNode				//头结点存储顶点
{
	VexType data;							//顶点名字
	ArcBox *firstin,*firstout;				//分别存储指向该顶点的第一条出弧和入弧
}VexNode;
typedef struct
{
	VexNode xlist[MAX_VEX_NUM];		//用数组存顶点		
	int vexnum,arcnum;
}OLGraph;


int LocateVex(OLGraph G,VexType u);									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息

void CreateGraph(OLGraph &G);							//一个函数构造四种图

void DestroyGraph(OLGraph &G);							//信息部分这里并没有所以就没有指针的free

VexType &GetVex(OLGraph G,int v);								//返回v的值

void PutVex(OLGraph &G,VexType v,VexType value);							//对v赋值value

int FirstAdjVex(OLGraph G,VexType v);						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空

int NextAdjVex(OLGraph G,VexType v,VexType w);						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
			
void InsertVex(OLGraph &G,VexType v);						//	在图G中新增顶点v			

void DeleteVex(OLGraph &G,VexType v);							//删除G中顶点v及其相关弧						

void InsertArc(OLGraph &G,VexType v,VexType w);							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>

void DeleteArc(OLGraph &G,VexType v,VexType w);							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	

void Visitfun(VexType v);

void DFS(OLGraph G,int v);									//从第v个顶点出发递归遍历树	
	
void DFSTraverse(OLGraph G ,void (*Visitfun)(VexType));							//	进行深度优先搜索			

void BFSTraverse(OLGraph G ,void (*Visitfun)(VexType));							//	进行广度优先搜索

void Display(OLGraph G);								//  输出邻接矩阵
#endif