#include <stdio.h>
#include "stack.h"
int main()
/*{												//八进制
	s X;
	init(&X);
	int N,m;			//N是输入 m是暂存输出
	scanf("%d",&N);
	while(N)
	{
		push(&X,N%8);
		N/=8;
	}
	while(!empty(&X))
	{
		pop(&X,m);
		printf("%d  ",m);
	}
	return 0;
}*/
{												//十六进制
	s X;
	init(&X);
	int N,m;
	scanf("%d",&N);
	while(N)
	{
		push(&X,N%16);
		N/=16;
	}
	while(!empty(&X))
	{
		pop(&X,m);
		if(m<=9)
		printf("%d  ",m);
		else
			printf("%c  ",m+55);
	}
	return 0;
}
