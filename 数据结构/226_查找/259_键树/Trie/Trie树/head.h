#ifndef HEAD_H
#define HEAD_H
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

typedef struct TrieNode
{
	NodeKind kind;
	union{
		struct {KeysType K;Record *infoptr;}lf;
		struct {TrieNode *ptr[27];int num;}bh;
	};
}TrieNode,*TrieTree;

#define EQ(a,b) (!strcmp((a),(b)))

int ord(char c);
void InitDSTable(TrieTree &T);
void DestroyDSTable(TrieTree &T);
Record *SearchTrie(TrieTree T,KeysType K);
void InsertDSTable(TrieTree &T,Record *r);
void TraverseDSTable(TrieTree T,void (*Visit)(Record*));
#endif