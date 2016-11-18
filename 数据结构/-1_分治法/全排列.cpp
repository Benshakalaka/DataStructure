#include <stdio.h>					//这是教材上的递归例子 全排列
void swap(int &a,int &b)
{
	int temp = a;
	a = b;
	b =temp;
}

//可以通过对程序全排列的结果进行分析  可知  根据全排列的思想
void show(int *a,int k,int m)
{
	if(k==m)
	{
		for(int i=0;i<m;i++)
			printf("%d ",a[i]);
		puts("");
	}
	else
	{
		int j;
		for(j=k;j<m;j++)
		{
			swap(a[k],a[j]);
			show(a,k+1,m);
			swap(a[k],a[j]);
		}
	}
}

int main()
{
	int a[] = {1,2,3};
	show(a,0,3);
	return 0;
}

