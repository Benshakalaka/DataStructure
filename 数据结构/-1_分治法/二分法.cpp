#include <stdio.h>						//利用分治 来解决寻找的问题
int Divide(int *a,int head,int tail,int value)
{		//a是一个非递减数组
	if(value==a[(head+tail)/2])									//将要寻找的数与中间数比较 相等则返回
		return (head+tail)/2;
	else if(value<a[(head+tail)/2])								//比中间数小则在左边寻找
		return Divide(a,head,(head+tail)/2,value);
	else														//否则右边寻找
		return Divide(a,(head+tail)/2+1,tail,value);
}
int main()
{
	int a[] = {2,3,5,6,7,9,22,34};
	int num = Divide(a,0,8,2);
	printf("%d\n",num+1);
	return 0;
}