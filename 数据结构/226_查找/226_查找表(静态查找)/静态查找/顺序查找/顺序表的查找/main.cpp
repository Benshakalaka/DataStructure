#include <stdio.h>				//本程序主要实现顺序表的查找 但夹杂有序表的查找(有序函数包含 Ascend、Create_Ord、Search_Bin 但是不在主函数中用出来 具体实现较为简单)
#include "head.h"


//------------------------------------------------------------------------
Elemtype r[N]={{179328,"何芳芳",85,89,98,100,93,80,47},
	{179325,"陈红",85,86,88,100,92,90,45},
	{179326,"陆华",78,75,90,80,95,88,37},
	{179327,"张平",82,80,78,98,84,96,40},
	{179324,"赵小怡",76,85,94,57,77,69,44}}; // 数组不按关键字有序
//------------------------------------------------------------------------



//----------------------------以下为主程序
void print(Elemtype c) // Traverse()调用的函数
{
   printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,
	   c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
}

 void main()
 {
   SSTable st;
   int i;
   long s;
   for(i=0;i<N;i++) // 计算总分
     r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+
	 r[i].chemistry+r[i].biology;
   Create_Seq(st,N,r); // 由数组r产生顺序静态查找表st
   printf("准考证号  姓名  政治 语文 外语 数学 物理 化学 生物 总分\n");
   Traverse(st,print); // 按顺序输出静态查找表st
   printf("请输入待查找人的考号: ");
   scanf("%ld",&s);
   i=Search_Seq(st,s); // 顺序查找
   if(i)
     print(st.elem[i]);
   else
     printf("没找到\n");
   Destroy(st);
 }
//---------------------------------


