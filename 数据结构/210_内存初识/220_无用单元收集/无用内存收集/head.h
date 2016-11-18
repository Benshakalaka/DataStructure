#include <stdio.h>								//GetHead那部分  其实没有搞懂为什么这么烦  跟GetTail一样不久可以了吗？？？？
#include <malloc.h>
#include <stdlib.h>
#include "String.h"
enum ElemTag{ATOM,LIST};						//用枚举来定义一种类型  只有0,1这两种选择  主要是为了程序可读性的提高

typedef struct Node								//一个节点（光看外面并不知道是个原子还是子表）
{
	int mark;
	ElemTag tag;								//等于 ATOM 表示原子  LIST 表示子表
	union										//为什么用这个union呢    因为既然这节点是不知道是什么的  所以为了不浪费空间 就公用一块内存 要么是一个值要么就是存下一个子表
	{
		int elem;								//这个有值代表原子
		struct									//这个有值代表子表（这里为什么用结构体呢  是为了把两部分区别开来，分成两个整体  一个是表示原子 一个表示子表）
		{
			struct Node *hp;					//存下一个子表的表头  
			struct Node *tp;					//下一个子表的表尾（一个子表不是表头就是表尾） 不懂的话120页有例子
		};
	};
}*GList,Node;

void InitGList(GList &);								//创建空的广义表
void DestroyGList(GList &);							//销毁
void CopyGList(GList &T,GList L);								//复制
int GListLength(GList &L);								//求的广义表长度，即元素个数
int GListDepth(GList &L);								//求广义表深度
bool GListEmpty(GList &L);								//判断广义表是否为空
GList GetHead(GList &L);								//取广义表的表头
GList GetTail(GList &L);			
void InsertFirst_GL(GList &L,GList e);							//插入元素作为广义表的第一个元素
void DeleteFirst_GL(GList &L,GList &e);							//删除
void Traverse_GL(GList &L,void (*visit)(GList));								//遍历
void sever(GList &str,GList &hstr);									//将str分割成两个部分 hstr为第一个‘，’之前的子串，str为之后的子串
void CreateGList(GList &L,String S);								//创建一个广义表								