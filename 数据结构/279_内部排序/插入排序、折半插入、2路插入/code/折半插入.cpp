#include <stdio.h>			
#include <malloc.h>

//插入排序法						//时间复杂度为O(n^2)
void Insert(int *a,int len)
{
	int i,temp;
	for(i=1;i<len;i++)
		if(a[i]<a[i-1])
		{
			temp = a[i];
			for(int j=i-1;temp < a[j];j--)
				a[j+1] = a[j];
			a[j+1] = temp;
		}
}

//折半插入排序										//时间复杂度为O(n^2)
void zhe_cha(int *a,int len)
{
	int start,end,mid;
	int temp;
	//下面是书上的
	//大致思路就是 在查找部分使用折半查找插入位置
	for(int i=1;i<len;i++)
	{
		temp = a[i];
		start = 0;end = i-1;
		while(start<=end)					//折半是将整个数组分成了三部分  数组 = 数组+mid+数组
		{									//整个过程在于寻找插入的前面的位置 
			mid = (start+end)/2;
			if(temp < a[mid])			//如果temp插入位置在前面数组
				end = mid-1;
			else
				start = mid+1;
		}
		for(int j=i-1;j>=end+1;j--)			//最终mid+1 将是要插入的位置
			a[j+1] = a[j];
		a[end+1] = temp;
	}
}
//下面我把折半查找贴出来 两者相比较一下
/*int Search_Bin(SSTable &ST,Keytype key)									//算法9.2	在顺序表中查找其关键字等于等于key的数据元素，若找到 则函数值为表中位置 否则为0
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
}*/


//2-路插入排序	减少了移动元素的次数	
//这里的first表示顺序表的第一个元素(最小值),final表示最后一个元素(最大值).因为其索引打乱了，即以第1个元素为准(枢纽),分成2路(左右两边,理解为2个有序的数组)进行插入排序 减少了移动元素的次数
void Path_2(int *a,int len)
//首先理清思路 根据提出的算法 可以将此程序分为大致两部分
//①： 大于final的 或者小于first的 直接插入并改变final或first即可
//②: d[first] < temp <d[final]的 可以再分为两组
//		Ⅰ: d[0] < temp <d[final]的 插入前面一组
//		Ⅱ: d[first] <temp <d[0]的 插入后一组
{
	int *d = (int*)malloc(sizeof(int)*len);
	int final,first,temp;
	d[0] = a[0];
	final = first = 0; 
	for(int i=1;i<len;i++)
	{
		temp = a[i];
		if(temp>d[final])										//①： 大于final的 或者小于first的 直接插入并改变final或first即可
			d[++final] = temp;
		else if(temp<d[first])
		{
			first = (first-1+len)%len;	//这里因为first一开始为0 而后为len-1 ,len-2,可以将0理解为len-0 ,结合实际最后还要求余
			d[first] = temp;
		}
		else if(final>0 && temp>=d[0] && temp<d[final])					//②: d[first] < temp <d[final]的 可以再分为两组
		{												//Ⅰ: d[0] < temp <d[final]的 插入前面一组
			int end = final;
			while(temp < d[end])			//这里将大于temp的数都往后移
			{
				d[end+1]=d[end];
				end--;
			}
			d[end+1] = temp;
			final++;							//必须改动final
		}
		else if(first>0 && temp<=d[0] && temp>d[first])	//Ⅱ: d[first] <temp <d[0]的 插入后一组
		{
			int start = first;
			while(temp>d[start])				//这里将小于temp的数都往前移
			{
				d[start-1] = d[start];
				start++;
			}
			d[start-1] = temp;
			first--;
		}
	}

	for(i=0;i<8;i++)
		printf("%d  ",d[i]);
	putchar('\n');

	for(i=0;i<len;i++)
		a[i] = d[(i+first)%len];
}



int main()
{
	//int x[6]={5,2,9,8,6,1};
	int x[8]={49,38,65,97,76,13,27,49};
	//int y[10]={43,22,54,88,22,24,17,99,55,220};
	//Path_2(x,8);
	//charu(x,8);
	Insert(x,8);
	for(int i=0;i<8;i++)
		printf("%d  ",x[i]);
	putchar('\n');
	return 0;
}


