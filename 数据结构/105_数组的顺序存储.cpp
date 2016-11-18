//数组的顺序存储表示				将多维数组转化成一维数组			难点主要在A.constants 的初始化这里的理解
#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_DIM 8		//定义最大维数为8
typedef int Elemtype;

typedef struct
{
	Elemtype *base;		
	int dim;			//维数
	int *bounds;		//维界基址
	int *constants;		//数组映像函数常量基址
}Array;

//初始化
bool InitArray(Array &A, int dim,...)
{
	if(dim<1 || dim>MAX_DIM)
		return false;
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int));
	if(!A.bounds)
		return false;
	va_list p;
	va_start(p,dim);
	int i,elemtotal=1;
	for(i=0;i<dim;i++)
	{
		A.bounds[i] = va_arg(p,int);
		elemtotal *= A.bounds[i]; 
	}
	A.base = (Elemtype *)malloc(elemtotal * sizeof(Elemtype));
	if(!A.base)
		return false;
	A.constants = (int *)malloc(sizeof(int) * dim);					//这个意思是  ： 第几维变量加一那内存需要跳过几个 
	A.constants[dim-1] = 1;											//这就意味着最后一维（也就是一维（也就是直线，二维相当于平面））加一那内存就要加一个空间【看下面的解释】
	for(i=dim-2;i>=0;i--)											//假设三维 比如A[3][4][2]. 那A[0][0][0] 到 A[0][0][1] 内存加 1 ；A[0][0][0] 到 A[0][1][0] 内存加 1*2=2 ；A[0][0][0] 到A[1][0][0] 内存加4*2=8；
		A.constants[i] = A.constants[i+1] * A.bounds[i+1];
	return true;
}

//销毁 
bool DestroyArray(Array &A)			//处理
{
	if(!A.base) return false;
	free(A.base);
	A.base = NULL;
	if(!A.bounds) return false;
	free(A.bounds);
	A.bounds = NULL;
	if(!A.constants) return false;
	free(A.constants);
	A.constants = NULL;
	return true;
}

//为下面函数调用做准备
bool Locate(Array &A,va_list p,int &off)						//定位 并把地址给off
{
	int i,temp;
	off = 0;
	for(i=0;i<A.dim;i++)
	{
		temp = va_arg(p,int);
		if(temp<0 || temp>=A.bounds[i])
			return false;
		off += A.constants[i] * temp;
	}
	return true;
}
bool Value(Array &A,Elemtype *e,...)	//把对应的位置的数赋给e
{
	va_list p;
	va_start(p,e);
	int off;
	if(!Locate(A,p,off))
		return false;
	*e = *(A.base+off);
	return true;
}
bool Assign(Array &A,Elemtype e,...)	//给对应位置赋值
{
	va_list p;
	va_start(p,e);
	int off;
	if(!Locate(A,p,off))
		return false;
	*(A.base+off) = e;
	return true;
}

int main()																//测验
{
	Array A;
	int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2;
	Elemtype e,*pl;
	InitArray(A,dim,bound1,bound2,bound3);
	p = A.bounds;
	printf("A.bounds : ");
	for(i=0;i<dim;i++)
		printf("%d ",*(p+i));
	p = A.constants;
	printf("A.consts : ");
	for(i=0;i<dim;i++)
		printf("%d ",*(p+i));
	printf("\n%d页%d行%d列的元素是：\n",bound1,bound2,bound3);			//三维的看成书的页 行 列
	for(i=0;i<bound1;i++)
	{
		for(j=0;j<bound2;j++)
		{
			for(k=0;k<bound3;k++)
			{
				Assign(A,i*100+j*10+k,i,j,k);
				Value(A,&e,i,j,k);
				printf("A[%d][%d][%d]=%-5d",i,j,k,e);
			}
			puts("");
		}
		puts("");
	}



	pl = A.base;
	printf("A.base : \n");
	for(i=0;i<bound1*bound2*bound3;i++)
	{
		printf("%5d",*(pl+i));
		if((i+1)%(A.constants[0])==0)		//按页（A.bound[0]）换行
			puts("");
	}
	DestroyArray(A);
	return 0;
}






/*网上解释

大致明白了，bounds存的就是每一维里面的个数，constants保存的是每一个维度如果下标增加1，那个对应到内存空间的下标应该增加多少。说起来比较抽象，我们假设是3维，就比较容易说清楚了，首先把3维看作有bounds[0]那么高，
对于每一个0到bounds[0]-1的范围内，就是一个平面，这个平面有bounds[1]那么长，bounds[2]那么宽。那么，我们把高=0，长=0，宽=0对应到内存的第一个位置，高=0，长=0，宽=1的对应到第二个位置，那么高=0，长=1，宽=0应该放
在什么位置呢？显然就是0+bounds[2]这个位置。那么高=1，长=0，宽=0的那个元素应该在哪个位置呢？显然是高=0这一个平面放完了之后的那个位置，高=0这个平面有长度*宽度那么多个元素，也就是bounds[1]*bounds[2]这么多个元
素，所以高=1，长=0，宽=0这个元素就应该在0+bounds[1]*bounds[2]这个位置，对吧。假设还有第四维度，我们假设这个维度代表时间吧，那时间=0，高=0，长=0，宽=0的元素放在内存第0个位置，那么时间=1，高=0，长=0，宽=0的元
素是不是应该放在0+bound[1]*bound[2]*bound[3]这个位置呢。这就是A.constants[i]=A.bounds[i+1] * A.constants[i+1];这个公式的来历。当然，我只是很简单的解释了，很多细节需要你自己考虑，因为语言表示起来太复杂了，
不知道怎么表述。。。
补充：
其实你仔细看A.constants[i]=A.bounds[i+1] * A.constants[i+1];，这是一个递推公式，把它展开的话，下面我就把constants[i]简写为coni，bounds[i]简写为boni那么
con i= bon[i+1]*con[i+1]=bon[i+1]*bon[i+2]*con[i+2] = bon[i+1]*bon[i+2]*bon[i+3]*con[i+3]
=bon[i+1]*bon[i+2]*bon[i+3]*...*bon[dim-1]你看这个公式是不是就是相当于上面说的高度*长度*宽度？
然后我们看最后一维，例如上面例子的宽度，宽度+1是不是就正好内存地址+1呢？于是对应宽度这个最后的维度，每次地址只需+1就能访问下一个元素，因此bon[dim-1]也就是最后一维的，是不是就应该等于1呢。。。于是，
上面的程序就能够搞懂了吧。
*/