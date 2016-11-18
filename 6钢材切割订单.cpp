#include <stdio.h>
#include <malloc.h>
void sort(int *,int);
void fun(int *a,int len,int sum,int total,int n,int i);//(a,8,0,28,1,0)
int main()
{
	int total_len,o_num;
	printf("输入长度 、 订单数 、 各订单长度\n");
	printf("总长度 : ____\b\b\b\b");
	scanf("%d",&total_len);
	printf("订单数 : ____\b\b\b\b");
	scanf("%d",&o_num);
	int *order = (int *)malloc(sizeof(int) * o_num);
	printf("各长度 ： \n");
	int i;
	for(i=0;i < o_num;i++)
		scanf("%d",order+i);
//	sort(order,o_num);
//	printf("n a[i] a[j] sum\n");
	fun(order,o_num,0,total_len,1,0);
	free(order);
	return 0;
}
void sort(int *s,int len)
{
	int i,j,temp;
	for(i=0;i<len;i++)
		for(j=i;j<len;j++)
			if(s[i] > s[j])
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
}
void fun(int *a,int len,int sum,int total,int n,int i)//(a,8,0,28,1,0)  暂时搁置  为什么只有两个答案是最佳 其他为什么不可以呢  题目都没懂！！
{
	for(int j=i;j<len;j++)
	{
		int c_sum=sum;
		sum += a[j];
		if(sum == (total-(n-1)*2))
			printf("%d   %d  %d     %d\n",n,a[i-1],a[j],sum );
		else
		fun(a,len,sum,total,n+1,j+1);
		sum=c_sum;
	}
}