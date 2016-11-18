#include <stdio.h>
#include <malloc.h>

#define Max 999

//其实整个看起来和矩阵连乘差不多
void FormMatrix(double *a,double *b,int n,double **w,double **e,int **root)
//数组a 用于记录非叶子节点的概率；b数组记录叶子节点[什么是叶子节点？叶子节就是在树中找不到的数，叶子节点表示一个范围]的概率；n记录集合中元素个数；
//二维数组w用于记录子树的概率之和；e用于记录子树的期望代价；root用于记录根节点
{
	int i;
	for(i=0;i<=n;i++)							//这个循环是初始化这种情况的：一个子树上只有叶子节点的情况(即只有虚拟键)
	{
		w[i+1][i] = b[i];					//之所以是 [1,0],[2,1]...这种是因为矩阵的摆放  可以倒过来理解 [0,1] [1,2] 就是叶子节点 满足在 0,1之间、1，2之间这种
		e[i+1][i] = b[i];
	}
	int j,k;
	double temp;
	for(j=0;j<n;j++)
		for(i=1;i<=n-j;i++)
		{
			w[i][i+j] = w[i][i+j-1]+a[i+j]+b[i+j];		//这是由固定公式的 就是相加
			e[i][i+j] = Max;							//可以先令这个等于很大的一个数，之后比较得到最优的数【最小】
			for(k=i;k<=i+j;k++)						//在 [i][i+j]之间挑选出根节点k，使得e值最小
			{
				temp = e[i][k-1]+e[k+1][i+j];
				if(e[i][i+j] > temp)
				{
					e[i][i+j] = temp;
					root[i][i+j] = k;				//记录下此时的根节点
				}
			}
			e[i][i+j] += w[i][i+j];
		}
	for(i=0;i<=n+1;i++)
		for(j=0;j<=n+1;j++)
			printf("%.2lf%c",w[i][j],(j+1)%(n+2)==0?'\n':' ');
	puts("");
	for(i=0;i<=n+1;i++)
		for(j=0;j<=n+1;j++)
			printf("%.2lf%c",e[i][j],(j+1)%(n+2)==0?'\n':' ');
	puts("");
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			printf("%d%c",root[i][j],(j+1)%(n+1)==0?'\n':' ');
}

int main()
{
	double a[6] = {-1,0.15,0.1,0.05,0.1,0.2};			//元素个数为n个
	double b[6] = {0.05,0.1,0.05,0.05,0.05,0.1};		//叶子节点数为n+1个
	int n = 5;
	double **w,**e;
	int **root;
	int i,j;
	root = (int **)malloc((n+1)*sizeof(int*));			//root用于记录根节点 如root[i][j] 表示从第i个元素到第j个元素这一段所选取的根节点下标
	for(i=0;i<=n;i++)
		root[i] = (int *)malloc(sizeof(int)*(n+1));		//root 是 (n+1)*(n+1)的 但是0号是抛弃的
	w = (double **)malloc((n+2)*sizeof(double*));		//w记录概率之和 如 w[i][j] = b[i-1]+a[i]+b[i]+···+a[j],b[j]
	for(i=0;i<=n+1;i++)
		w[i] = (double *)malloc(sizeof(double)*(n+2));	//w 是 (n+2)*(n+2)的，行上0号是抛弃的，n+1号是有用的；列上n+1是抛弃的，0号是有用的；为什么呢？因为有一个子树上只有叶子节点的情况(即只有虚拟键)，这种情况下j=i-1, e[i][i-1]=b[i-1],即对应本程序11行的循环初始化 从 [1][0] 到 [6][5]分别为b数组的值；另外的情况就是j>=i的，需要在这之间选出根
	for(i=0;i<=n+1;i++)							
		for(j=0;j<=n+1;j++)
			w[i][j] = 0; 
	e = (double **)malloc((n+2)*sizeof(double*));			//e表示期望代价  如e[i][j] = e[i][k-1] + e[k+1][j] + w[i][j]
	for(i=0;i<=n+1;i++)
		e[i] = (double *)malloc(sizeof(double)*(n+2));		//e 是 (n+2)*(n+2)的 行上和列上的属性是和w相同的
	for(i=0;i<=n+1;i++)
		for(j=0;j<=n+1;j++)
			e[i][j] = 0;
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			root[i][j] = 0;
	FormMatrix(a,b,n,w,e,root);
	return 0;
}