#include <stdio.h>							//这是书上158页的6.62题目  哈夫曼编码   （不明白可查什么是哈夫曼编码  什么是编码 什么是译码）
#include <malloc.h>
#include <string.h>
#define swap(a,b) a=a^b;b=a^b;a=a^b

typedef struct
{
	int weight;								//权
	int parent,lchild,rchild;					//函数中要用到双亲节点 和左右子节点
}HTNode,*HuffmanTree;				//动态分配数组存储哈夫曼树

void Select(HuffmanTree HT,int i,int &s1,int &s2);						//在存储哈夫曼树的数组HT[1,...,i]选择parent为0且权weight最小的两个节点，编号为s1,s2
void CreateHuffmanTree(HuffmanTree &HT,int *w,int n);					//创建哈夫曼树
void HuffmanCoding_1(HuffmanTree &HT,char ** &HC,int n);				//w存放n个字符的权值(均>0)，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC
void HuffmanCoding_2(HuffmanTree &HT,char ** &HC,int n);				//法二
int HuffmanTranslate(HuffmanTree &HT,char *in,int *out,int n);			//译码

int main()
{
	HuffmanTree HT;
	//char **HC;
	int n,*w,i;
	printf("The number of weight ?   ");
	scanf("%d",&n);
	w = (int*)malloc(sizeof(int)*(n+1));
	w[0] = 0;
	for(i=1;i<=n;i++)
		scanf("%d",&w[i]);
	CreateHuffmanTree(HT,w,n);
	//得到字符编码
	HuffmanCoding_2(HT,HC,n);
	for(i=1;i<=n;i++)
		printf("%s\n",HC[i]);
	//译码
	/*char in[20];
	int out[20],count;
	printf("Input the Coding : \n");
	scanf("%s",in);										//一串0、1的编码  译成相对应字符对应的位置
	count = HuffmanTranslate(HT,in,out,n);
	for(i=0;i<count;i++)
		printf("%d   ",out[i]);*/
	return 0;
}

void Select(HuffmanTree HT,int i,int &s1,int &s2)			//从HT的[1,..,i]中挑选出最小的两个s1,s2
{
	int j=1;
	while(j<=i)
	{
		if(HT[j].parent==0)
		{
			s1 = j;
			break;
		}
		j++;
	}
	j = s1+1;
	while(j<=i)
	{
		if(HT[j].parent==0)
		{
			s2 = j;
			break;
		}
		j++;
	}
	
	if(HT[s1].weight > HT[s2].weight)			//始终保持HT[s1].weight小于HT[s2].weight的状态
	{
		swap(s1,s2);
	}
	for(j=s2+1;j<=i;j++)
	{
		if(j!=s1 && HT[j].parent==0 && HT[j].weight < HT[s2].weight)			//过程与挑选最小的差不多
		{
			s2 = j;
			if(HT[s1].weight > HT[s2].weight)			//始终保持HT[s1].weight小于HT[s2].weight的状态
			{
				swap(s1,s2);				//这样的确简洁了 但是如果没有这个大括号 会导致整个程序都是错的。。。
			}
		}
	}
}

void CreateHuffmanTree(HuffmanTree &HT,int *w,int n)
{
	if(n<=1)
		return;
	int m = 2*n-1;								//有n个字符  那就说明有m个节点(不明白看书 哈夫曼树是正则而二叉树)
	HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));			//数组中0号位置不用
	int i;
	for(i=0;i<=n;i++,w++)
	{
		HT[i].weight = *w;						//  【  赋权  以用于之后的赫夫曼二叉树构造  】
		HT[i].lchild = HT[i].parent = HT[i].rchild = 0;				//置零
	}
	
	for(;i<=m;i++)
		HT[i].weight = HT[i].lchild = HT[i].parent = HT[i].rchild = 0;
	int s1,s2;									//s1,s2用于接受Select函数数据
	for(i=n+1;i<=m;i++)
	{
		Select(HT,i-1,s1,s2);
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = HT[s2].parent = i;
	}														//直到这里 已经建立好了哈夫曼树  HT[i]就是头结点  算法根据“哈夫曼树的定义.txt”


}

