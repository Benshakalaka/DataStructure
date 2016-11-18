#include <stdio.h>
#include <malloc.h>

void LCSLength(int m,int n,int *a,int *b,int **c)		//通过这个函数我们可以知道最长子序列的长度 但无法得知确切的路径 
{		//m为a长度 n为b长度	c为子序列长度集 
	int i,j;
	for(i=0;i<=m;i++)
		c[i][0] = 0;
	for(i=0;i<=n;i++)
		c[0][i] = 0;					//这两步清零是 对整个过程初始化 或者说是走的第一步 在i和j都为0的情况下该行该列都为0 
	for(i=1;i<=m;i++)			//这里并没有指定一定要拿谁作为主要的循环依据	既然我们由自上至下的思考得知对c[i][j] 每一个都有所求 
		for(j=1;j<=n;j++)
		{
			if(a[i]==b[j])
				c[i][j] = c[i-1][j-1]+1;			//满足这种情况	c[i][j]  =   c[i-1][j-1]+1		i,j>0; xi = yi;
			else if(c[i-1][j]>=c[i][j-1])			//下面比较则为  max {c[i][j-1] , c[i-1][j] }	i,j>0; xi ≠ yi
				c[i][j] = c[i-1][j];
			else
				c[i][j] = c[i][j-1];
		}
}

													//总的来说 还是需要自上至下的思考 然后利用这种思想进行自下而上的计算  得到最终结果


int main()
{
	int a[8] = {0,1,2,3,2,4,1,2};
	int b[7] = {0,2,4,3,1,2,1};
	int **c;
	c = (int **)malloc(sizeof(int *)*8);
	int i;
	for(i=0;i<8;i++)
		c[i] = (int *)malloc(sizeof(int)*7);
	int **d;
	LCSLength(7,6,a,b,c,d);
	int j;
	for(i=0;i<8;i++)
		for(j=0;j<7;j++)
			printf("%d%c",c[i][j],(j+1)%7==0?'\n':' ');
	return 0;
}