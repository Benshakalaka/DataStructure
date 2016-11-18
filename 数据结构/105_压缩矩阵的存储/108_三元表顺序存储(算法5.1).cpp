#include <stdio.h>				//包含书上的算法5.1和5.3
#include <malloc.h>
typedef int Etype;					//存储的元素的值的类型

#define MAXSIZE 2000				//一个矩阵总共的元素个数限制

typedef struct						//每个元素的数据类型
{
	int i,j;							//i,j分别表示行、列下标
	Etype e;							//所存的值
}Triple;
typedef struct
{
	Triple data[MAXSIZE+1];			//data[0]弃之不用，便于操作
	int mu,nu,tu;					//mu表示总行数 nu表示总列数 tu表示非零元素个数
}TMatrix;

void CreateMatrix(TMatrix &);								//创建稀疏矩阵M
void DestroyMatrix(TMatrix &);								//销毁稀疏矩阵M
void PrintMatrix(TMatrix &);								//输出稀疏矩阵M
void CopyMatrix(TMatrix,TMatrix &);							//由稀疏矩阵M复制得到T
bool AddMatrix(TMatrix,TMatrix,TMatrix &);					//求稀疏矩阵的和 Q=M+N
bool SubMatrix(TMatrix,TMatrix,TMatrix &);					//求稀疏矩阵的差 Q=M-N
bool MultMatrix(TMatrix,TMatrix,TMatrix &);					//求稀疏矩阵的乘积 Q=M*N
void TransposeMatrix(TMatrix,TMatrix &);					//求稀疏矩阵M的转置矩阵T

int main()
{
	TMatrix M,N,Q,T,X;
	CreateMatrix(M);
	CreateMatrix(N);
	PrintMatrix(M);
	PrintMatrix(N);
//	AddMatrix(M,N,Q);			//相加要求两矩阵具有相同行、列
//	PrintMatrix(Q);
//	TransposeMatrix(Q,T);		//转置无要求
//	PrintMatrix(T);
	MultMatrix(M,N,X);			//相乘则要求前一个和后一个的列和行相同
	PrintMatrix(X);
	return 0;
}

void CreateMatrix(TMatrix &M)					//创建稀疏矩阵M					此处要求严格顺序输入（任意输入以后的程序有）
{
	printf("Input the total lins and rows as well as the elements numner(which are not 0):\n");
	scanf("%d%d%d",&M.mu,&M.nu,&M.tu);					//行数 列数 非零元素
	M.data[0].e = M.data[0].i = M.data[0].j = 0;		//既然data[0]不用 那就全清零
	printf("You just have to input the element which is not 0.\n");
	int m,n,e,b=1,count;		//暂时用变量代替，要进行判断是否输入正确  b用来判定 count用来计数
	for(count=1;count<=M.tu;count++)		//一个一个来
	{	
		while(b)
		{
			printf("line 、row 、 value: ");
			scanf("%d%d%d",&m,&n,&e);
			if(m>=1 && m<=M.mu)
				if(n>=1 && n<=M.nu)
				{
					M.data[count].e = e;
					M.data[count].i = m;
					M.data[count].j = n;
					b = 0;
				}
			if(b!=0)
				printf("Sorry , input again.\n");
		}
		b=1;
	}
}

void PrintMatrix(TMatrix &M)					//输出稀疏矩阵M
{
	int count=1;			//计数
	int i,j;						//i为行数 j为列数
	for(i=1;i<=M.mu;i++)
	{
		for(j=1;j<=M.nu;j++)
		{
			if(i==M.data[count].i && j==M.data[count].j)
			{
				printf(" %d",M.data[count].e);
				count++;
			}
			else
				printf(" 0");
		}
		puts("");
	}
	puts("");
}

void DestroyMatrix(TMatrix &M)				//销毁稀疏矩阵M
{
	M.mu = 0;
	M.nu = 0;
	M.tu = 0;
}

void CopyMatrix(TMatrix M,TMatrix &T)					//由稀疏矩阵M复制得到T
{
	T = M;
}

bool AddMatrix(TMatrix M,TMatrix N,TMatrix &Q)					//求稀疏矩阵的和 Q=M+N
{
	if(M.mu!=N.mu || M.nu!=N.nu)				//因为加法是一个一个元进行的，是个体的，所以可以一个一个来，M里的这个元素比N里的那个元素快了，就让N元素加一，N快同理。遇到相同位置的时候就可以操作
		return false;
	Q.mu = M.mu;
	Q.nu = M.nu;
	Q.tu = 0;
	int count_m=1,count_n=1,temp;						//count_m、count_n为m、n计数器
	while(count_m<=M.tu && count_n<=N.tu)
	{
		if(M.data[count_m].i > N.data[count_n].i)			//这里进行的是行的比较，当然既然有值，就不可能是0，所以放进Q中去
			Q.data[++Q.tu] = N.data[count_n++];	
		else if(M.data[count_m].i < N.data[count_n].i)
			Q.data[++Q.tu] = M.data[count_m++];
		else if(M.data[count_m].i == N.data[count_n].i)
		{
			if(M.data[count_m].j > N.data[count_n].j)		//这里开始进行列的比较，这个慢了，当然就被落下了，也要放进Q中去
				Q.data[++Q.tu] = N.data[count_n++];
			else if(M.data[count_m].j < N.data[count_n].j)
				Q.data[++Q.tu] = M.data[count_m++];
			else if(M.data[count_m].j == N.data[count_n].j)			//相同位置就计算
			{
				temp = M.data[count_m].e+N.data[count_n].e;
				if(temp)												//非零才能放进
				{
					Q.data[++Q.tu].e = temp;
					Q.data[Q.tu].i = M.data[count_m].i;
					Q.data[Q.tu].j = M.data[count_m].j;
				}
				count_m++;
				count_n++;
			}
		}
	}		
	while(count_m<=M.tu)
		Q.data[++Q.tu] = M.data[count_m++];
	while(count_n<=N.tu)
		Q.data[++Q.tu] = N.data[count_n++];
	return true;
}

