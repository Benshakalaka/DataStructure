#include <stdio.h>
#include "head.h"

int main()
{
	int j,k,n;
	VexType v1,v2;
	OLGraph G;													//这是用来存储有向图的 所以测试不必多
	CreateGraph(G);
	Display(G);
	printf("Modify . the old and the new : ");
	scanf("%s%s",v1,v2);
	PutVex(G,v1,v2);										//改顶点名字
	printf("Insert a new vex : ");
	scanf("%s",v1);
	InsertVex(G,v1);										//添加新顶点
	printf("Insert some arcs(edges) related to the new vex\n");
	printf("How many?\n");											//新顶点的边
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("The other vex's name : ");
		scanf("%s",v2);
		printf("Choose a direction for the vex(0:head 1:tail)\n");
		scanf("%d",&j);
		if(j)
			InsertArc(G,v2,v1);
		else
			InsertArc(G,v1,v2);
	}
	Display(G);
	printf("Delete one arc . Input the two vex of it:\n");
	scanf("%s%s",v1,v2);
	DeleteArc(G,v1,v2);										//删边
	Display(G);
	printf("Delete some vex: ");
	scanf("%s",v1);
	DeleteVex(G,v1);								//删顶点
	Display(G);
	printf("The result of DepthFS: \n");
	DFSTraverse(G,Visitfun);									//深搜
	printf("The result of BFS: \n");
	BFSTraverse(G,Visitfun);									//广搜
	DestroyGraph(G);
	return 0;
}