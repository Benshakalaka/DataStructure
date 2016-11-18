#include <stdio.h>
#include <malloc.h>

//因为这个k的值是最大值，所以在创建辅助数组的时候有时候会造成极大的空间浪费	也是一个缺陷吧

void CountingSort(int *a,int *b,int k,int len)			//k为整个数组最大的关键字
{
	int *c = (int *)malloc(sizeof(int)*k);
	int i;
	for(i=0;i<=k;i++)				//初始化	
		c[i] = 0;
	for(i=1;i<=len;i++)				//c[i]是辅助用  这里是将每个关键字个数按顺序数出来
		c[a[i]]++;
	for(i=1;i<=k;i++)				//然后相加 就知道了某个数应该在数组中的位置
		c[i] = c[i]+c[i-1];
	for(i=len;i>=1;i--)				//在最终数组b中确定位置
	{
		b[c[a[i]]] = a[i];
		c[a[i]]--;					//这一步是因为可能存在相同元素，所以不能占用相同位置 
	}
}

int main()
{
	int a[9] = {0,2,5,3,0,2,3,0,3};
	int k = 5;
	int b[9];
	CountingSort(a,b,k,8);
	for(int i=1;i<=8;i++)
		printf("%d ",b[i]);
	puts("");
	return 0;
}