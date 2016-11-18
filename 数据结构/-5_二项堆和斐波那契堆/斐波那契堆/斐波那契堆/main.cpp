#include <stdio.h>
#include <malloc.h>
#include "head.h"

int main()
{
	FibonacciHeap heapb = 0;
	Make_Fib_Heap(heapb);
	int a[] = {12,7,25,15,28,33,41,1};
	int b[] = {18,35,20,42,9,31,23,6,48,11,24,52,13,2};
	printf("== 斐波那契堆(hb)中依次添加: ");
	for(int i=0;i<14;i++)
	{
		printf("%d ",b[i]);
		Fibopnode node = (Fibopnode)malloc(sizeof(FiboNode));
		node->key = b[i];
		Fib_Heap_Insert(heapb,node);
	}
	printf("\n");
	printf("== 输出堆\n");
	Print(heapb);
	printf("== 斐波那契堆(hb)删除最小节点\n");
	Fib_Heap_Extract_Min(heapb);
	Print(heapb);

	FibonacciHeap heapa = 0;
	/*Make_Fib_Heap(heapa);
	printf("== 斐波那契堆(ha)中依次添加: ");
	for(i=0;i<8;i++)
	{
		printf("%d ",a[i]);
		Fibopnode node = (Fibopnode)malloc(sizeof(FiboNode));
		node->key = a[i];
		Fib_Heap_Insert(heapa,node);
	}
	printf("== 输出堆\n");
	Print(heapa);
	printf("== 斐波那契堆(ha)删除最小节点\n");
	Fib_Heap_Extract_Min(heapa);
	Print(heapa);
	heapa = Fib_Heap_Union(heapa,heapb);
	Print(heapa);*/
	Fibonacci_Heap_Delete(heapb,heapb->min->left->child->right);
	Print(heapb);
	return 0;
}