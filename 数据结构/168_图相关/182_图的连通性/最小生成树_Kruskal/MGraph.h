#ifndef MGRAPH_H
#define MGRAPH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 0			//最大值（用于带权的图或者网）
#define MAX_VERTEX_NUM 20			//最大顶点个数
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef char VexType[10];			// 顶点的字符串长度

typedef struct
{
	int adj;						//对无权图 用1或0 表示是否相邻 ； 对有权图 则为权值
	//InfoType *info;				//与该弧相关信息的指针  （此程序并未用到）
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	VexType vexs[MAX_VERTEX_NUM];						//顶点向量
	AdjMatrix arcs;					//整个邻接矩阵
	int vexnum,arcnum;				//整个图的顶点和边数
	GraphKind kind;					//图存的种类 是有向无向图 还是有向无向网
}MGraph;



bool CreateGraph(MGraph &);								//按照V和VR的定义构造图G 

bool CreateGraph_DG(MGraph &);							// 有向图
bool CreateGraph_DN(MGraph &);							//有向网
bool CreateGraph_UDG(MGraph &);							//无向图
void CreateGraph_UDN(MGraph &);								//无向网


int LocateVex(MGraph G,VexType u);							//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息

void DestroyGraph(MGraph &G);							//信息部分这里并没有所以就没有指针的free
			
VexType &GetVex(MGraph G,int v);								//返回v的值

void PutVex(MGraph &G,VexType v,VexType value);							//对v赋值value

int FirstAdjVex(MGraph G,VexType v);						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空

int NextAdjVex(MGraph G,VexType v,VexType w);						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
			
void InsertVex(MGraph &G,VexType v);						//	在图G中新增顶点v			

void DeleteVex(MGraph &G,VexType v);							//删除G中顶点v及其相关弧						

void InsertArc(MGraph &G,VexType v,VexType w);							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>

void DeleteArc(MGraph &G,VexType v,VexType w);							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>

void Visitfun(VexType v);

void DFS(MGraph G,int v);									//从第v个顶点出发递归遍历树	
	
void DFSTraverse(MGraph G,void (*Visitfun)(VexType));							//	进行深度优先搜索			

void BFSTraverse(MGraph G,void (*Visitfun)(VexType));							//	进行广度优先搜索

void Display(MGraph G);								//  输出邻接矩阵

#endif