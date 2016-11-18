#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int ord(char c)									//取到所需下标 实验用为数字 所以是 c-'0',字母的话该是 c-'A'
{
	return c-'0';
}
void Distribute(SLCell *r,int i,Arrtype &f,Arrtype &e)	
//静态链表L的r域中记录已按(keys[0],...,keys[i-1])有序。
//本算法按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
//f[0...RADIX-1]和e[0...RADIX-1]分别指向各子表中第一个和最后一个记录
{
	int j;
	for(j=0;j<RADIX;j++)								//先初始化这个数组 因为要用好几次 e不一定要初始化 因为这里都是 e[] = ?; 而没有 ？= e[];
	{
		f[j] = 0;
		e[j] = 0;
	}
	int temp;
	for(int p=r[0].next;p;p=r[p].next)					//遍历静态链表中的每一个节点  可看图更容易理解
	{
		temp = ord(r[p].keys[i]);
		if(!f[temp])										//如果是第一个则放在f[]中  可看图理解
			f[temp] = p;
		else
			r[e[temp]].next = p;							//否则接在后面
		e[temp] = p;
	}
	
}
void Collect(SLCell* r,int i,Arrtype f,Arrtype e)
//本算法按照keys[i]自小至大将f[0...RADIX-1]所指各子表依次连接成一个链表
//e[0...RADIX-1]为各子表的尾指针
{
	int j,temp;
	int p = 0;
	for(j=0;j<RADIX;j++)
		if(f[j])
		{
			r[p].next = f[j];
			p = e[j];										//这里直接利用了e[] 因为之前在Distribute函数中已经将字符相同的按顺序连起来了 这里只需要将头和尾接上就行了 而不是一个个的再接一遍
			r[p].next = 0;						//这一步是必须的 因为不知道什么时候结束 所以必须在最后添一个尾的标志 就跟链表创建的时候一样
		}
}

void RadixSort(SLList &L)
//L是采用静态链表表示的顺序表
//对L做基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点
{
	int i;
	for(i=0;i<L.recnum;i++)						//这里必须要初始化一下 因为是链表（虽然是静态的） 给点面子。。。才好以链表的形式一个个访问（虽然暂时还不是跳来跳去的访问 -，-）
		L.r[i].next = i+1;
	L.r[i].next = 0;	//结束标志
	Arrtype f,e;
	i=L.keynum-1;
	for(;i>=0;i--)
	{
		Distribute(L.r,i,f,e);			//将每个字符排序
		Collect(L.r,i,f,e);				//整理出来				可看图理解
	}
}