#include <stdio.h>											//具体结构看图（四种结构一起的图）
#include "head.h"

int main()
{
	int k,n;
	VexType v1,v2;
	AMLGraph G;
	CreateGraph(G);
	Display(G);
	/*printf("Modify . the old and the new : ");
	scanf("%s%s",v1,v2);
	PutVex(G,v1,v2);
	Display(G);
	printf("Insert a new vex : ");
	scanf("%s",v1);
	InsertVex(G,v1);										//添加新顶点
	Display(G);
	printf("Insert some arcs(edges) related to the new vex\n");
	printf("How many?\n");											//新顶点的边
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("The other vex's name : ");
		scanf("%s",v2);
		InsertArc(G,v1,v2);
	}
	Display(G);
	printf("The result of DepthFS: \n");
	DFSTraverse(G,Visitfun);								//深搜
	printf("The result of BFS: \n");
	BFSTraverse(G,Visitfun);					//广搜*/
	/*printf("Delete some arc : ");
	scanf("%s%s",v1,v2);
	DeleteArc(G,v1,v2);
	Display(G);*/
	printf("Delete certain vex : ");
	scanf("%s",v1);
	DeleteVex(G,v1);
	Display(G);
	//DestroyGraph(G);
	return 0;
}