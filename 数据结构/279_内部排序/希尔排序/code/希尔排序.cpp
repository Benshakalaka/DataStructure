#include <stdio.h>

typedef int Keytype;

#define N 100

typedef struct
{
	Keytype key;
}Elemtype;

typedef struct
{
	Elemtype r[N];
	int length;
}SqList;

void Print(SqList L)
{
	for(int i=1;i<=L.length;i++)
		printf("%d ",L.r[i].key);
	puts("");
}

void ShellInsert(SqList &L,int dk)					//这个函数其实就是个插入函数  不过因为dk的存在使得整个插入的过程变成了跳跃式插入
{
	for(int i=dk+1;i<=L.length;i++)					//这里十分十分要注意是就是这个 “i=dk+1和i++”，两者很巧妙的实现了按增量分组的任务 。i=dk+1还可以理解，是下一个要访问的数。i++就不同了。按照插入排序的方式来的话应该是i+=dk; 但是一旦这样，就只能访问一组。如1、2、3、4、5 增量为2 i+=dk;的话只能访问1、3、5这组，2、4这组就跳过去了；然而用i++就可以都访问
		if(L.r[i].key < L.r[i-dk].key)
		{
			L.r[0] = L.r[i];			//0号用于存储
			for(int j=i-dk;j>0 && L.r[j].key>L.r[0].key;j-=dk)
				L.r[j+dk] = L.r[j];
			L.r[j+dk] = L.r[0];
		}
}

void ShellSort(SqList &L,int dlta[],int t)
{
	for(int k=0;k<t;k++)						//增量数组 dlta ，有3中增量，一种增量对数组进行一次排序 所以总共刚进行了3此排序
	{
		ShellInsert(L,dlta[k]);
		Print(L);
	}
}

#define n 10

int main()
{
	Elemtype r[n] = {{49},{38},{65},{97},{76},{13},{27},{49},{55},{04}};
	SqList L;
	L.length = n;
	int i;
	for(i=1;i<=n;i++)
		L.r[i] = r[i-1];
	int dlta[3] = {5,3,1};
	ShellSort(L,dlta,3);
	Print(L);
	return 0;
}