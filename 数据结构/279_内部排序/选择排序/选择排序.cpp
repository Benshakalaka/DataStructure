//0号元素其他用途
#include <stdio.h>
//--------------------------------------------------------简单的选择排序----------------------------------------------------------------
int ChooseMin(int *a,int len,int i)	//在数组a中从[i,len]挑出最小的一个
{
	int k = i;
	for(int j = i;j<=len;j++)
		if(a[k] > a[j])
			k = j;
	return k;
}
void Swap(int &a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void SelectSort(int *a,int len)
{
	int i,temp;
	for(i=1;i<len;i++)
	{
		temp = ChooseMin(a,len,i);			//挑出i之后的最小的之后
		if(i!=temp)							//或本来就是i 或与i处的数交换位置
			Swap(a[i],a[temp]);
	}
}
//-------------------------------------------------------------------------------------------------------------------------


int main()
{
	int a[9] = {0,6,3,5,1,2,7,8,4};
	SelectSort(a,8);
	int i;
	for(i=1;i<=8;i++)
		printf("%d ",a[i]);
	puts("");
	return 0;
}