#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

double fun(double a,double b,char c)					//单步计算
{
	switch(c)
	{
	case '*':
		return a*b;
	case '/':
		if(b==0)
		{
			printf("Hehe\n");
			exit(1);
		}
		return a/b;
	case '+':
		return a+b;
	case '-':
		return a-b;
	}
	return 0;
}

double translate(char *s,int *count)						//将字符转化为数字
{
	char m[20];int i=0,j=0;double sum=0.0;int temp=0;
	while(*s && (*s>='0' && *s<='9') || *s=='.')
	{
		if(*s!='.') 
		{
			if(temp==0)	
				m[i++] = *s;
			else
				m[i+j++] = *s;
		}
		else 
			temp++;
		s++;
	}
	if(temp!=0)
		*count = i+j+1;
	else
		*count = i+j;
	int k=0,i_temp=i;
	while(i>0)
	{
		sum+=(m[k]-'0')*pow(10.0,i-1);
		i--;k++;
	}
	while(j>0)
	{
		sum+=(m[i_temp+j-1]-'0')*pow(10.0,(-j));
		j--;
	}
	return sum;
}

bool Judge(char *ss)												//判断括号是否匹配
{
	s X;
	init(&X);
	char tc;
	double ttc;
	char *tp;
	tp = ss;
	while(*tp)
		switch(*tp)
	{
		case '(':
			push(&X,*tp);tp++;break;
		case ')':
			if(empty(&X))
			{
				clear(&X);
				return false;
			}
			else
			{
				pop(&X,&ttc);
				tc = (int)ttc;
				if(tc=='('&&*tp==')')
				{
					tp++;break;
				}
				else
				{
					clear(&X);
					return false;
				}
			}
		default:
			tp++;
	}
	if(empty(&X))
	{
		clear(&X);
		return true;
	}
	else
	{
		clear(&X);
		return false;
	}
}

bool Judgechar(char c)						//判断字符				④
{
	if((c>='0'&&c<='9') || c=='+' || c=='-' || c=='*' || c=='/' ||c=='(' || c==')')
		return true;
	else
		return false;
}

double Cal(char *ss)
{
	s S1;				//存数字
	s S2;				//存运算符
	init(&S1);
	init(&S2);	
	char *p = ss;
	double cc,x,x1,x2,temp;int count;
	char c;
	while(*p!='\n' )
	{
		if(!Judgechar(*p))
		{
			printf("Wring Form!\n");
			exit(1);
		}
		switch(*p)
		{
			case '(':
				if((p-ss)!=0)								//避免 如 2(2+4) 这种错误输入格式
					if(*(p-1)>='0' && *(p-1)<='9')
					{
						printf("Wrong Form!\n");
						exit(1);
					}
				if(*(p+1)=='-')							//单目运算符的存在
					push(&S1,0.0);
				push(&S2,*p);
				p++;
				break;
			case ')':
				if(*(p+1)>='0' && *(p+1)<='9')				//①
				{
					printf("Wrong Form!\n");
					exit(1);
				}
				if(empty(&S2)==1)
				{
					exit(1);
				}
				pop(&S2,&cc);
				c = (int)cc;
				while(c != '(')
				{
					pop(&S1,&x2);
					pop(&S1,&x1);
					x = fun(x1,x2,c);
					push(&S1,x);
					pop(&S2,&cc);
					c = (int)cc;
				}
				p++;
				break;
			case '+':
			case '-':
				if(*(p+1)=='\n')					//②
				{
					printf("Wrong Form!\n");
					exit(1);
				}
				if(empty(&S2))
				{
					push(&S2,*p);
					p++;break;
				}
				else
				{
					pop(&S2,&cc);
					c = (int)cc;
				}
				if(c=='(')
				{
					push(&S2,cc);
					push(&S2,*p);
					p++;break;
				}
				
				pop(&S1,&x2);
				pop(&S1,&x1);
				x = fun(x1,x2,c);
				push(&S1,x);	
				break;
			case '*':
			case '/':
				if(*(p+1)=='\n')					//③
				{
					printf("Wrong Form!\n");
					exit(1);
				}
				if(empty(&S2))
				{
					push(&S2,*p);
					p++;break;
				}
				pop(&S2,&cc);
				c = (int)cc;
				if(c=='+' || c=='-' || c=='(')
				{
					push(&S2,c);
					push(&S2,*p);
					p++;
				}
				else
				{
					pop(&S1,&x2);
					pop(&S1,&x1);
					x = fun(x1,x2,c);
					push(&S1,x);
				}
				break;
			default:
				if((*p>='0' && *p<='9') || *p=='.')
				{
					temp=translate(p,&count);
					push(&S1,temp);
				}
				p+=count;
				break;
		};
	}
	while(!empty(&S2))
	{
		pop(&S2,&cc);
		c = (int)cc;
		pop(&S1,&x2);
		pop(&S1,&x1);
		x = fun(x1,x2,c);
		push(&S1,x);
	}
	pop(&S1,&x);
	clear(&S1);
	clear(&S2);
	return x;
}

int main()
{
	char s[100];
	fgets(s,100,stdin);	
	if(!Judge(s))
	{
		printf("Wrong Form!\n");
		return 0;
	}
	double result;
	result = Cal(s);
	printf("%lf\n",result);
	return 0;
}

