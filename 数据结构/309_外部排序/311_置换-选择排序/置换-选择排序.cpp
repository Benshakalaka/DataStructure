								//本程序首先选出最小的一个数，然后在这个数之上挑选最小 
#include <stdio.h>

typedef struct
{
	Rcdtype rec;
	Keytype key;
	int		rnum;
}RcdNode,workarea[w];

int rc,rmax;

void Replace_Selection(LoserTree &ls,Workarea &wa,int q,FILE *fi,FILE *fo)
//在败者树ls和内存工作区wa上用置换-选择排序求初识归并段，fi为输入文件
//（只读文件）指针，fo为输出文件（只写文件）指针，两个文件均已打开
{
	Construct_Loser(ls,wa);
	rc = 1;								//当前归并段	
	rmax = 1;							//最大归并段
	while(rc<=rmax)
	{
		get_run(ls,wa);
		fwrite();
		rc = wa[ls[0]].rnum;
	}
}

void get_run(LoserTree &ls,Workarea &wa)
//求得一个初始归并段，fi为输入文件指针，f0为输出文件指针
{
	int q;
	int minimax;
	while(wa[ls[0]].rnum==rc)								//要符合在这一段求最小的要求
	{
		q = ls[0];								//将这个要输出去 并 输入新数 的workarea下标记住
		minimax = wa[q].key;					//将最小记住 用于以后在这个基础之上进行挑选
		fwrite(...........);	//输出
		if(feof(fi))						//如果没有数字可以写入了	那么将这个位置的数改成最大 以阻止其参与比较
		{
			wa[q].key = Max;
			wa[q].rnum rmax+1;
		}
		else								//否则写入新数
		{
			fread(&wa[q].key.......);
			if(wa[q].key > minimax)					//写入的新数是否大于之前的最小值呢	大于则将其序号标称正在进行的序号
				wa[q].rnum = rc;
			else									//否则将其序号标为下一段比较的序号
				rmax = wa[q].rnum = rc+1;
		}
		Select_MiniMax(ls,wa,q);					//一旦输出了一个数【或者说加入新的数】就需要重新从这个点调整整颗败者树
	}
}

void Select_MiniMax(LoserTree &ls,Workarea wa,int q)
//从wa[q]起到败者树的根比较选择MiniMax记录，并由q指示它所在的归并段
{
	int temp;
	while(q)
	{
		temp = (w+q)/2;			//temp代表上一层
		if(wa[q].rnum>wa[p].rnum || wa[q].rnum==wa[ls[temp]].rnum && wa[q].key > wa[ls[temp]].key)		//这里为什么满足序号大于条件就能进行交换了呢？ 因为选取某个最小后，之后就是选取大于这个最小的 之后有小于这个最小的数出现的话就分到第二段去 之后第三段、第四段所以总归是一段一段来的
		{
			int p = ls[temp];
			ls[temp] = q;
			q = p;
		}
	}
	ls[0] = q;
}

void Construct_Loser(LoserTree &ls,Workarea &wa)
//输入w个记录到内存工作区wa，建的败者树ls，选出关键字最小的记录并由s指示
//其在wa中的位置
{
	int i;
	for(i=0;i<w;i++)
		wa[i].rnum = wa[i].key = ls[i] = 0;
	for(i=w-1;i>=0;i--)
	{
		fread(wa[i].key............);
		wa[i].rnum = 1;
		Select_MiniMax(ls,wa,i);				//自底向上的调整
	}
}

int main()
{
	return 0;
}