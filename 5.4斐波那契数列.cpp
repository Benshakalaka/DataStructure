#include <stdio.h>               //斐波那契数列
//循环实现-----------------------------------------------------------------
/*int fun(int x);
int main()
{
	int x;
	scanf("%d",&x);
	printf("%d\n",fun(x));
	return 0;
}

int fun(int x)
{
	int a=1,b=1,c;
	if(x==1)
		return 1;
	else if(x==2)
		return 1;
	else if(x>=3)
	{
		for(int i=3;i<=x;i++)
		{
			c=a+b;
			a=b;
			b=c;
		}
		return c;
	}
	else
		return 0;
}*/
//递归实现-----------------------------------------------------------------
#include <stdlib.h>
int fun(int i)
{
	if(i==1)
		return 1;
	else if(i==2)
		return 1;
	else if(i>2)
		return fun(i-1)+fun(i-2);
	else
		exit(-1);
}
int main()
{
	int x;
	scanf("%d",&x);
	printf("%d",fun(x));
	return 0;
}