bool SubMatrix(TMatrix M,TMatrix N,TMatrix &Q)					//求稀疏矩阵的差 Q=M-N
{
	for(int i=1;i<=N.tu;i++)						//减法借助加法
		N.data[i].e *= -1;
	if(!AddMatrix(M,N,Q))
		return false;
	return true;
}

//算法5.3
bool MultMatrix(TMatrix M,TMatrix N,TMatrix &Q)					//求稀疏矩阵的乘积 Q=M*N
{
	if(M.nu!=N.mu)
		return false;
	//这里要为M，N提供每行（注意是行）开头的非零元素的下标,存储于temp_m,temp_n,这里num_m,num_n用于辅助 (这部分转置里有解释)
	int i;
	int *num_m = (int *)malloc(sizeof(int) * (M.mu+1));
	int *num_n = (int *)malloc(sizeof(int) * (N.mu+1));
	for(i=1;i<=M.mu;i++)
		num_m[i] = 0;
	for(i=1;i<=N.mu;i++)
		num_n[i] = 0;
	for(i=1;i<=M.tu;i++)
		num_m[M.data[i].i]++;
	for(i=1;i<=N.tu;i++)
		num_n[N.data[i].i]++;
	int *temp_m = (int *)malloc(sizeof(int) * (M.mu+1));
	int *temp_n = (int *)malloc(sizeof(int) * (N.mu+1));
	temp_m[1]=1;
	temp_n[1]=1;
	for(i=2;i<=M.mu;i++)
		temp_m[i]=temp_m[i-1]+num_m[i-1];
	for(i=2;i<=N.mu;i++)
		temp_n[i]=temp_n[i-1]+num_n[i-1];

	//得到temp_m,temp_n只是一小步骤
	Q.mu = M.mu;
	Q.nu = N.nu;
	Q.tu = 0;
	int *temp_Q = (int *)malloc((Q.nu+1) * sizeof(int));	//下面循环是按照一行一行来的 这里设立一个temp_Q[]来存储每列的内容
	for(i=1;i<=Q.nu;i++)
		temp_Q[i]=0;
	int j,k,t_m,t_n,g;		//j为M计数,k为N计数，t_m为M的元素限定范围（其值为下一行非零元素开头下标）t_n为N的元素限定范围,g为temp_Q所用
	for(i=1;i<=Q.mu;i++)			//结果矩阵一行一行来（用记过矩阵的行作为循环的依据）
	{
		if(i+1<=M.mu)
			t_m = temp_m[i+1];
		else
			t_m = M.tu+1;
		for(j=temp_m[i];j<t_m;j++)			//M的第一行  范围是这一行的开头坐标直到下一行的开头坐标为止（到了最后一行就用M.tu来限定）
		{
			if(M.data[j].j+1 <= N.mu)			//这里解释同上
				t_n = temp_n[M.data[j].j+1];
			else
				t_n = N.tu+1;
			for(k=temp_n[M.data[j].j];k<t_n;k++)//这里解释同上（也是用行 ， 而非平时计算用的列（因为平时都是M的行乘以N的列））
			{
				temp_Q[N.data[k].j]+=M.data[j].e * N.data[k].e;	//将对应的结果矩阵的第i行的第N.data[k].j个元素先存起来
			}
		}
		for(g=1;g<=Q.nu;g++)				//把存储的值归还给Q
		{
			if(temp_Q[g])						//确保非零
			{
				Q.data[++Q.tu].j = g;
				Q.data[Q.tu].i = i;
				Q.data[Q.tu].e = temp_Q[g];
			}
		}
		for(g=1;g<=Q.nu;g++)						//最后必须清零，不然下次会叠加
		temp_Q[g]=0;

	}
	free(num_m);
	free(num_n);
	free(temp_m);
	free(temp_n);
	return true;
}


//此为算法5.1
void TransposeMatrix(TMatrix M,TMatrix &T)				//求稀疏矩阵M的转置矩阵T
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	//转置的主要难点就在这  
	int *num = (int *)malloc((M.nu+1) * sizeof(int));		//用于记录M中每列（注意在M中是行）有多少个元素
	int *temp = (int *)malloc((M.nu+1) * sizeof(int));		//用于记录T中每行（注意在N中是列）开头元素的下标(看	理解.txt)
	int i;					//i作计数器
	for(i=1;i<=M.nu;i++)
		num[i] = 0;
	for(i=1;i<=M.tu;i++)
		num[M.data[i].j]++;
	temp[1] = 1;				//第一行总是以1为开头的
	for(i=2;i<=M.nu;i++)
		temp[i] = num[i-1] + temp[i-1];
	int j;
	//这里直接一个个操作   因为已经知道了该点在T矩阵中的位置（毕竟行是按顺序排列的）
	for(i=1;i<=M.tu;i++)
	{
		j = temp[M.data[i].j];
		T.data[j].e = M.data[i].e;
		T.data[j].i = M.data[i].j;
		T.data[j].j = M.data[i].i;
		temp[M.data[i].j]++;
	}
	free(num);
	free(temp);
}
