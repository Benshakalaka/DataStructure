//动态规划问题
#include <stdio.h>					//用于处理多个矩阵相乘的最优方案  当然本题不是为了求解而是为了得到如何求解（如何加括号，因为满足结合律 所以哪几个先处理会很影响效率）的方案
#include <malloc.h>

struct Ma								//矩阵的结构 包含行和列		
{
	int line;
	int column;
}p[] = {								//这里弄了6个矩阵相乘  根据书上的例题而来 分别为行和列
		{0,0},
		{30,35},{35,15},{15,5},
		{5,10},{10,20},{20,25}	
	};

//利用动态规划 利用矩阵表示如何求解效率最高
void MatrixChain(struct Ma *p,int n,int **m,int **s)		
//p为每个矩阵的行和列数组；n为相乘个数；m为二维数组，记录两个矩阵相乘所需处理的最优次数，比如 m[2][5] 的值记录的就是矩阵 A2*A3*A4*A5 的最优(少)求解次数(当然，
//A2*A3*A4*A5 中这里那里都有可能出现个括号)；s为断点记录 如k=s[1][6] 的值说明从A1*...*A6 中的第k个地方是断点，k左边与k右边变成分开的来那个部分 即 (A1,..,Ak)(Ak+1,...An)
{
	int d,i,j,k;
	int temp;

	//以下是 (j==i)的时候
	for(i=1;i<=n;i++)						//先处理m[i][i] 即对角线上的数，从自身到自身 不需要加括号 所以次数是0
		m[i][i] = 0;

	//以下则是求当 (j>i)的时候
	for(d=1;d<n;d++)						//要考虑这个主循环的由来 首先要知道求解顺序(看图) 之后，顺应下面的内层循环设置外层循环
		for(i=1;i<=n-d;i++)					//这里的 判断条件 （i<=n-d）的含义是 （i+d<=n）因为i+d就是另一个矩阵
		{
			j = i+d;	//另一个矩阵序号
			m[i][j] = m[i][i] + m[i+1][j] + p[i].line * p[i].column * p[j].column;		//先将第一个求出来 可以在下面进行比较或在j=i+1的时候无法进入下面循环
			s[i][j] = i;																//同时记录断点
			for(k=i+1;k<j;k++)	//比较取最优解
			{
				temp = m[i][k] + m[k+1][j] + p[i].line * p[k].column * p[j].column;			//求m值与上面相同 (原理见图)
				if(temp < m[i][j])
				{
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
}

void Traceback(int i,int j,int **s)
{
}

int main()
{
	//以下为初始化变量，由于m[][] 的形式 不能作为 **m 传入函数 所以只能mallo 两个二维数组
	int i,j;
	int **m,**s;
	m = (int **)malloc(sizeof(int *)*7);
	for(i=0;i<7;i++)
		m[i] = (int *)malloc(sizeof(int));
	s = (int **)malloc(sizeof(int *)*7);
	for(i=0;i<7;i++)
		s[i] = (int *)malloc(sizeof(int));
	for(i=0;i<=6;i++)									//并且初始化  方便输出 
		for(j=0;j<=6;j++)
			m[i][j] = s[i][j] = 0;


	MatrixChain(p,6,m,s);								//函数处理  整个程序的精髓就在这里 这个函数处理的两个矩阵就是解除问题的方案
	

	for(i=0;i<=6;i++)										//输出m
		for(j=0;j<=6;j++)
			printf("%d%c",m[i][j],(j+1)%7==0?'\n':' ');
		puts("");
	for(i=0;i<=6;i++)										//输出s
		for(j=0;j<=6;j++)
			printf("%d%c",s[i][j],(j+1)%7==0?'\n':' ');
	return 0;
}
