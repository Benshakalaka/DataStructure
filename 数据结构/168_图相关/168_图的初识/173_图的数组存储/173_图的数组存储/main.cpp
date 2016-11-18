#include <stdio.h>							//这个数组存储图的程序并没有检测完全   创建有向图的函数是利用了txt读取文件进行的 文件名为hehe.txt 其他则是手动创建
#include "head.h"							//主要利用有向图来检测了整个程序的函数

int main()
{
	MGraph G;
	CreateGraph(G);
	Display(G);											//输出矩阵
	VexType i,j;	
	printf("Input the new vex and the old so as to modify some vex: ");
	scanf("%s%s",i,j);
	PutVex(G,i,j);
	printf("The result of DepthFS : \n");
	DFSTraverse(G,Visitfun);							//深搜
	printf("The result of BFS: \n");
	BFSTraverse(G,Visitfun);						//广搜
	printf("Input the head vex and tail in order to delete some arc: ");
	scanf("%s%s",i,j);
	DeleteArc(G,i,j);									//删弧
	Display(G);
	printf("Input the name of some vex to delete it : ");
	scanf("%s",i);
	DeleteVex(G,i);										//删顶点
	Display(G);
	return 0;
}