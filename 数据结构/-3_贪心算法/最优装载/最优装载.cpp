#include <stdio.h>

//题目很简单 根据txt中题目要求。只要保证重量不超过，物品尽量多。 所以将重量排序，一个个都放上知道超出质量
void Sort(int *&t,int *w,int n)
{
	//可使用快速排序，将物品质量从小到大排序
}
void Loading(int *&x,int *w,int c,int n)
{
	int *t = (int *)malloc(sizeof(int)*(n+1));
	Sort(t,w,n);					//		算法主要时间复杂度集中在排序上
	int i,temp=0;
	for(i=1;i<=n;i++)
		x[i] = 0;
	for(i=1;i<=n && w[t[i]]<=c;i++)
	{
		x[t[i]] = 1;
		c -= w[t[i]];
	}
}

int main()
{
	return 0;
}