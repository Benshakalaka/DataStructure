#include <stdio.h>					//后缀表达式的实现（栈的应用）
#include "stack.h"
int main()
{
	s X;
	init(&X);
	char s[30],*tp,tc;
	scanf("%s",s);
	tp = s;										//接收该方程式
	while(*tp)									//直到最后空字符
		switch(*tp)								//利用switch
	{
		case '(':
			push(&X,*tp);tp++;break;		//任何情况下‘（ ’都是可以插入的
		case ')':
			if(empty(&X))					//出现 ‘）’，一开始就有是违法的
				exit(1);
			pop(&X,tc);						//合法的话 就把‘（ ’到‘ ）’之间的全输出
			while(tc != '(')
			{
				printf("%c",tc);
				pop(&X,tc);
			}
			tp++;
			break;
		case '+':
		case '-':
			if(!empty(&X))									//加减好按照设计无论遇到什么都要先出让进的
			{
				pop(&X,tc);
				if(tc == '(')								//这里提前pop了 所以如果把 ‘（ ’不小心弄出去了 要补回来 否则括号部分就无穷循环了
				{
					push(&X,tc);
				}
				else
				printf("%c",tc);
			}
			push(&X,*tp);						//前面已经出了 这里进
			tp++;
			break;
		case '*':
		case '/':
			if(!empty(&X))								//乘除号遇到加减直接进 遇到同等级先出让进
			{
				pop(&X,tc);								//这里同样提前出了
				
				if(tc == '(' || tc=='+'|| tc=='-')							//遇到括号、遇到低级 则提前出的要补回来
					push(&X,tc);
				else
					putchar(tc);
			}
			push(&X,*tp);							//统一进
			tp++;
			break;
		default:
			putchar(*tp);					//遇字母数字  则出去
			tp++;
			break;
	}
	while(!empty(&X))											//最后清空栈里的东西
	{
		pop(&X,tc);
		printf("%c",tc);
	}
	puts("");
	return 0;
}