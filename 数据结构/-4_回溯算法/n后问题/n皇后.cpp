#include <iostream>
#include <cmath>
using namespace std;

class nQueen
{
public:
	nQueen(int);
	bool Place(int);
	void BackTrack(int);
	void BackTrack_2();
	void show();
private:
	int n;					//n个皇后 以及n*n的图
	int *r;					//路径 r[i] 表示第i个皇后在第i列的第r[i]个位置					
	int sum;				//可行方案数
};

nQueen::nQueen(int m):n(m)
{
	r = new int[n+1];
	for(int i=0;i<=n;i++)
		r[i] = 0;
	sum = 0;
}

bool nQueen::Place(int k)					//看皇后是否可以放在现在的位置上 是否与之前的皇后有冲突（行、列、斜线）
{
	for(int i=1;i<k;i++)
		if(abs(i-k)==abs(r[i]-r[k]) || r[i]==r[k])	//看txt
			return false;
	return true;
}

void nQueen::BackTrack(int k)			//回溯
{
	if(k>n)
		sum++;
	else
	{
		for(int i=1;i<=n;i++)
		{
			r[k] = i;
			if(Place(k))		//该位置可以放置 则继续回溯
				BackTrack(k+1);
		}
	}
}

void nQueen::BackTrack_2()
{
	for(int i=0;i<=n;i++)
		r[i] = 0;
	sum = 0;
	int k=1;
	int g=1;
	while(k>0)						//这里注意		为什么判断条件是大于0呢？ 先想一下整个程序什么时候应该停下？呃 应该在第一行走到最后的时候或者说第一行的点走完想继续往后退成0的时候
	{
		r[k]++;			//这一步是在循环走完后才觉得要加上的
		while(r[k]<=n && !Place(k))			//为第i个点寻找位置	直到找到可以安放的位置【与前几个满足限制条件】
			r[k]++;
		if(r[k]<=n)					//循环结束了 且是因为找到才结束的
		{
			if(k==n)			//如果已经到最后一个点了 说明整条路是通的  那么这条路完了且计数完毕呢？ 就继续找这个点可能位置 找不到就往后退 跟着程序走一边就行
				sum++;
			else			//否则继续下一个点
			{
				k++;
				r[k]=0;				//这里注意	必须加这一句话 虽然在初始化里已经有了 但是两者意义不同 这里是指每一次进入新的就置零 从头开始寻找
			}
		}
		else
			k--;					//如果循环是因为没找到就结束的 那么往后退一个点另寻出路
	}
}

void nQueen::show()
{
	cout << sum <<endl;
}

int main()
{
	nQueen Q(8);
	//Q.BackTrack(1);
	Q.BackTrack_2();
	Q.show();
	return 0;
}