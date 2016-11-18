#include <stdio.h>
#include <malloc.h>
#define swap(a,b) a=a^b;b=a^b;a=a^b
//冒泡排序法
void maopao(int *a,int len)
{
	for(int i = 0 ; i < len-1; i++)
		for(int j = 0;j < len-i-1;j++)
			if(a[j] > a[j+1])                //前后两者相比 一次次交换位置
			{
				swap(a[j],a[j+1]);
			}
}
//选择排序法
void xuanze(int *a,int len)
{
	for(int i=0;i<len-1;i++)
		for(int j=i+1;j<len;j++)            //一个和所有的比 找出最值
			if(a[i] > a[j])
			{
				swap(a[i],a[j]);
			}
}
//插入排序法
void charu(int *a,int len)
{
	int temp;
	for(int i=1;i<len;i++)
		for(int j=0;j<i;j++)
			if(a[j] > a[i])
			{
				temp = a[i];                        //先一个 然后的数相当于按顺序插入
				for(int k=i;k>j;k--)
					a[k]=a[k-1];
				a[j] = temp;
				break;//这句话可以改成temp=a[i];
			}
}


//快速排序                                 //左右开弓  先找出一个数的位置然后分两边找另外两边数组一个数的位置  递归
int Findpos(int *a,int l,int h)
{
	int temp = a[l];
	while(l < h)
	{
		while(a[h] > temp && l<h)
			h--;
		a[l] = a[h];
		while(a[l] < temp && l<h)
			l++;
		a[h] = a[l];
	}
	a[l] = temp;
	return h;
}
void kuaisu(int *a,int l,int h)
{
	int pos;
	if(l < h)
	{
		pos = Findpos(a,l,h);
		kuaisu(a,l,pos-1);
		kuaisu(a,pos+1,h);
	}
}


//合并两个不等长的数组
int *guibing(int *a,int *b,int len_a,int len_b)                    //假设两个数组是已经排好序的
{
	int len_c = len_a + len_b;
	int *c = (int *)malloc(sizeof(int) * len_c);
	int *pa=a,*pb=b,*pc=c;										//开头
	int *pa_last = a+len_a-1,*pb_last = b+len_b-1;					//结尾
	while(pa <= pa_last  &&  pb <= pb_last)
	{
		if(*pa < *pb) *pc++ = *pa++;
		else		  *pc++ = *pb++;
	}
	while(pa <= pa_last) *pc++ = *pa++;
	while(pb <= pb_last) *pc++ = *pb++;
	return c;
}


int main()
{
	int x[6]={5,2,8,9,6,1};
	//maopao(x,6);
	//xuanze(x,6);
	//charu(x,6);
	kuaisu(x,0,5);
	for(int i=0;i<6;i++)
		printf("%d  ",x[i]);
	/*														//归并检验
	int y[5] = {4,7,11,16,23};
	int z[7] = {5,8,9,15,18,20,21};
	int *c;
	c = guibing(y,z,5,7);
	for(int i=0;i<5+7;i++)
		printf("%d  ",c[i]);
	*/
	putchar('\n');
	return 0;
}