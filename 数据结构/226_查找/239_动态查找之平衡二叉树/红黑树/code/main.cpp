#include <stdio.h>
#include <iostream>
#include "head.h"

int main()
{
	RBTree T = 0;
	/*RBTree temp = RBSearch(T,5);
	if(!temp)
		printf("Not found\n");
	else
		printf("%d\n",temp->key);*/
//插入测试					根据文件夹中图片
	RB_INSERT(T,12);
	RB_INSERT(T,1);
	RB_INSERT(T,9);
	RB_INSERT(T,2);
	RB_INSERT(T,0);
	RB_INSERT(T,11);
	RB_INSERT(T,7);
	RB_INSERT(T,19);
	RB_INSERT(T,4);
	RB_INSERT(T,15);
	RB_INSERT(T,18);
	RB_INSERT(T,5);
	RB_INSERT(T,14);
	RB_INSERT(T,13);
	RB_INSERT(T,10);
	RB_INSERT(T,16);
	RB_INSERT(T,6);
	RB_INSERT(T,3);
	RB_INSERT(T,8);
	RB_INSERT(T,17);

//删除节点测试				根据文件夹中的图片
	RB_DELETE(T,12);
	RB_DELETE(T,1);
	RB_DELETE(T,9);
	RB_DELETE(T,2);
	RB_DELETE(T,0);
	RB_DELETE(T,11);
	RB_DELETE(T,7);
	RB_DELETE(T,19);
	RB_DELETE(T,4);
	RB_DELETE(T,15);
	RB_DELETE(T,18);
	RB_DELETE(T,5);
	RB_DELETE(T,14);
	RB_DELETE(T,13);
	RB_DELETE(T,10);
	RB_DELETE(T,16);
	RB_DELETE(T,6);
	RB_DELETE(T,3);
	RB_DELETE(T,8);
	RB_DELETE(T,17);
	RBTraverse(T);
	system("pause");
	return 0;
}