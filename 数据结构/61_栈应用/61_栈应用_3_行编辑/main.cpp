#include <stdio.h>							//行编辑程序  ‘#’退格 ‘@’整行废弃
#include <string.h>
#include "stack.h"
int main()
{
	s X;
	init(&X);
	char s[30],tc,*tp;
	gets(s);
	int len=0;
	tp = s;
	while(*tp)
		switch(*tp)
	{
		case '#':
			if(empty(&X))
			{
				tp++;
				break;
			}
			pop(&X,tc);
			len--;
			tp++;
			break;
		case '@':
			while(!empty(&X))
				pop(&X,tc);
			tp++;
			len = 0;
			break;
		default:
			push(&X,*tp);tp++;len++;break;
	}
	char s2[30];
	int i=len;
	while(!empty(&X))						//改变输出顺序
	{
		pop(&X,tc);
		s2[i-1] = tc;
		i--;
	}
	s2[len] = '\0';
	printf("%s\n",s2);
	return 0;
}