#include <stdio.h>									//整个程序在于把整个创建出来 即CreateGList
#include "String.h"
#include "head.h"

int main()
{
	char p[80];
	String t;
	GList L,M;
	InitGList(L);																					//InitGList
	InitGList(M);
	printf("空广义表L的深度=%d L是否空？%d（1：是 0：否）\n",GListDepth(L),GListEmpty(L));
	printf("请输入广义表L（书写形式：空表（），原子：a，其他（a，（b））：\n");
	gets(p);
	StrAssign(t,p);
	CreateGList(L,t);																		//CreateGList
	printf("广义表L的长度 = %d\n",GListLength(L));
	printf("广义表L的深度 = %d  L是否为空： %d\n",GListDepth(L),GListEmpty(L));					//GListDepth
	printf("遍历广义表：\n");
	Traverse_GL(L);
	printf("\n复制广义表 M=L\n");
	CopyGList(M,L);																				//CopyGList
	printf("广义表M的长度 = %d\n",GListLength(M));
	printf("广义表M的深度 = %d\n",GListDepth(M));												//GListDepth
	printf("遍历广义表：\n");
	Traverse_GL(M);
	DestroyGList(M);																				//DestroyGList
	M = GetHead(L);																					//GetHead
	printf("\nM是L的表头，遍历M:\n");
	Traverse_GL(M);
	DestroyGList(M);
	M = GetTail(L);																					//GetTail
	printf("\nM是L的表尾，遍历M:\n");
	Traverse_GL(M);
	InsertFirst_GL(M,L);																				//InsertFirst_GL
	printf("\n插入L为M的表头，遍历M:\n");
	Traverse_GL(M);
	printf("\n删除M的表头，遍历M:\n");
	DestroyGList(L);																				//DestroyGList
	DeleteFirst_GL(M,L);																				//DeleteFirst_GL
	Traverse_GL(M);
	DestroyGList(M);																						//DestroyGList
	return 0;
}