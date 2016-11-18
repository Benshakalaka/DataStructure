//边界标识法
#include <stdio.h>					//双重循环链表结构

typedef struct WORD
{
	union						//之前用过一次在结构体中使用union 是在二叉树的线索遍历那会儿  
	{							//这里为什么使用union呢？ 因为结构体既表示一个空闲块的head 也表示其foot部分  head中使用llink 指向前一个空闲块  foot中使用uplink 指向本空闲块的首地址
		struct WORD *llink;
		struct WORD *uplink;
	};//head 和 foot分别指向空闲块的第一个字和最后一个字
	int tag;			//标志  0为空闲块 1为占用块
	int size;			//空闲块大小
	struct WORD *rlink;			//下一个空闲块
	//Othertype other;										//字的其他部分
}WORD,head,foot, *Space;

#define FootLoc(p) p+p->size-1					//一块空闲块需要head和foot来指定
int e = 3;			//约定 


int main()
{
	return 0;
}


//分配
//为了使系统更有效运行  作出如下两条约定
//假设采取首次拟合法  (选取适当常量e)
//① 用户需大小为n 已找到容量为m的空闲块后(m>=n) 当m-n<=e时  就将整个容量为m的空闲块赋给用户； 否则只分配其中n个字的内存块。同时 为了避免修改指针 约定将该节点中的高地址部分分给用户
//② 每次分配之后，令指针指向刚进行过分配的节点的后继节点
Space AllocBoundTag(Space &pav,int n)
//根据上面的约定实现算法  n为用户所需  pav为头结点（并不需要在意头结点的称谓 因为这种双向循环处处都是头结点）
{
	Space temp = pav;			//指向一个空闲块的开头 首字  所以下面没有head 但是有foot
	while(temp && temp->size < n && temp->rlink!=pav)				//这里需要注意了 主要判断依据是找到大于等于n的空闲块 但是既然是循环队列就要考虑① 该节点是否存在 ②该节点在等于出发点就表明未找到所需的点
		temp = temp->rlink;
	//for(;temp && temp->size<n && temp->rlink!=pav;temp=temp->rlink);//可换成这样更简洁方便

	if(!temp || temp->size<n)//******本来觉得也可以换成if(!temp || temp->rlink==pav) 但是这样是不正确的 因为本身是双向循环链表 如果① 链表中正好只有一个节点 且大于等于n  那这个节点的rlink是指向自己的 ② 最后一个节点的rlink也指向pav。  while循环断在第二个判断，如果使用了temp->rlink==pav 那整个程序就结束了 并没有将这
		return NULL;			//个满足的点给出去  但是换成temp->size<n后说明的确是整个过程没有找到  并且while循环断在第三个判断*******very significant
	
	Space foo;
	foo = FootLoc(temp);
	pav = temp->rlink;
	if( temp->size-n <= e )		//将整个m大小都给出去 类似双向循环链表的节点删除  e为约定内容 做全局变量
	{
		foo->tag = 1;
		temp->tag = 1;		//修改分配节点的标志
		if(temp==pav)				//本来是写成这样的 temp->rlink==pav; 这样是错的如果是最后一个节点呢 错在对双向循环链表的考虑不细致
			pav = NULL;
		else
		{
			pav->llink = temp->llink;				//居然忘了考虑llink了
			temp->llink->rlink = temp->rlink;
		}
	}
	else						//将m中的n大小部分给出去 修改一些参数就可以
	{
		foo->tag = 1;			//将空闲块的后半部分割出去 foot的标志改为1
		temp->size -= n;			//剩余空闲块大小更新
		foo = FootLoc(temp);	//找到剩余空闲块的新foot 并进行更新
		foo->tag = 0;
		foo->uplink = temp;
		temp = foo+1;			//修改分配空间的参数
		temp->tag = 1;
		temp->size = n;
	}
	return temp;
}



