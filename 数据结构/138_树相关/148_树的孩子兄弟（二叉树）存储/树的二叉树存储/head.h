#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>

typedef int Type;
typedef struct CSNode
{
	Type data;
	struct CSNode *firstchild,*nextsibling;
}CSNode, * CSTree;

void Print(CSTree);
void InitTree(CSTree &);										//构造空树
void DestroyTree(CSTree &);									//销毁树
void CreateTree(CSTree &);										//构造树
bool TreeEmpty(CSTree );											//判断树是否为空		
int TreeDepth(CSTree );										//树的深度
Type Value(CSTree );									//返回p所指的点的值
Type Root(CSTree );											//返回T的根
CSTree Point(CSTree ,Type);										//	返回树中值为s的节点的指针	
bool Assign(CSTree &,Type, Type);										//将元素cue改为value
Type Parent(CSTree T,Type cue);										//若非根，则返回双亲	
Type LeftChild(CSTree T,Type cue);									//若为非叶子节点 则返回左孩子  否则空
Type RightSibling(CSTree T,Type cue);									//若有右兄弟 则返回右兄弟 否则为空
void InsertChild(CSTree &T,Type p,int i,CSTree c);									//插入c为T中p节点的第i棵子树
void DeleteChild(CSTree &T,int i,Type p);									//删除T中p节点的第i棵子树
void PreOrderTraverse(CSTree , void (*Visit)(CSTree));								//先序
void PostOrderTraverse(CSTree , void (*Visit)(CSTree));							//后序	
void LevelOrderTraverse(CSTree , void (*Visit)(CSTree));							//层序
void PostOrderTraverse2(CSTree ,void (*Visit)(CSTree));

#endif