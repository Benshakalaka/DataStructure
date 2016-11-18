#include <stdio.h>				//与两个栈实现一个队列相对应
#include "queue.h"

int main()
{
	int a[] = {1,2,3,4,5,6,7};
	pss Queue_A,Queue_B;
	Queue_A = (pss)malloc(sizeof(ss));
	Queue_B = (pss)malloc(sizeof(ss));
	init(Queue_A);
	init(Queue_B);
	int i;
	for(i=0;i<7;i++)
		en_queue(Queue_A,a[i]);
	printf("Datas stored in Queue_A:\n");					//输出存储在A中的数据
	for(i=0;i<7;i++)
		printf("%d%c",a[i],(i+1)%7==0?'\n':' ');
	int temp;
	//以下为按照栈的形式输出第一个数
	for(i=0;i<6;i++)										//将队列A中数据逐个导入B中，但是 最后一个数不导 而是直接输出out_queue  这样就把最后一个数第一个输出了
	{
		out_queue(Queue_A,temp);
		en_queue(Queue_B,temp);
	}
	printf("Output the first data as Stack-style : \n");
	out_queue(Queue_A,temp);
	printf("%d\n",temp);
	//以上是输出一个数 那如果要连续输出呢
	//以下就是连续输出   为了避免只将一个栈作为存储 而另一个作为临时的浪费 利用两个指针
	pss p, q;
	if(is_empty(Queue_A))
	{
		p = Queue_B;
		q = Queue_A;
	}
	else
	{
		p = Queue_A;
		q = Queue_B;
	}
	while(!is_empty(p))						//将p作为有数的那个栈 q作为空栈
	{
		while(current(p)>1)					//将p中最后一个数输出  
		{
			out_queue(p,temp);
			en_queue(q,temp);
		}
		out_queue(p,temp);
		printf("%d ",temp);
		if(is_empty(Queue_A))				//有数的队列已经变成了另一个 此刻将p指针指向这个队列
		{
			p = Queue_B;
			q = Queue_A;
		}
		else
		{
			p = Queue_A;
			q = Queue_B;
		}
	}
	puts("");
	return 0;
}