//①
//方法一 是从叶子节点到根节点  记录从叶子到根节点之间的历程（0或者1）  继而反向记录编码
void HuffmanCoding_1(HuffmanTree &HT,char ** &HC,int n)
{
	int m=2*n-1;
	//从这里开始给每个字符赋编码
	HC = (char **)malloc((n+1) * sizeof(char));			//n个字符 n个字符串
	char *temp;
	temp = (char *)malloc(n * sizeof(char));		//既然是哈夫曼树  那一个字符的编码（0，1之类）长度不会超过n 用temp来临时代替H[i]  因为一个字符编码长度仍是未知
	temp[n-1] = '\0';			//所有编码的长度中最大的长度是可寻的
	int i,c,f,start;
	for(i=1;i<=n;i++)
	{
		c = i;
		start = n-1;						//这函数是从叶子节点循着parent一直往上找到根节点  编码字符串的字符出现顺序也是从后往前
		for(f = HT[i].parent;f;f = HT[f].parent)
		{
			if(HT[f].lchild == c)					//该叶子在左边就为0 不然为1
				temp[--start] = '0';
			else
				temp[--start] = '1';
			c = f;
		}
		HC[i] = (char *)malloc((n-start) * sizeof(char));		//现在用temp来存储了编码  在HC中存储时就可以准确知道长度 
		strcpy(HC[i],&temp[start]);
	}
	//free(temp);
}


//②
//方法二 是从根节点向下寻找叶子节点  并记录从根节点到某一叶子节点的历程（0或者1） 继而顺序记录编码
void HuffmanCoding_2(HuffmanTree &HT,char ** &HC,int n)
{
	//从这里开始给每个字符赋编码
	int i,m=2*n-1;
	HC = (char **)malloc((n+1) * sizeof(char));			//n个字符 n个字符串
	for(i=1;i<=m;i++)
		HT[i].weight = 0;					//weight在之前建树的时候有用 但是在找编码的时候是用不到的 不如用其来当作标记 0、1、2  0表示未曾遍历过是需要向左（默认先向左）继续探索的 1表示已经经历过其左子树 但右子树未曾经历  2表示左右都经历过  需要往上parent返回一层
	int p=m,start=0;
	char *temp;
	temp = (char *)malloc(n * sizeof(char));
	while(p)			//判断条件是p值，p是某节点的parent值，若等于0，则表明此时根节点已被完全访问
	{
		if(HT[p].weight==0)								//0表示未曾遍历过是需要向左（默认先向左）继续探索的
		{
			HT[p].weight = 1;		//表明已经经历过 但右子树未知
			if(HT[p].lchild)										//有左子树 那说明并不是叶子节点
			{
				p = HT[p].lchild;							//继续向左
				temp[start++] = '0';						//并且记录
			}
			//这里是用else if   一般有左子树（在哈夫曼树中） 就该有右子树  所以省去一个判定
			else if(!HT[p].rchild)					//没有左子树的前提下 没有右子树 表示找到叶子节点
			{
				temp[start] = '\0';			//直接等于 '\0'是因为前面是 temp[start++]='';先赋值后后加一
				HC[p] =(char*)malloc((start+1)*sizeof(char));
				strcpy(HC[p],temp);
			}
		}
		else if(HT[p].weight==1)						//1表示已经经历过其左子树 但右子树未曾经历
		{
			HT[p].weight=2;
			if(HT[p].rchild)				//访问右子树
			{
				p = HT[p].rchild;
				temp[start++] = '1';		//记录
			}
		}
		else										// 2表示左右都经历过  需要往上parent返回一层
		{
			HT[p].weight=0;				//复习的时候一下子看不懂了。这个此时好像并没有什么意义，估计是便于下一次访问或是别的函数访问，不至于节点的weight被无缘无故占用	
			p = HT[p].parent;
			start--;				//去掉最后一个记录是因为整个循环是调用的一个temp数组，一个start游标，减一是将temp最后一个字符去掉(因为退回了parent节点 比如原来A节点为parent，向左后数组+'0',正好为叶子节点，将此数组赋予一个字母后，要返回，就要将加上的'0'去掉，毕竟之后的编码不是走这条路)
		}
	}
}

int HuffmanTranslate(HuffmanTree &HT,char *in,int *out,int n)
{//译码相对简单些  0向左 1向右  直到叶子节点 之后返回根节点
	char *temp = in;
	int m=2*n-1,start=0;
	while(*temp)
	{
		if(*temp == '0')
			m = HT[m].lchild;
		else
			m = HT[m].rchild;
		if(HT[m].lchild==0 && HT[m].rchild==0)
		{
			out[start++] = m;
			m = 2*n-1;
		}
		temp++;
	}
	return start;
}