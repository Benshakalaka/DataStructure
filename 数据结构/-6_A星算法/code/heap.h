#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
typedef int Keytype;							//关键字类型

#define N 100

typedef struct Unit
{
	Keytype key;									//关键字   即 G+H的值
	struct Unit *parent;							//双亲节点 为什么要这个双亲节点呢？因为计算G值需要
	bool obstacle;									//是否为障碍
	int G;											//G值是如何计算的呢？G是从开始点A到当前方块的移动量。所以从开始点A到相邻小方块的移动量为1，该值会随着离开始点越来越远而增大。
	int H;											//H值的计算上升空间大。 H是从当前方块到目标点的移动量估算值（具有不确定性，需要提供特定的算法，注意是估值）。这里使用了十分基础的曼哈顿长
	int x;											//坐标
	int y;
}Unit;									//元素类型

typedef struct									//用于操作的辅助空间
{
	Unit r[N];
	int length;
}SqList;

typedef SqList Heaptype;

void HeapAdjust(Heaptype &H,int s,int n)			//用于调整堆中的某个元素
{
	int i;
	H.r[0] = H.r[s];									
	for(i=2*s;i<=n;i*=2)								
	{
		if(i<n && H.r[i].key>H.r[i+1].key)				
			i++;
		if(H.r[0].key <= H.r[i].key)				
			break;
		H.r[s] = H.r[i];	
		s = i;					
	}
	H.r[s] = H.r[0];			
}

void HeapSort(Heaptype &H)							//对整个堆进行整理
{
	int i;
	for(i=H.length/2;i>=1;i--)						
		HeapAdjust(H,i,H.length);					
}


Unit ExtractMin(Heaptype &H)				//拿出最小关键字节点
{
	Unit temp = H.r[1];
	H.r[1] = H.r[H.length];
	H.length--;
	HeapAdjust(H,1,H.length);
	return temp;
}

void Swap(Unit &A,Unit &B)
{
	Unit temp = A;
	A = B;
	B = temp;
}
void InsertHeap(Heaptype &H,Unit e)			//插入一个节点
{
	H.length++;
	H.r[H.length] = e;
	if(e.key == H.r[1].key)						//这里在加入节点的地方有个细微的操作：将最近刚加入的点（如果该点的key值与原堆中最小节点的key值相同）选择作为堆的最小节点。
		Swap(H.r[1],H.r[H.length]);
	HeapSort(H);
}

bool Checkifinheap(Heaptype H,Location temp)
{
	if(!H.length)
		return false;
	for(int i=1;i<=H.length;i++)
		if(H.r[i].x==temp.x && H.r[i].y==temp.y)
			return true;
	return false;
}

void init(Heaptype &H)
{
	H.length = 0;
}
#endif