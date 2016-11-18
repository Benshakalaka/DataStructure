#include <stdio.h>          //最简单的递归  阶乘
int fun(int);
int main()
{
	printf("%d",fun(5));
	return 0;
}

int fun(int a)
{
	/*int s=a;
	if(a>1)
		s*=fun(a-1);
	return s;*/
	if(a==1)
		return 1;
	else 
		return fun(a-1)*a;
}

                                          // a * fun(a-1)
                                               //(a-1) * fun(a-2)
												       //(a-2) * fun(a-3) 
																//------------