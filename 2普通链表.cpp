#include <stdio.h>                //程序没有释放内存  视频里没有释放 但我觉得应该是要释放的
#include <malloc.h>               //    for     malloc
#include <stdlib.h>                    //   for        exit


typedef struct Student         //结构体声明
{
	int num;
	struct Student *pnext;
}node,* pnode;                   //利用typedef来改名字


pnode createnode(void);             //创建函数返回指针
void traverse(pnode);              //遍历
bool is_empty(pnode);               //判断链表是否为空
int length(pnode);                    //看长度
void sort(pnode);                   //链表排序
void sort2(pnode &);				//改善后的链表排序
bool insert(pnode,int,int);          //插入
bool delete_list(pnode,int,int *);   //删除 
 


int main()
{
	pnode phead;
	phead=createnode();
	traverse(phead);
	insert(phead,3,999);
	traverse(phead);
	return 0;
}


pnode createnode()             //创建函数返回指针
{
	pnode phead=(pnode)malloc(sizeof(node));      //此为头结点(与众节点是相同的)
	if(phead==NULL)                                   //这一步也挺必要的  不过不怎么会用到
	{
		printf("Sorry ! the memory is empty ! \n");
		exit(1);
	}
	pnode ptail=phead;
	ptail->pnext=NULL;                               //指定一个尾节点永远指向链表尾部以方便添加
	printf("how long do you want to input?\n");
	int len,i,temp;
	scanf("%d",&len);
	for(i=0;i<len;i++)
	{
		pnode newnode=(pnode)malloc(sizeof(node));
		if(newnode==NULL)
		{
			printf("Sorry ! the memory is empty ! \n");
			exit(1);
		}
		printf("the %d number :  ",i+1);
		scanf("%d",&temp);
		newnode->num=temp;
		ptail->pnext=newnode;                     // 操作尾节点 来增加链表节点  这一步是把地址赋给尾节点指向的节点的pnext
		newnode->pnext=NULL;                       //这一步是让new节点的pnext等于NULL  因为不确定是否为最后一个节点 
		ptail=newnode;                            //这一步是使尾节点再次指向最后一个节点
	}
	return phead;
}


void traverse(pnode phead)          //遍历
{
	pnode p=phead->pnext;            //本来想能不能直接操作 phead呢  原来是不行的  操作了就那phead改掉了  怎么能改呢？
	while(p!=NULL)
	{
		printf("%d  ",p->num);
		p=p->pnext;
	}
	putchar('\n');
}




bool is_empty(pnode phead)               //判断链表是否为空
{
	if(phead->pnext==NULL)
		return true;
	else
		return false;
}



int length(pnode phead)                                //看长度
{	
	int len=0;
	pnode p=phead->pnext;            
	while(p!=NULL)
	{
		len++;
		p=p->pnext;
	}
	return len;
}




void sort(pnode phead)                   //链表排序
{
	pnode p=phead->pnext;
	pnode q;
	int i,j,t,len;
	len=length(phead);
	for(i=0;i<len;i++,p=p->pnext)              //这一块的算法跟数组是一样的  不过这里可以不用什么 p=p->pnext 也可以用p++不过这个就用到了c++里的操作符重载  就成了所谓的泛型 （ 笔记本上有记载 ）
	{
		for(j=i+1,q=p->pnext;j<len;j++,q=q->pnext)               
			if(p->num > q->num)
			{
				t=p->num;                      //我就想 如果数据的成员多一点的话 那也要这样一个一个的复制吗。。我觉得看可以利用地址来完成 
				p->num=q->num;
				q->num=t;
			}
	}
}
//这里通过整个的交换 继而把地址互换回来
void sort2(pnode &phead)
{
	pnode p=phead->pnext;
	pnode q;
	node t;												//这里不好弄pnode指针t 因为下面我要进行是内容交换 而不是地址交换(如果是地址交换的话，那t与某个指针存一样的地址，那个指针改动后t的内容也会跟着改动，就不方便后来把指针拿回去)
	int i,j,len;
	len=length(phead);
	for(i=0;i<len;i++,p=p->pnext)
	{
		for(j=i+1,q=p->pnext;j<len;j++,q=q->pnext)               
			if(p->num > q->num)
			{
	//			printf("p所存地址 ：%p\nq所存地址 ：%p\nt所存地址 ：%p\n",p->pnext,q->pnext,t.pnext);
				t = *p;						//内容交换（通过指针的解引用）
				*p = *q;
				*q = t;
	//			printf("\np所存地址 ：%p\nq所存地址 ：%p\nt所存地址 ：%p\n",p->pnext,q->pnext,t.pnext);
				q->pnext = p->pnext;			//将指针内容里存着的地址交换回来
				p->pnext = t.pnext;
	//			printf("\np所存地址 ：%p\nq所存地址 ：%p\nt所存地址 ：%p\n",p->pnext,q->pnext,t.pnext);
			}
	}
}



bool insert(pnode phead,int pos,int val)                            //插入        插入和删除差不多 只是修改一些
{
	pnode p=phead;
	int i=0;
	while(i<pos-1 && p!=NULL)                                     //找到插入的前一个节点   插入是要在一个节点后面 所以该节点不能为NULL
	{
		p=p->pnext;
		i++;
	}
	if(pos <1 || p==NULL)
		return false;
	pnode newp=(pnode)malloc(sizeof(node));                     
	newp->num=val;                                                  //执行插入操作
	newp->pnext=p->pnext;
	p->pnext=newp;
	return true;
}




bool delete_list(pnode phead,int pos,int *val)                    //       删除
{
	pnode p=phead;
	int i=0;
	while(i<pos-1 && p->pnext!=NULL)                              //找到删除节点的前一个节点    该节点的pnext 即指针域不能为NULL   如果是NULL 那该节点就是最后一个节点了啊
	{
		p=p->pnext;
		i++;
	}
	if(pos <1 || p->pnext==NULL)
		return false;
	pnode newp=(pnode)malloc(sizeof(node));
	*val=p->pnext->num;                                                //执行删除操作  把删去的数赋给val
	p->pnext=p->pnext->pnext;
	free(p->pnext);    
	p->pnext=NULL;                                            //free()操作是释放指针所指向的内存 而指针变量已然存在      指针就是地址 地址就是指针  然而指针和指针变量是不一样的
	return true;
}