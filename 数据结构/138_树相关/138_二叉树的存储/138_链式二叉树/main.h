#include <stdio.h>
#include "head.h"

int main()
{
	BiTree T;
	printf("按照先序次序输入（先根节点 继而左子 最后右子  0 即为空）: \n");
	CreateBiTree(T);
	PreOrderTraverse(T,Print);puts("");
	InOrderTraverse(T,Print);puts("");
	PostOrderTraverse(T,Print);puts("");
	DestroyBiTree(T);
	return 0;
}