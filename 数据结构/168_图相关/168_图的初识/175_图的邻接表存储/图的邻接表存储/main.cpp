#include <stdio.h>
#include "head.h"

int main()
{
	int i,j,k,n;
	ALGraph G;
	VexType v1,v2;
	/*printf("Please create a DG\n");								//单独对拿向图进行测试大部分函数	检测一
	CreateGraph(G);
	Display(G);
	printf("Delete one arc(edge). Input the tail and head\n");
	scanf("%s%s",v1,v2);
	DeleteArc(G,v1,v2);
	printf("Modify the name of some vex\n");
	scanf("%s%s",v1,v2);
	PutVex(G,v1,v2);
	printf("Insert a new vex\n");
	scanf("%s",v1);
	InsertVex(G,v1);
	printf("Insert some arcs(edges) related to the new vex\n");
	printf("How many?\n");
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
	printf("Delete some vex: ");
	scanf("%s",v1);
	DeleteVex(G,v1);
	Display(G);
	printf("The result of DepthFS: \n");
	DFSTraverse(G,Visitfun);
	printf("The result of BFS: \n");
	BFSTraverse(G,Visitfun);
	DestroyGraph(G);*/






	/*printf("Try the DG、DN、UDG、UDN one after another.\n");						//将所有图种进行测试	检测二
	for(i=0;i<3;i++)
	{
		CreateGraph(G);
		Display(G);
		printf("Insert a new vex and what's the name : ");
		scanf("%s",v1);
		InsertVex(G,v1);
		printf("Insert some arcs(edges) related to the new vex\n");
		printf("How many?\n");
		scanf("%d",&n);
		for(k=0;k<n;k++)
		{
			printf("The other vex's name : ");
			scanf("%s",v2);
			if(G.kind<=1)												//插入弧（边）的时候看是否为有向图（网）
			{
				printf("Choose a direction for the vex(0:head 1:tail)\n");
				scanf("%d",&j);
				if(j)						//有向的话 还需要确定头和尾
					InsertArc(G,v2,v1);
				else
					InsertArc(G,v1,v2);
			}
			else														//无向则直接插
				InsertArc(G,v1,v2);
		}	
		Display(G);
		printf("Delete some vex: ");
		scanf("%s",v1);
		DeleteVex(G,v1);
		Display(G);
		DestroyGraph(G);
	}*/





	CreateGraph(G);													//检测3.1  出现了问题
	Display(G);
	/*for(i=FirstAdjVex(G,"m");i>=0;i=NextAdjVex(G,"m",GetVex(G,i)))
		printf("%d %s \n",i,GetVex(G,i));
	puts("");
	ArcPoint p = G.vertices[12].firstarc;
	while(p)
	{
		printf("%d  ",p->adjvex);
		p = p->nextarc;
	}
	puts("");*/


	/*for(i=FirstAdjVex(G,"m");i>=0;i=NextAdjVex(G,"m",v1))			//检测3.2  通过检测四选择跳过问题
	{
		strcpy(v1,GetVex(G,i));
		printf("%s  ",v1);	
	}
	puts("");
	ArcPoint p = G.vertices[12].firstarc;
	while(p)
	{
		printf("%d  ",p->adjvex);
		p = p->nextarc;
	}
	puts("");*/





	//CreateGraph(G);														//检测4.1
	//Display(G);
	/*printf("%s\n",GetVex(G,11));
	printf("%d\n",strcmp(GetVex(G,11),"l"));
	printf("%d\n",NextAdjVex(G,"m",GetVex(G,11)));
	printf("%d\n",NextAdjVex(G,"m","l"));*/



	/*printf("%s\n",GetVex(G,11));											//检测4.2		没解决问题 但跳过问题。。。
	strcpy(v1,GetVex(G,11));
	printf("%d\n",strcmp(GetVex(G,11),"l"));
	printf("%d\n",NextAdjVex(G,"m",v1));
	printf("%d\n",NextAdjVex(G,"m","l"));*/
	return 0;
}