#include <stdio.h>				//实现 出队列操作
#include <malloc.h>
#include "stack.h"
//不难理解  只是在看到问题时候是否想得到是否有思路  将两个栈一起来实现队列的出队
//一道面试题 无意中看到的
int main()
{
	ps Stack_A = (ps)malloc(sizeof(s));
	ps Stack_B = (ps)malloc(sizeof(s));
	init(Stack_A);
	init(Stack_B);
	int i;
	int a[] = {1,2};
	printf("The origin order of the array:\n");
	for(i=0;i<2;i++)
		printf("%d ",a[i]);
	puts("");
	for(i=0;i<2;i++)
		push(Stack_A,a[i]);
	printf("Datas in Stack_A:\n");
	traverse(Stack_A);
	int temp;
	while(!empty(Stack_A))				//此处可以优化	可以计数  不必将所有都导入B 而是留下A中的最后一个 继而直接输出 而不是导入B后由B输出
	{
		pop(Stack_A,temp);
		push(Stack_B,temp);
	}
	printf("Datas in Stack_B:\n");
	traverse(Stack_B);
	pop(Stack_B,temp);
	printf("Output the first number as the Queue-style :\n");
	printf("%d\n",temp);
	//以上实现的是一次性  往下则是需要反复入队出队
	//一种方式是在取出一个元素后，将所有元素导入A如果需要入队则直接入A  之后按需重复上述步骤
	//还有一种方式如下：
	//如果需要入队
	//以下的if不一定需要  意思是如果要入队 则直接进A  （为什么不需要来回倒腾一番呢？因为我要入队的数全都暂时存在A中 一旦B中的数消耗掉了 就将A中的数字导入B）
	/*if(empty(Stack_A))					//如果A是空的 则需要将B中的全部导入A，然后将此数入A
		while(!empty(Stack_B))
		{
			pop(Stack_B,temp);
			push(Stack_A,temp);
		}*/		
	push(Stack_A,10);					//不空的话 说明数全在A中 直接将此数入A
	//需要出队
	//这种方式如果要出队 并不会在上一次出队后将B中所有数全倒回A 而是将计就计（当然 这得需要没有新增的入队操作） 
	if(empty(Stack_B))					//如果为空，则将A中的全部导入B
		while(!empty(Stack_A))
		{
			pop(Stack_A,temp);
			push(Stack_B,temp);
		}
	printf("Datas in Stack_B:\n");
	traverse(Stack_B);
	pop(Stack_B,temp);					//如果不空 则说明数全在B中（或者说并没有进行入队操作） 则直接将B中数据pop
	printf("Output the next number as the Queue-style :\n");
	printf("%d\n",temp);
	//当然 如果要继续的话 可以设循环
	return 0;
}