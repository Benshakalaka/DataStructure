#include <stdio.h>
//#include <malloc.h>
#include <string.h>
#include <stdlib.h>


#define MAX_VEX_NUM 20										//限制最大顶点数
#define INFINITY 1000			//最大值（用于带权的图或者网）
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef char VexType[10];			// 顶点的字符串长度
typedef int InfoType;

//typedef char InfoType;

struct Edge
{
	int m,n;
	int w;
};

typedef struct ArcNode						//这个是头结点之后节点的类型
{
	int adjvex;					//当前节点位置
	struct ArcNode *nextarc;	//指向下一个邻接节点
	InfoType *info;										//这里的信息用来装载网的权
}ArcNode, *ArcPoint;
typedef struct									//这个是头结点
{
	VexType data;				
	ArcPoint firstarc;			//指向第一个邻接节点
}VNode, AdjList[MAX_VEX_NUM];					//要是我自己来写的话 不一定会直接typedef一个数组类型 而是会typedef指针类型 之后去分配内存  但是整个程序是可添加删除顶点的 所以不稳定 一下子规定好规模也是不错选择
typedef struct									//这个类型是将整个图信息包含起来
{
	AdjList vertices;
	int vexnum,arcnum;			//整个图的顶点数 弧数
	int kind;					//种类
}ALGraph;


int LocateVex(ALGraph G,VexType u);									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息

Edge* CreateGraph(ALGraph &G);							//一个函数构造四种图

void DestroyGraph(ALGraph &G);							//信息部分这里并没有所以就没有指针的free

VexType &GetVex(ALGraph G,int v);								//返回v的值

void PutVex(ALGraph &G,VexType v,VexType value);							//对v赋值value

int FirstAdjVex(ALGraph G,VexType v);						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空

int NextAdjVex(ALGraph G,VexType v,VexType w);						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
			
void InsertVex(ALGraph &G,VexType v);						//	在图G中新增顶点v			

void DeleteVex(ALGraph &G,VexType v);							//删除G中顶点v及其相关弧						

//void InsertArc(ALGraph &G,VexType v,VexType w);							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
void InsertArc(ALGraph &G,int ,int, int,Edge*&);

void DeleteArc(ALGraph &G,VexType v,VexType w);							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	

void Visitfun(VexType);
void DFS(ALGraph G,int v);									//从第v个顶点出发递归遍历树	
	
void DFSTraverse(ALGraph G,void (*Visitfun)(VexType));							//	进行深度优先搜索			

void BFSTraverse(ALGraph G,void (*Visitfun)(VexType));							//	进行广度优先搜索

void Display(ALGraph G);								//  输出邻接矩阵
