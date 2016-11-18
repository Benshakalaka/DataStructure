#ifndef HEAP_H
#define HEAP_H

typedef int Keytype;							//关键字类型

#define N 100

typedef struct
{
	Keytype key;
}Elemtype;									//元素类型

typedef struct									//用于操作的辅助空间
{
	Elemtype r[N];
	int length;
}SqList;

typedef SqList Heaptype;

void HeapAdjust(Heaptype &H,int s,int n)
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

void HeapSort(Heaptype &H)				
{
	int i;
	for(i=H.length/2;i>=1;i--)						
		HeapAdjust(H,i,H.length);					
}


Elemtype ExtractMin(Heaptype &H)
{
	Elemtype temp = H.r[1];
	H.r[1] = H.r[H.length];
	H.length--;
	HeapAdjust(H,1,H.length);
	return temp;
}

void InsertHeap(Heaptype &H,Elemtype e)
{
	H.length++;
	H.r[H.length] = e;
	HeapSort(H);
}


#endif HEAP_H