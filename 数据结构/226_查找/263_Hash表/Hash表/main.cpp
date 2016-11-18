// 整个哈希表是有问题在里面的  问题在c这个点上		不过不知道怎么解决  几乎所有跟c有关的都存在问题 比如head.cpp的88行 的判断  又比如
#include <stdio.h>
#include "head.h"
#define N 10
void Visit(Elemtype elem)
{
	printf("%d ",elem.key);
}
int main()
{
	Elemtype r[N]={{17},{60},{29},{38},{1},{2},{3},{4},{60},{13}};
	HashTable h;
   int i,p;
   int j;
   Keytype k;
   InitHashTable(h);
   for(i=0;i<N-1;i++)
   { // 插入前N-1个记录
     j=InsertHash(h,r[i]);
     if(j==DUPLICATE)
       printf("表中已有关键字为%d的记录，无法再插入记录(%d)\n",r[i].key,r[i].key);
   }
   printf("按哈希地址的顺序遍历哈希表:\n");
   TraverseHash(h,Visit);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     Visit(h.elem[p]);
   else
     printf("没找到\n");
   j=InsertHash(h,r[i]); // 插入第N个记录
   printf("按哈希地址的顺序遍历重建后的哈希表:\n");
   TraverseHash(h,Visit);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     Visit(h.elem[p]);
   else
     printf("没找到\n");
   DestroyHashTable(h);\
	return 0;
}