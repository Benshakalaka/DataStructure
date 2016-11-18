#include <stdio.h>
#include "head.h"

int main()
{
	int i;
	CSTree T,p;
	Type e,e1;
	InitTree(T);
	printf("The depth of the tree is : %d\n",TreeDepth(T));
	CreateTree(T);
	printf("The depth of the tree is : %d\n",TreeDepth(T));
	printf("PreOrder Traverse the Tree: \n");
	PreOrderTraverse(T,Print);puts("");
	printf("Please input the element you want to remedy and the new one : \n");
	scanf("%d%d",&e,&e1);
	Assign(T,e,e1);
	printf("PostOrder Traverse the Tree :\n");
	PostOrderTraverse2(T,Print);puts("");
	printf("The parent of %d is %d ,first son is %d and next brother is %d\n",e1,Parent(T,e1),LeftChild(T,e1),RightSibling(T,e1));



	/*printf("建立树p：\n");
	InitTree(p);
	CreateTree(p);
	printf("and then LevelOrder Traverse the tree p:\n");
	LevelOrderTraverse(p,Print);puts("");
	printf("Insert the Tree p into T,input the parent and order: ");
	scanf("%d%d",&e,&i);
	InsertChild(T,e,i,p);
	printf("LevelOrder Traverse the tree\n");
	LevelOrderTraverse(T,Print);
	printf("Delete the i ed sonTree e of T: ");
	scanf("%d%d",&e,&i);
	DeleteChild(T,e,i);
	printf("LevelOrder Traverse the tree\n");
	LevelOrderTraverse(T,Print);puts("");*/
	DestroyTree(T);
	return 0;
}