#include <stdio.h>
#include <stdlib.h>

int Max_part_normal(int *v,int c,int &m,int &n)
// 时间复杂度为O(n^2)
//v为数组，c为个数、m，n为：录从v[m]开始到v[n]结束
//本算法是基本算法，容易理解但是时间复杂度高
//思想：在数组V中 找出 最大子数组
//过程：将所有可能一一列举，继而比出最大。
{
	int i,j;
	int sum=0,temp=0;	
	for(i=0;i<c;i++)				//从第一个数开始，以下循环则是从这个数开始，参与个数不同从而结果不同进行比较
	{
		for(j=i;j<c;j++)
		{
			temp += v[j];
			if(sum < temp)
			{
				sum = temp;
				m = i;
				n = j;
			}
		}
		temp = 0;
	}
	return sum;
}




int Max_part_Divided(int *v,int start,int end)
// 时间复杂度为O(nlogn)
//本算法采用分治策略进行求解
//将v分为两段，a和b。最大子段有三种可能：
//	① 段a即为最大子段
//	② 段b即为最大子段
//	③ 在段a和段b之间 即 v[i]到v[j] (start<=i<=end/2,  end/2+1<=j<=end)
//过程：得到三组数据后，进行比较，取出最大
{
	if(start == end)										//若只有一个数且该数为负，正如题目所说，若全部为负，则最大为0
		return v[end]>0?v[end]:0;
	int center = (start+end)/2;
	int lsum = Max_part_Divided(v,start,center);			//情况①
	int rsum = Max_part_Divided(v,center+1,end);			//情况②
	int i;													//以下情况③
	int sum_s = 0,temp = 0;
	for(i=center;i>=0;i--)		//将左半部分的最大算出来，必须从center开始减，因为这一段是要和右边那段连起来的
	{
		temp += v[i];
		if(sum_s<temp)
			sum_s = temp;
	}
	int sum_e = 0;
	temp = 0;
	for(i=center+1;i<=end;i++)	//将右半部分的最大算出，必须从center开始加
	{
		temp += v[i];
		if(sum_e<temp)
			sum_e = temp;
	}
	int sum = sum_s+sum_e;		//两边相连
	if(sum<lsum)				//以下为三者进行比较
		sum = lsum;
	if(sum<rsum)
		sum = rsum;
	return sum;
}

int  Max_part_dynamic(int *v,int n)
//动态规划算法:
//b[j]=max{a[i]++a[j]},1<=i<=j,且1<=j<=n,则所求的最大子段和为max b[j]，1<=j<=n。
//由b[j]的定义可易知，当b[j-1]>0时b[j]=b[j-1]+a[j]，否则b[j]=a[j]。故b[j]的动态规划递归式为:
//b[j]=max(b[j-1]+a[j],a[j])，1<=j<=n。
//T(n)=O(n)
//依旧是最优子的思想

{
	int i;
	int b=0,sum=0;
	for(i=0;i<n;i++)
	{
		if(b>0)
			b += v[i];
		else
			b = v[i];
		if(sum < b)
			sum = b;
	}
	return sum;
}

int main()
{
	int result;
//	int m,n;
//	int a[] = {-2,11,-4,13,-5,-2};
//	result = Max_part(a,6,m,n);
//	printf("%d   [%d]--[%d]\n",result,m,n);
	
//	int a[] = {0,-2,11,-4,13,-5,-2};
//	result = Max_part_Divided(a,1,6);
//	printf("%d\n",result);	

	int a[] = {-2,11,-4,13,-5,-2};
	result = Max_part_dynamic(a,6);
	printf("%d\n",result);
	return 0;
}