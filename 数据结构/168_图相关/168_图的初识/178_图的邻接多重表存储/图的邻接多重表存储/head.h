//******************************************************************无向图的邻接多重表*****
//这种存储方式有优点 当然也有缺点  从一个顶点向后寻找的时候 不能确定弧节点中的i和j哪个才是和顶点一样的部分
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX_NUM 20
typedef enum{unvisited,visited} VisitIf;
typedef char InfoType;
typedef char VexType[10];

typedef struct EBox
{
	VisitIf mark;			//访问标记
	int ivex,jvex;				//该边的两个顶点
	struct EBox *ilink,*jlink;	//分别指向依附这两个顶点的下一条边
	InfoType *info;				//边的信息
}EBox;
typedef struct VexBox
{
	VexType data;
	EBox *firstedge;		//第一条依附该顶点的边
}VexBox;
typedef struct
{
	VexBox adjmulist[MAX_VEX_NUM];
	int vexnum,arcnum;		//无向图的顶点数和边数
}AMLGraph;

int LocateVex(AMLGraph G,VexType v);									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息

void CreateGraph(AMLGraph &G);							//构造无向图

void DestroyGraph(AMLGraph &G);							

VexType &GetVex(AMLGraph G,int v);								//返回v的值

void PutVex(AMLGraph &G,VexType v,VexType value);							//对v赋值value

int FirstAdjVex(AMLGraph G,VexType v);						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空

int NextAdjVex(AMLGraph G,VexType v,VexType w);						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
			
void InsertVex(AMLGraph &G,VexType v);						//	在图G中新增顶点v			

void DeleteVex(AMLGraph &G,VexType v);							//删除G中顶点v及其相关弧						

void InsertArc(AMLGraph &G,VexType v,VexType w);							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>

void DeleteArc(AMLGraph &G,VexType v,VexType w);							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	

void MarkInitial(AMLGraph G);

void Visitfun(VexType v);

void DFS(AMLGraph G,int v);									//从第v个顶点出发递归遍历树	
	
void DFSTraverse(AMLGraph G,void (*Visitfun)(VexType));							//	进行深度优先搜索			

void BFSTraverse(AMLGraph G,void (*Visitfun)(VexType));							//	进行广度优先搜索

void Display(AMLGraph G);								//  输出邻接矩阵
