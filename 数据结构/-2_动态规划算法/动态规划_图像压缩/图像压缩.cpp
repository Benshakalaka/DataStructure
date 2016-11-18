#include <stdio.h>
#include <malloc.h>

int length(int *init,int i);
void Compress(int *init,int n,int *s,int *b,int *l);
void Output(int n,int *init,int *l,int *s,int *b);

int main()
{
	int init[7] = {0,10,12,15,255,1,2};
	int *s,*b,*l;								
	s = (int*)malloc(sizeof(int)*(7));		//s[i]是共i个像素总共所需位数
	l = (int*)malloc(sizeof(int)*(7));		//l[i]和第i个像素一起的个数
	b = (int*)malloc(sizeof(int)*(7));		//b[i]是每个像素的位数
	Compress(init,6,s,b,l);
	Output(6,init,l,s,b);
	return 0;
}

int length(int *init,int i)						//计算出该像素点所需要的位数
{
	int b=0,temp=init[i];
	while(temp)
	{
		temp /= 2;					//二进制的方式存储 
		b++;
	}
	return b;
}

void Compress(int *init,int n,int *s,int *b,int *l)
{
	//比如现在有5个，l[5]为2 ，那么这一组有2个，然后再找l[3]的。。。这样就形成了m组 这样就是从上至下的思考
	int lmax = 256,head = 11;
	s[0] = 0;
	for(int i=1;i<=n;i++)						//前i个的最优解
	{
		b[i] = length(init,i);							//将新增的像素所需位数算出来
		int bmax = b[i];					//暂时令所需最大位数等于这个
		l[i] = 1;							//现在和第i个像素在同一组的只有他自己一个
		s[i] = s[i-1]+bmax;					//现在总共所需位数（不算head），暂时等于s[i-1]加上新增像素点的位数
		for(int j=2;j<=i && j<=lmax;j++)				//这里的j指的是和第i个像素在一组的像素点的个数	；这里的lmax是因为题目中有限制 每组最多这么多个像素点
		{
			if(bmax<b[i-j+1])					//在该组的j个像素中找到所需位数最长的一个（这样才能满足整个组）
				bmax = b[i-j+1];
			if(s[i]>s[i-j]+j*bmax)			//s[i-j]是最优的 加上j个像素点 这是新产身的 s[i]是原先比较下较优的 如果还有更优的 则取代 并且用l[i]记录下该组个数  
			{
				s[i] = s[i-j]+j*bmax;
				l[i] = j;
			}
		}
		s[i] += head;				//head的用处是记录每组的像素个数和所需最大位数的
	}
}

void Output(int n,int *init,int *l,int *s,int *b)			//将结果输出
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d%c",init[i],i%n!=0?' ':'\n');
	printf("The greatest result is %d\n",s[n]);
	printf("counts       bits\n");
	int bmax;
	int g=0;
	while(n>=1 && g++<10)
	{
		printf("%d[%d～%d]    ",l[n],n,n-l[n]+1);
		bmax = b[n];
		for(i=1;i<=l[n];i++)
			if(bmax<b[n-i+1])
				bmax = b[n-i];
		n -= l[n];
		printf("   %d\n",bmax);
	}
	
}


//结果里l[5]=2;这是为什么呢？为什么将255和1这两个像素放在一起而不分开呢？因为没分出一组就会多11位用于记录该组的像素个数和所需最大位数，而将像素为1的和255放在一起则使总长度更短（因为只要8位就可以）