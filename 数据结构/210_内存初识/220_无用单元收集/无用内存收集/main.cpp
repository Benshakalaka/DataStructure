//这里主要是main.cpp里面的MarkList 函数
#include <stdio.h>
#include "head.h"
#include "String.h"

void visit(GList p);
void MarkList(GList L);

int main()
{
	GList L;
	String S;
	char c[30] = "(a,(b,c,d))";
	StrAssign(S,c);	printf("------\n");
	CreateGList(L,S);
	Traverse_GL(L,visit);
	MarkList(L);
	printf("After:\n");
	Traverse_GL(L,visit);
	return 0;
}



void visit(GList p)
{
	if(p->tag==ATOM)
		printf("mark=%d  %c\n",p->mark,p->elem);
	else if(p->tag==LIST)
		printf("mark=%d  list\n",p->mark);
}


//利用表节点本身的指针域标记遍历路径的算法
//节点中的tag  代表路径的走向（即当指针p由b(p所指节点)移向c(p的hp部分)之前，先将b节点中的hp域值改为指向a，并将b节点中的tag域值改为0；而当指针p由b移向f(p的tp部分)之前，则先将b节点中的tp域的值改为指向a，tag域的值改为1.）
void MarkList(GList L)						//为占用节点做标志
{
	GList t,p,q;					//声明三个变量	t为当前节点p的母节点 q为p的表头或表尾
	t = NULL;						//如图所示  当p指向第一个节点时，t=null
	p = L;
	int finished = 0;
	//本循环类似于树的非递归遍历，但是并没有用到栈 是利用本身的指针标记进行循环 
	while(!finished)			//循环的条件在非递归遍历中是用empty(Stack) 但这里没有 所以需要在特定情况下指定循环结束条件(其实非递归遍历也可以理解成这样 即当栈空时finished=1)
	{
		//这个循环：表里面存有表头指针表尾指针(除了表头就是表尾) 这里先从表头着手(因为表头就又是一个表，然后再表头。。。(递归)）
		while(p->mark == 0)			//循环的判断条件当mark==1时结束 //导致mark==1的情况有以下两种【备注①②】	
		{
			p->mark = 1;		//经过即标志
			q = p->hp;			//q为p的表头
			if(q && q->mark==0)										//导致mark==1情况 ① q不存在 即空 没有hp更不可能有tp了
			{
				if(q->tag==0)										//导致mark==1情况 ② 连接的是原子而非表 相当于空 即无法再往下
					q->mark = 1;
				else					//表头也是表 意味着3个变量都要变化   向下走
				{
					p->hp = t;		
					p->tag = ATOM;			//令tag=0 即下一次是移向hp部分 并且hp部分已变为记录t
					t = p;
					p = q;
				}
			}
		}							//循环结束 表明已走到每个head表的head的尽头（极力向左靠 最左边）
									//中序非递归遍历也是差不多  先往最左边走，输出，然后出栈，然后向出栈元素的右边走 存在则新一遍循环（又是完整的树） 不存在则继续出栈。。。
		q = p->tp;					//head弄完了 就弄tail  顺着过程图走一边就明白
		if(q && q->mark==0)							//若tail存在并且未标志过，则相当于一个新的表 回到循环最初  当然 t,p,q需要变化 p变成p->tp（非递归遍历中是等于右子树 然后回归最初循环）
		{
			p->tp = t;
			//p->tag = 1;			//不需要改变这个  自己再写一遍的时候加上了因为是向右走嘛 但看书上没加 应该是因为这本身是一个表，tag就等于1（不会是原子 看上面的循环可知 :会提前用q去试探）实在不懂跟着过程图走一边
			t = p;
			p = q;
		}
		else										//若tail不存在，说明这个节点的tp是走不下去的 必须返回上层（非递归遍历中是出栈，在这里‘出栈’操作较为繁琐）
		{
			//这个循环在t的tag=0时候断掉而不是p的tag=0的时候，然而我们要的是p的tp可以走，为什么这样呢 因为用t来判断的话，当t等于NULL的时候 说明没有一个节点tp可以走 但是用p，p=NULL时候，执行q = t;t = q->tp;时候就报错了。但是用t，下面就需要让p=t；
			while(t && t->tag==1)			//首先需要往上走 往上走一次依旧tp不能走 那依然往上走（如何判断tp能不能走呢？ tag=1表示这个节点往右走过 或是 本身就是右边从右边回来的，没有右边可以走 tag=0表明暂时只向左走过）
			{
				q = t;
				t = q->tp;
				q->tp = p;					//这一步：还原。  往回走后之后就不会在回来 那么tp中以前存的t(母节点)现在要存回原来的下一个
				p = q;
			}
			if(!t)				//当t回到最最初的时候整个程序结束
				finished = 1;
			else				//找到可以往tp走的节点
			{
				q = t;
				t = q->hp;
				q->hp = p;			//还原  因为要往右走了 所以hp就恢复 让tp去存
				p = q;
				p->tag = LIST;			//往右走 需要让tag=1 很容易遗漏
			}
		}
	}
}

//-------------------------------------------------------------以下是树的中序非递归遍历， 用于比较
/*void InOrderTraverse_2(BiTree T,void (*Visit)(BiTree))						//2
{
	ps Stack;
	Stack = (ps)malloc(sizeof(s));
	BiTree temp;
	init(Stack);
	push(Stack,T);
	
	while(!empty(Stack))			//一开始会搞混乱 左子节点一个一个过去是要push的(因为还有右子节点等会儿需要访问)  然而如果是右子节点的话就不push了 因为既然已经是右子节点（二叉树）这一层就无需考虑了  pop出来的直接是上上层
	{
		while(Gettop(Stack,temp) && temp)
			push(Stack,temp->LN);
		pop(Stack,temp);						//上面的循环是直到temp=NULL停止  那么就会（肯定）有一个NULL 也被存在这个栈中  要把他弄出来  
		if(!empty(Stack))					//有可能根节点就是NULL  那么这个if就不需要运行了
		{
			pop(Stack,temp);				//提取栈顶元素			注意！！！这里拿出来就没有再放进去  因为接下来考虑右子节点了
			Visit(temp);						//输出这个位置的元素内容  
			push(Stack,temp->RN);				//把右子节点放进去
		}
	}			//直到栈里没有元素了 那说明整个结束了  因为存在栈里是为了访问右子节点 既然没了 说明右边的也全访问过了
}//非递归
*/