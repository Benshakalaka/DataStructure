#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>









 #define N 5 // 数据元素个数
 typedef int Keytype; // 设关键字域为长整型
 #define key number // ***************定义关键字为准考证号				只要改变这个就能改变寻找的目标（关键词 比如可以是学号、数学、语文等）

 //------------------------------------------------------------------------以下为数据类型 可改变
struct Elemtype // 数据元素类型(以教科书图9.1高考成绩为例)
 {
   long number;					// 准考证号，与关键字类型同
   char name[9];				 // 姓名(4个汉字加1个串结束标志)
   int politics;				// 政治
   int Chinese;					// 语文
   int English;					// 英语
   int math;					// 数学
   int physics;					// 物理
   int chemistry;				// 化学
   int biology;					// 生物
   int total;					// 总分
 };












typedef struct								//类型
{
	Elemtype *elem;								//数据顺序存储基址	0号元素留空（为什么？在函数Search_Seq中有解释）
	int length;
}SSTable;

//对数值型关键字
#define EQ(a,b) ((a)==(b))			//equal
#define LT(a,b) ((a)<(b))			//less than
#define LQ(a,b)	 ((a)<=(b))			//less than + equal

void Create_Seq(SSTable &,int,Elemtype*);							//构建一个含n个数据元素的静态顺序查找表
void Ascend(SSTable &);								//重建查找表为按关键字的非降序排序
void Create_Ord(SSTable &,int);							//构建一个含n个数据元素的静态非降序排序顺序查找表
void Destroy(SSTable &);								//销毁
int Search_Seq(SSTable &,Keytype );						//算法9.1	在顺序表中查找其关键字等于等于key的数据元素，若找到 则函数值为表中位置 否则为0
int Search_Bin(SSTable &,Keytype );						//算法9.2	在顺序表中查找其关键字等于等于key的数据元素，若找到 则函数值为表中位置 否则为0
void Traverse(SSTable,void (*visit)(Elemtype));			//遍历





