#include <stdio.h>

int k=5;											//声明是5-路归并的败者树

typedef int LoserTree[k];							//败者树是完全二叉树且不含叶子，可采用顺序存储

typedef struct
{
	Keytype key;
}ExNode,External[k+1];								//外节点 只存待放归并记录的关键字

void K_Merge(LoserTree &Ls,External &b)
//利用败者树Is将编号从0到k-1的k个输入归并段中的记录归并到输出归并段
//b[0]至b[k-1]为败者树上的k个叶子节点，分别存放k个输入归并段中当前记录的关键字
{
	int i;
	for(i=0;i<k;i++)							//得到b数组初识值
		Input(b[i].key);
	CreateLoserTree(Ls);						//建立败者树
	while(b[Ls[0]].key!=MAX)					//这个判断条件是建立在一个前提条件下的：5-路归并，那分成的几组中的最后一个元素设置为MAX 方便最后判断是否结束
	{
		q = Ls[0];
		Output(q);			//输出最小
		Input(b[q]);		//最小的数换成下一个数
		Adjust(Ls,q);		//调整成新的败者树
	}
	Output(Ls[0]);
}

void Adjust(LoserTree &Ls,int s)
//沿从叶子节点b[s]到根节点Ls[0]的路径调整败者树
{
	int t = (s+k)/2;						//这句话很重要  没开始写函数的时候不知道将哪组外节点放在哪个树中的节点下面  看到这句话瞬间就明白了  节点下标和外节点组下标肯定是存在着某种函数关系的
	int temp;
	while(t)											//因为0号节点是不在这棵完全二叉树里的 所以到0的时候就可以结束
	{
		if(b[s].key > b[Ls[t]].key)			//举个例子 两个叶子 6 和 10，双亲存的是10 用6来和上一层进行比较直到最后。之后发现6是最小的将6取出换为15 此时要将双亲中存的10换为15 且要用来和上层比较的是10  所以这里是Swap
		{
			temp = s;
			s = Ls[t];
			Ls[t] = temp;
		}
		t /= 2;						//除以2的意思是向上一层  因为是完全二叉树
	}
	Ls[0] = s;											//但是0号是用来存最小的
}

void CreateLoserTree(LoserTree &Ls)
//已知b[0]到b[k-1]为完全二叉树Is的叶子节点存在k个关键字，沿从叶子到根的k条路径将Is调整成败者树
{
	int i;
	for(i=0;i<k;i++)								//为每个节点初始化一下  不然不好Adjust （这时候随便放(0,...,k-1)中的数
		Ls[i] = i;
	for(i=k-1;i>=0;i--)								//从下到上进行调整 对一定要自下至上 颠倒会导致一些遗漏
		Adjust(Ls,i);
}

int main()
{
	return 0;
}