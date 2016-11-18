#include <stdio.h>
void fun(int n)
{
	if(n>0)
	{
		printf("%d  ",n);
		fun(n-1);
	}
	else
		return;
}
void fun2(int n)
{
	if(n>0)
		fun2(n-1);		
	else
		return;	
	printf("%d  ",n);

}
int main()
{
	printf("递归:\n");
	fun(5);
	putchar('\n');
	fun2(5);
	putchar('\n');
	printf("循环:\n");
	for(int j=1;j<=5;j++)
		printf("%d  ",j);
	return 0;
}