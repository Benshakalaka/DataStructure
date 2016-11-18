//构造一棵二叉树	本来以为是跟哈夫曼树是差不多的 但是并不是。。。这里面的数学原理是最主要的 辅以递归实现
//这种建树的方式很容易看出一点就是 根节点大于其左子树上左右节点 和 小于右子树上所有节点  这样查找所要比较的次数就是depth
//其实是折半查找的改进
void SecondOptimal(BiTree &T,Elemtype *r,float *sw,int low,int high)
{
	int i=low,j;
	int min = abs(sw[high] - sw[low]);
	int dw = sw[high] + sw[low-1];					//dw min 根据数学原理而来
	for(j=low+1;j<=high;j++)						//找到最小的 就是根
		if(min > abs(dw-sw[j] - sw[j-1]))
		{
			min = abs(dw-sw[j] - sw[j-1]);
			i = j;
		}
	T = (BiTree)malloc(sizeof(BiTNode));
	T->x = r[i];
		//分为两半，3部分	(low,...i-1),(i),(i+1,...high)  
	if(i==low)								//先是左半边(low,low+1,low+2,..,i-1)	如果i==low 说明此时左子树为空										
		T->LN = NULL;
	else
		SecondOptimal(T->NL,r,sw,low,i-1);	//否则递归
	if(i==high)								//再试右半边
		T->RN = NULL;
	else
		SecondOptimal(T->RN,r,sw,i+1,high):
}

void InitSW(SSTable ST,float *sw)
{
	sw[0] = 0;
	for(int i=1;i<=ST.length;i++)
		sw[i] = sw[i-1]+ST.elem[i-1].weight;
}