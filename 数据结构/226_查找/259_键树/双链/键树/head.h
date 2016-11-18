#ifndef HEAD_H
#define HEAD_H
//操作中不含有删除 因为这种树一般是不会删除节点的
#define MAXKEYLEN 16					//关键字的最大长度

typedef struct
{
	char ch[MAXKEYLEN];					//关键字
	int num;							//关键字长度
}KeysType;								//关键字类型

typedef enum {LEAF , BRANCH} NodeKind;	//节点种类：｛叶子，分支｝

struct Record							//信息记录类型  在双链树中的叶子节点中的infoptr指针就指向某个这种类型的信息
{
	KeysType key;						//记录中的关键字
	//Others other;					//其他部分（暂时隐匿 避免麻烦）
};
typedef struct DLTNode
{
	char symbol;
	struct DLTNode *next;				//指向兄弟节点
	NodeKind kind;
	union{
	Record *infoptr;					//叶子节点的记录指针
	struct DLTNode *first;				//分支节点的孩子链指针
	};
}DLTNode, *DLTree;				//双链树的类型


void InitDSTable(DLTree &DT);				//构造一个空的双链树
void DestroyDSTable(DLTree &DT);			//双链树DT存在，将其销毁
Record *SearchDLTree(DLTree DT,KeysType K);	//搜索关键字。若搜到，则返回指向该记录的指针，否则返回空
void InsertDSTable(DLTree &DT,Record *r);	//若DT中不存在其关键字等于r->key的数据元素，则按顺序插入
void TraverseDSTable(DLTree DT,void (*Visit)(Record*));	//遍历

#endif