#ifndef HEAD_H
#define HEAD_H
typedef enum Color{Red,Black} Color;

typedef int Key;

typedef struct RBT
{
	Color color;
	Key key;
	struct RBT *Lchild;
	struct RBT *Rchild;
	struct RBT *Parent;
}RBNode, *RBTree;

void LEFT_ROTATE(RBTree &T,RBTree x);
void RIGHT_ROTATE(RBTree &T,RBTree y);
void RB_INSERT(RBTree &T,Key x);
void RB_INSERT_FIXUP(RBTree &T,RBTree x);
void RB_DELETE(RBTree &T,Key x);
void RB_DELETE_FIXUP(RBTree &T,RBTree x,int side);
RBTree RBSearch(RBTree T,Key x);
void RBTraverse(RBTree T);
#endif