#include "head.h"


void Create_Seq(SSTable &ST,int n,Elemtype* r)										//构建一个含n个数据元素的静态顺序查找表
{
	int i;
	ST.elem = (Elemtype *)malloc((n+1)*sizeof(Elemtype));
	if(!ST.elem)
		exit(1);
	for(i=1;i<=n;i++)
		ST.elem[i] = r[i-1];
	ST.length = n;
}

void Ascend(SSTable &ST)												//重建查找表为按关键字的非降序排序
{											//这个算法是选择算法 只不过将其拆解了 选择算法是拿一个和其余剩下的所有进行比较 选出最小的然后swap
	int i,j,k;
	for(i=1;i<=ST.length;i++)							//第一层循环 
	{
		k = i;
		ST.elem[0] = ST.elem[i];					//这里借助这个空着的ST.elem[0] 当作temp
		for(j=i+1;j<=ST.length;j++)
			if(LT(ST.elem[j].key,ST.elem[0].key))			//挑选出比当前数小且是最小的
			{
				k = j;
				ST.elem[0] = ST.elem[j];
			}
		if(k!=i)									//存在这个最小的数 那么交换
		{
			ST.elem[j] = ST.elem[i];
			ST.elem[i] = ST.elem[0];
		}
	}
}

void Create_Ord(SSTable &ST,int n,Elemtype*r)										//构建一个含n个数据元素的静态非降序排序顺序查找表
{
	Create_Seq(ST,n,r);
	Ascend(ST);
}

void Destroy(SSTable &ST)					//销毁
{
	free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
}

int Search_Seq(SSTable &ST,Keytype key)									//算法9.1	在顺序表中查找其关键字等于等于key的数据元素，若找到 则函数值为表中位置 否则为0
{
	//**************************ST.elem[0]起到哨兵作用 虽然仅仅是一个程序设计上的小小改进，然而实践证明，在长度大于1000时 查找所需平均时间几乎减少一半*********************************
	ST.elem[0].key = key;									//0号留空的目的是存储用户要查询的key 方便下面的for循环
	for(int i=ST.length;!EQ(ST.elem[i].key,key);i--);		//如果找到的话就直接返回位置；否则未找到 i-- 一直到i==0的时候循环停止 因为ST.elem[0] = key;
	return i;
}

int Search_Bin(SSTable &ST,Keytype key)									//算法9.2	在顺序表中查找其关键字等于等于key的数据元素，若找到 则函数值为表中位置 否则为0
{													//二分查找/折半查找
	int mid,start,end;
	start = 1;
	end = ST.length;
	while(start<=end)
	{
		mid = (start+end)/2;
		if(EQ(ST.elem[mid].key,key))
			return mid;
		else if(LT(key,ST.elem[mid].key))
			end = mid-1;
		else
			start = mid+1;
	}
	return 0;
}

void Traverse(SSTable ST,void (*visit)(Elemtype))
{
	Elemtype *p = ST.elem+1;
	for(int i=1;i<=ST.length;i++)
		visit(*(p++));
}
