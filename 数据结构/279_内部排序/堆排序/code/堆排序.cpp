#include <stdio.h>

typedef int Keytype;							//关键字类型

#define N 100

typedef struct
{
	Keytype key;
}Elemtype;									//元素类型

typedef struct									//用于操作的辅助空间
{
	Elemtype r[N];
	int length;
}SqList;

typedef SqList Heaptype;

void Print(Elemtype e)
{
	printf("%d ",e.key);
}
void HeapAdjust(Heaptype &H,int s,int n)
//已知H.r[s,...,n]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数调整H.r[s]
//的关键字，使H.r[s,...,n]成为一个大顶堆		注意：是大顶堆 就是根最大的那种
{
	int i;
	H.r[0] = H.r[s];									//用0号来存一下
	for(i=2*s;i<=n;i*=2)								//看懂循环了吗？ 循环方式就表明是处理一棵树  搞成大顶堆
	{
		if(i<n && H.r[i].key<H.r[i+1].key)				//i<m也很重要 毕竟有个i+1需要考虑呢    左右孩子哪个大下标就赋给i 注意为什么是赋大的是因为是大顶堆！
			i++;
		if(H.r[0].key >= H.r[i].key)					//如果根大于两个孩子里最大的，说明已经按照大顶堆方式放好了
			break;
		H.r[s] = H.r[i];		//根的值换成大孩子的（因为根比大孩子小）
		s = i;					//现在要处理i为根的树 看看把原来的根换到孩子位置上有没有影响大顶堆的摆放方式
	}
	H.r[s] = H.r[0];			//原先我写的不是s而是i 可是上面是先判断break之后才赋值的 所以s和i的值不同 必须是s s才是换的空着的地方
}

void Swap(Elemtype &a,Elemtype &b)
{
	Elemtype temp = a;
	a = b;
	b = temp;
}
void HeapSort(Heaptype &H)				
//对进行堆排序
//要实现堆排序需要有两步:
//	① 如何由一个无序序列建成一个堆
//	② 如何在输出堆顶元素后调整剩余元素成为一个新的堆
{
	int i;
	for(i=H.length/2;i>=1;i--)						//第一部分
													//要干嘛？								见步骤①
		HeapAdjust(H,i,H.length);					//① 为什么是从H.elngth/2 开始并递减？	因为这是树的非终端节点（按数组存储就是数组前面一半）；那为什么是总中间到开头而不是从开头到中间？ 如果是颠倒过来就错了 会引发隔了一层的数无法参与比较 自下向上的比较则使整个过程完整 不懂看图“57行顺序问题”
													//② 为什么是i到H.length？				因为假设在数组中根节点下标为i,左右孩子则为（完全二叉树）2*i 和  2*i+1这两个 主要将这棵树调整为大顶堆 跟其余的没什么关系

	for(i=H.length;i>1;i--)							//第二部分
													//要干嘛？
	{												//既然已经建成大顶堆了，那么顶上的就是最大的 
		Swap(H.r[1],H.r[i]);						//① 顶上最大 按排序方式那么放到最后一个去
		HeapAdjust(H,1,i-1);						//② 既然交换了位置，那么肯定就不是大顶堆了 需要再处理 不过一个已经安放好 长度减少了
	}
}
#define n 10

int main()
{
	Elemtype r[n] = {{49},{99},{65},{97},{76},{13},{27},{49},{55},{04}};
	Heaptype H;
	H.length = n;
	int i;
	for(i=1;i<=n;i++)
		H.r[i] = r[i-1];
	HeapSort(H);
	for(i=1;i<=n;i++)
		printf("%d ",H.r[i].key);
	puts("");
	return 0;
}