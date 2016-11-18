#ifndef HEAD_H
#define HEAD_H


typedef int Keytype;		//关键字类型

#define NULLKEY 0


typedef struct				//存储元素结构
{
	Keytype key;
}Elemtype;

typedef struct
{
	Elemtype *elem;			//数据元素存储基址，动态分配数组
	int count;				//当前数组元素个数
	int sizeindex;			//hashsize[sizeindex]为当前容量
}HashTable;

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define EQ(a,b) ((a)==(b))

void InitHashTable(HashTable &H);
void DestroyHashTable(HashTable &H);
unsigned Hash(Keytype K);
int SearcHash(HashTable H,Keytype K,int &p,int &c);
int InsertHash(HashTable &H,Elemtype e);
int Delete(HashTable &H,Elemtype e);
void TraverseHash(HashTable H,void(*Visit)(Elemtype));
int Find(HashTable H,Keytype K,int &p);
#endif