#include "stack.h"
#include "queue.h"
#include "head.h"

void Print(BiTree T)
{
	if(T)
		printf("%d ",T->x);
}

void CreateBiTree(BiTree &root)								//按照先序顺序构造二叉树   其实跟遍历差不多的
{
	int temp;
	scanf("%d",&temp);									//如果这里使用的c++ ， 那就不需要有数据类型的考虑
	if(temp == 0)
	{
		root = NULL;
		return;
	}
	root = (BiTree)malloc(sizeof(BiTNode));
	root->x = temp;
	CreateBiTree(root->LN);
	CreateBiTree(root->RN);
}

void PreOrderTraverse(BiTree T,void (*Visit)(BiTree))				//先序遍历
{
	if(T)
		Visit(T);
	if(T->LN != NULL)
		PreOrderTraverse(T->LN,Visit);
	if(T->RN != NULL)
		PreOrderTraverse(T->RN,Visit);
}

//递归算法较为容易理解
void InOrderTraverse(BiTree T,void (*Visit)(BiTree))					//1   中序遍历
{
	if(T->LN != NULL)
		InOrderTraverse(T->LN,Visit);
	if(T)
		Visit(T);
	if(T->RN != NULL)
		InOrderTraverse(T->RN,Visit);
}//递归	

//理解较难				
void InOrderTraverse_2(BiTree T,void (*Visit)(BiTree))						//2
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
void InOrderTraverse_3(BiTree T,void (*Visit)(BiTree))						//3
{
	ps Stack;
	Stack = (ps)malloc(sizeof(s));
	BiTree temp = T;
	init(Stack);
	while(temp || !empty(Stack))						//这里与上面一个不同的地方  是因为没有事先把根节点放入  考虑2个情况就是①如果不含有左子节点 ②为空树
	{
		if(temp)
		{
			push(Stack,temp);
			temp = temp->LN;					//理解了上面一个后 看这个 较容易  这里是使劲往左移。。。
		}
		else								//这个else指的是已经移到了最左边了  此时的temp=NULL;  但是没有进入栈中
		{
			pop(Stack,temp);			//拿出最顶的temp
			Visit(temp);
			temp = temp->RN;				//令temp 等于右子节点 如果不空 也存入栈（这个毋庸置疑  因为从递归的概念看 这个相当于一个树 可能也拥有左子树和右子树 ）
		}
	}
}

void PostOrderTraverse(BiTree T,void (*Visit)(BiTree))						//后序遍历
{
	if(T->LN != NULL)
		PostOrderTraverse(T->LN,Visit);
	if(T->RN != NULL)
		PostOrderTraverse(T->RN,Visit);
	if(T)
		Visit(T);
}

void LevelOrderTraverse(BiTree T,void (*Visit)(BiTree))							//层序遍历
{
	pss Queue;
	Queue = (pss)malloc(sizeof(ss));
	BiTree temp;
	init(Queue);
	en_queue(Queue,T);
	/*Visit(T);
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		if(temp->LN)
		{
			en_queue(Queue,temp->LN);
			Visit(temp->LN);
		}
		if(temp->RN)
		{
			en_queue(Queue,temp->RN);
			Visit(temp->RN);	
		}
	}*/											//以上自己写的  显然要麻烦的多  但是书上就精简的多  在运行的时候既然 肯定每一个节点都要访问一遍的 所以不必要在存入队列的时候就访问 这样就可精简了
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		Visit(temp);
		if(temp->LN)
			en_queue(Queue,temp->LN);
		if(temp->RN)
			en_queue(Queue,temp->RN);
	}
}

void InitBiTree(BiTree &T)												//初始化
{
	T = NULL;
}

void DestroyBiTree(BiTree &T)											//销毁树
{	
	if(T->LN != NULL)
		DestroyBiTree(T->LN);
	if(T->RN != NULL)
		DestroyBiTree(T->RN);
	if(T == NULL)
		return;
	free(T);
	T = NULL;	
}


Type Parent(BiTree T,Type e)														//寻找父母节点  既然是寻找 那必是一个个找过来直到找到 就有一点遍历的意思
//这里采用层序遍历来寻找
{ 
	pss Queue;
	Queue = (pss)malloc(sizeof(ss));
	BiTree temp;
	init(Queue);
	en_queue(Queue,T);
	while(!is_empty(Queue))
	{
		out_queue(Queue,temp);
		if(temp->LN&&temp->LN->x==e || temp->RN&&temp->RN->x==e)
			return temp->x;													//找到返回父母节点的值
		if(temp->LN)
			en_queue(Queue,temp->LN);
		if(temp->RN)
			en_queue(Queue,temp->RN);
	}
	return NULL;
}
