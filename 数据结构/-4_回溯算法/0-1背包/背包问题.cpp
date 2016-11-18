#include <iostream>
using namespace std;

class Knap
{
public:
	struct Thing
	{
		int w;
		int p;
		double value;
	};
	Knap(int,int,Thing*);
	int Bound(int i);
	void BackTrade(int i);
	void Arrange();
	void show();
private:
	int c;						//最大重量
	int bestp;					//当前最大价值
	int cw;						//当前重量
	int cp;						//当前价值
	int n;						//可选个数
	Thing *ct;						//提供的选择
	int best_solution[20];				//最优选择方案
	int c_solution[20];					//当前选择方案
};

Knap::Knap(int cc,int cn,Thing *temp):c(cc),n(cn),ct(temp)		//构造函数初始化
{
	bestp = 0;
	cw = 0;
	cp = 0;
	int i;
	for(i=1;i<=n;i++)				//需先置零 0为未选	1为已选
	{
		best_solution[i] = 0;
		c_solution[i] = 0;
		ct[i].value = double(ct[i].p)/double(ct[i].w);			//这里妈的好像一定要这样诶。。。不然都不是小数
	}
	
}

void Knap::Arrange()						//令所有物品按照价值从大到小排好序**********这是必须的
{
	Thing temp;
	for(int i=1;i<=n-1;i++)					//用了选择排序
		for(int j=i+1;j<=n;j++)
			if(ct[i].value<ct[j].value)
			{
				temp = ct[i];
				ct[i] = ct[j];
				ct[j] = temp;
			}
}

int Knap::Bound(int i)					//上界
//什么是上界呢？	就是说假设我在做了几个选择之后（或还未开始），先通过贪心算法的背包问题得出最优解(按价值单位)【结果是得不到的但可以用作上界】	那Bound函数拿来干嘛？ 用来剪枝  将不需要考虑的右枝剪去	
{
	int cleft = c-cw;
	int pmax = cp;
	while(i<=n && cleft>=ct[i].w)			//这一步步到此函数最后是用来按贪心算法求最优	这就需要将物品按价值排序 不然出错 所以上面的Arrange函数必不可少了
	{
		cleft -= ct[i].w;
		pmax += ct[i].p;
		i++;
	}
	if(i<=n)
		pmax += cleft/ct[i].w*ct[i].p;
	return pmax;
}

void Knap::BackTrade(int i)				//回溯求解
{
	if(i>n)												//表示已经访问到最后一个物品	不会再继续访问下去了
	{
		if(bestp < cp)			//如果当前价值大于当前最优 就替换
		{
			for(int i=1;i<=n;i++)
				best_solution[i] = c_solution[i];
			bestp = cp;
		}
		return;
	}
	if(cw+ct[i].w<=c)				//往左边走（含义是将这个物品纳入背包）	不需要考虑Bound来剪枝是因为往左走的话最优解就是双亲节点的最优解
	{
		c_solution[i] = 1;
		cw += ct[i].w;
		cp += ct[i].p;
		BackTrade(i+1);
		cw -= ct[i].w;	//这两步体现了些些回溯
		cp -= ct[i].p;
	}
	if(Bound(i+1)>bestp)				//往右边走（不纳入背包）	考虑Bound是因为如果往右边走所能得到的最优解如果还是小于当前最优解的话就没必要去考虑了 就是所谓的剪枝
		BackTrade(i+1);
}

void Knap::show()
{
	cout << bestp <<endl;
	cout << "slution : \n";
	for(int i=1;i<=n;i++)
		cout << best_solution[i] << "  ";
	puts("");
	for(int j=1;j<=n;j++)
		cout << ct[j].p << " "; 
	puts("");
}

int main()
{
	/*int a[] = {0,79,58,86,11,28,62,15,68};
	int b[] = {0,83,14,54,79,72,52,48,62};
	int n = 8;
	int w = 200;*/
	/*int a[] = {0,77,22,29,50,99};
	int b[] = {0,92,22,87,46,90};
	int n = 5;
	int w = 100;*/
	int a[] = {0,95,75,23,73,50,22,6,57,89,98};
	int b[] = {0,89,59,19,43,100,72,44,16,7,64};
	int n = 10;
	int w = 300;
	Knap::Thing ct[20];

	for(int i=1;i<=n;i++)
	{
		ct[i].w = a[i];
		ct[i].p = b[i];
	}
	Knap p(w,n,ct);
	p.Arrange();
	p.BackTrade(1);
	p.show();
	return 0;
}