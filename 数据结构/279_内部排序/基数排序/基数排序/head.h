#ifndef HEAD_H
#define HEAD_H
#define MAX_NUM_OF_KEY 8			//关键字项数的最大值

#define RADIX 10					//关键字基数，此时是十进制整数的基数

#define MAX_SPACE 1000			

#define Keystype char

typedef struct
{
	Keystype keys[MAX_NUM_OF_KEY];		//关键字
	//Infotype other;						//其他
	int next;
}SLCell;								//静态链表的节点类型

typedef struct
{
	SLCell r[MAX_SPACE];				//静态链表的可利用空间，r[0]为头节点
	int keynum;							//记录的当前关键字个数
	int recnum;							//静态链表的当前长度
}SLList;								//静态链表的类型
							
typedef int Arrtype[RADIX];				//指针数组类型

void Distribute(SLCell* &r,int i,Arrtype &f,Arrtype &e);		
//静态链表L的r域中记录已按(keys[0],...,keys[i-1])有序。
//本算法按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
//f[0...RADIX-1]和e[0...RADIX-1]分别指向各子表中第一个和最后一个记录

void Collect(SLCell* &r,int i,Arrtype f,Arrtype e);
//本算法按照keys[i]自小至大将f[0...RADIX-1]所指各子表依次连接成一个链表
//e[0...RADIX-1]为各子表的尾指针

void RadixSort(SLList &L);
//L是采用静态链表表示的顺序表
//对L做基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点

#endif