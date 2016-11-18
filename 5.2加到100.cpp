#include <stdio.h>                //极其简单的递归  1+2+3-----+100
int fun(int);
int main()
{
	printf("it is  %d\n",fun(100));
	return 0;
}
int fun(int a)
{
	if(a<=1)
		return 1;
	else
		return a+fun(a-1);
}
