#include <stdio.h>					//按照程序过程可看出运作过程 但是这课树是不存在的  难理解。。
#include "List.h"

void Getpower(int i,pS A,pS &B)
{
	if(i > ListLength(A))							//当i大于长度时候 说明已经到了最后一层
		Traverse(B,print);
	else
	{
		int k,g;
		GetList(A,i,k);
		g = ListLength(B);
		
		InsertList(B,g+1,k);					//取
		Getpower(i+1,A,B);
		
		DeleteList(B,g+1);						//舍
		Getpower(i+1,A,B);
	}
}

int main()
{
	pS A,B;
	A = InitList();
	B = InitList();
	InsertList(A,1,1);
	InsertList(A,2,2);
	InsertList(A,3,3);
	Getpower(1,A,B);
	return 0;
}
