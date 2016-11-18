#include<stdio.h>

//数据存储在a[1...n-1]
//法① ：暴力破解
/*void Leftmove(int *a,int n)
{
	a[0] = a[1];
	for(int i=1;i<n-1;i++)
		a[i] = a[i+1];
	a[n-1] = a[0];
}*/

//法② ：三步反转法
void Reverse(int *a,int start,int end)			//将一段反转
{
	while(start<end)
	{
		int temp = a[start];
		a[start++] = a[end];
		a[end--] = temp;
	}
}
//将整段分为X+Y			看图理解
void Leftmove(int *a,int n,int count)
{
	Reverse(a,1,count);						//将X段反转
	Reverse(a,count+1,n);					//将Y段发转
	Reverse(a,1,n);							//整个反转
}




int main()
{
	int a[8] = {0,1,2,3,4,5,6,7};
	Leftmove(a,7,3);
	for(int i=1;i<8;i++)
		printf("%d ",a[i]);
	return 0;
}