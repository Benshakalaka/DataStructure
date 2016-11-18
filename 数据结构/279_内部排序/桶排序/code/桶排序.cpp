#include <stdio.h>
#include <malloc.h>		//这里每个桶用链表实现

#define BucketNum 10		//分为10个桶

typedef struct Node				//链表存储的节点
{
	double key;
	struct Node *next;
}Node,*pNode;

typedef struct					//每个桶的名字【类别】		暂时用数组下标做标记
{
	//double kind;
	pNode first;
}Bucket;

void ShowBucket(Bucket *bucket)						//将链表输出来看看
{
	pNode p = 0;
	for(int i=0;i<BucketNum;i++)
	{
		p = bucket[i].first;
		printf("---%d--- : ",i);
		while(p)
		{
			printf("%lf ",p->key);
			p = p->next;
		}
		puts("");
	}
}

void InsertBucket(Bucket *aim,double val)			//一个链表插入的过程
{
	pNode one = (pNode)malloc(sizeof(Node));
	one->key = val;
	one->next = 0;
	if(!aim->first)
		aim->first = one;
	else
	{
		pNode p = aim->first,q = 0;
		while(val>p->key)
		{
			q = p;
			p = p->next;
		}
		if(!q)
		{
			one->next = aim->first;
			aim->first = one;
		}
		else
		{
			one->next = p;
			q->next = one;
		}
	}
}
void BucketSort(double *a,int len)					//桶排序
{
	Bucket *bucket = (Bucket*)malloc(sizeof(Bucket)*BucketNum);			//辅助用数组
	int i;	
	for(i=0;i<BucketNum;i++)
		bucket[i].first = 0;
	for(i=1;i<=len;i++)							//以插入排序进行
		InsertBucket(bucket+int(a[i]*10),a[i]);

	pNode p = 0;
	int j=1;
	for(i=0;i<BucketNum;i++)							//将每一个数按顺序放进数组
	{
		p = bucket[i].first;
		while(p)
		{
			a[j++] = p->key;
			p = p->next;
		}
	}ShowBucket(bucket);
}

int main()
{
	double a[11] = {0,0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
	BucketSort(a,10);
	for(int i=1;i<=10;i++)
		printf("%lf ",a[i]);
	puts("");
	return 0;
}