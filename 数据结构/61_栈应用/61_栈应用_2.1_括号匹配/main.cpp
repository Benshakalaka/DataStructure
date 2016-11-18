/*#include <stdio.h> 
#include "stack.h"
#include <stdlib.h>
int main()
{
	s X;
	init(&X);
	char tc;
	char s[20],*tp;
	scanf("%s",s);
	tp = s;
	while(*tp)
	{
		if(empty(&X))
			push(&X,*tp);
		else
		{
			pop(&X,tc);
			if(tc == '(')
			{
				if(*tp == ')');
				else if(*tp == ']')
				{
					printf("NO\n");
					exit(1);
				}
				else
				{
					push(&X,tc);
					push(&X,*tp);	
				}
			}
			else if(tc == '[')
			{
				if(*tp == ']');
				else if(*tp == ')')
				{
					printf("NO\n");
					exit(1);
				}
				else
				{
					push(&X,tc);
					push(&X,*tp);
				}
			}
			else
			{
				printf("NO\n");
				break;
			}
		}
		tp++;
	}
	if(!empty(&X))
		printf("NO\n");
		else
		printf("OK\n");
	return 0;
}*/

// 下面是书上的答案
#include <stdio.h> 
#include "stack.h"
#include <stdlib.h>
int main()
{
	s X;
	init(&X);
	char tc;
	char s[20],*tp;
	scanf("%s",s);
	tp = s;
	while(*tp)
		switch(*tp)
	{
		case '(':
		case '[':
			push(&X,*tp);tp++;break;
		case ')':
		case ']':
			if(empty(&X))
			{
				printf("NO Matching\n");
					exit(1);
			}
			else
			{
				pop(&X,tc);
				if((tc=='('&&*tp==')') || (tc=='['&&*tp==']'))
				{
					tp++;break;
				}
				else
				{
					printf("NO Matching\n");
					exit(1);
				}
			}
		default:
			tp++;
	}
	if(empty(&X))
		printf("OK\n");
	else
		printf("NO Matching\n");
	return 0;
}
//总的来说 相比之下 还是欠考虑了
//一个是switch 的使用 一个是好多次tp++都没写