#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>				//另一个是顺序存储  即数组存储  这里利用链表来存储  相对而言较为简单
#include <malloc.h>

typedef int Type;

typedef struct BiTNode												//数据类型
{
	Type x;									//所存数据
	struct BiTNode *LN;						//左子
	struct BiTNode *RN;						//右子
}BiTNode,*BiTree;

void Print(BiTree);															//输出函数
void CreateBiTree(BiTree &);												//创建函数
void PreOrderTraverse(BiTree ,void (*Visit)(BiTree));							//先序遍历
void InOrderTraverse(BiTree ,void (*Visit)(BiTree));							//中序遍历
void InOrderTraverse_2(BiTree ,void (*Visit)(BiTree));					//中2
void InOrderTraverse_3(BiTree ,void (*Visit)(BiTree));					//中3
void PostOrderTraverse(BiTree ,void (*Visit)(BiTree));						//后序遍历
void LevelOrderTraverse(BiTree ,void (*Visit)(BiTree));						//层序遍历
void InitBiTree(BiTree &);													//初始化
void DestroyBiTree(BiTree &);
Type Parent(BiTree,Type);											//寻找父母节点
#endif