//回收
//若释放块的左右均为占用块，则直接将此新的空闲块插入；
//若左邻是空闲块 则与左邻一起插入；
//右邻同理；
//左右都为空闲块 则需要一起插入。
void Reclaim(Space pav,Space fre)
{
	if(!pav)													//如果空闲块中是空的  也就没有左邻右邻之说  相当于直接插入一个空的循环双向链表
	{
		pav = fre->llink = fre->rlink = fre;	//都指向自己
		fre->tag = (fre+fre->size-1)->tag = 0;	//改变标志
		(fre+fre->size-1)->uplink = fre;		//整个完整的空闲块的一个属性
		return;
	}

	Space prev,next,foot;	//便于判断操作
	prev = (fre-1)->uplink;	//指向左邻的head
	next = fre+fre->size;	//右邻的head

	int temp_1;
	Space temp_A,temp_B;
	//链表本身非空
	if(prev->tag && next->tag)									//如果左邻、右邻恰好都为空
	//很好理解，相当于拿到一个空闲块的地址 要插入空闲双向循环链表。（插在pav的前面  并将pav指向这个点 下次就第一个访问这个空闲块）
	{
		//属性修改
		foot = FootLoc(fre);
		fre->tag = foot->tag = 0;
		foot->uplink = fre;
		//指针操作
		fre->rlink = pav;
		fre->llink = pav->llink;
		pav->llink->rlink = fre;
		pav->llink = fre;
		pav = fre;
	}
	else if(!(prev->tag) && next->tag)							//如果左邻为空闲右邻为占用
	//一开始挺迷惑的，难道不是左边正好也有一块空闲然后正好两个一起被回收到空闲链表里去吗？？？ 确实不是！！！ -。-！ 
	//好吧  为什么不是呢？ 因为这里指的左邻右邻都是指物理内存(物理内存当然是可以靠+1,+size来确定下一块内存的)  然而我要将这个空闲块存进链表去 地址不是靠加加减减就能来的
	//这里判断左邻右邻是否正好为空闲是指： 左邻右邻是否正好是空闲链表中的一员 如果是就直接将这块空闲内存加进左邻右邻里面去 就不需要链表上多一个节点
	
	//这里是左邻为空闲 左邻在这个空闲节点的上面 所以相当于直接将这个空闲节点从根部加到左邻中去 并不导致什么指针的变化
	{
		//都是属性的变化
		temp_1 = fre->size;
		temp_A = (fre-1)->uplink;
		temp_A->size += temp_1;				//内存大小变化
		foot = FootLoc(fre);
		foot->uplink = temp_A;				//根部的foot所存的uplink需要变化
		foot->tag = 0;
	}
	else if(prev->tag && !(next->tag))							//如果左邻为占用右邻为空闲
	{
		//这里是右邻为空闲  右邻在这个空闲块的下面  相当于将右邻从空闲块的根部加进去(右邻的头被屁股盖住了。。) 但是右邻是链表中的一个节点啊(右邻head中存着两边的link) 所以空闲块head就要取代右邻在链表中的位置 导致指针的变化
		//属性变化
		temp_A = fre+fre->size;
		fre->size += temp_A->size;
		foot = FootLoc(temp_A);
		foot->uplink = fre;					//这个foot是右邻的foot 其uplink要指向空闲块的head
		fre->tag = 0;
		//指针的变化
		fre->llink = temp_A->llink;			//空闲块取代过程
		temp_A->llink->rlink = fre;
		fre->rlink = temp_A->rlink;
		temp_A->rlink->llink = fre;
	}
	else if(!(prev->tag) && !(next->tag))						//如果左邻右邻都为空闲
	{
		//左右都为空闲  左中右（上中下） 正好用左邻同时挂住自己 空闲块 右邻 。 右邻从此消失~~~
		//迷の右邻
		temp_A = (fre-1)->uplink;
		temp_B = fre+fre->size;
		temp_B->llink->rlink = temp_B->rlink;
		temp_B->rlink->llink = temp_B->llink;
		//属性变化
		temp_A->size = temp_A->size+fre->size+temp_B->size;
		foot = FootLoc(temp_B);
		foot->uplink = temp_A;				//这个foot就是那个迷失的右邻的。。。
	}
}
