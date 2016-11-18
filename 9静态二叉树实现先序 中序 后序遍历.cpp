#include <stdio.h>             //简单的静态二叉树实现先序 中序 后序遍历  
#include <malloc.h>

typedef struct Node
{
	char data;
	struct Node *plchild;
	struct Node *prchild;
}N,*pN;

pN createNode();
void xianxu(pN);
void zhongxu(pN);
void houxu(pN);

int main()
{
	pN pT=createNode();
	xianxu(pT);
	puts("\n");
	zhongxu(pT);
	puts("\n");
	houxu(pT);
	putchar('\n');
	return 0;
}

pN createNode()
{
	pN pA=(pN)malloc(sizeof(N));
	pN pB=(pN)malloc(sizeof(N));
	pN pC=(pN)malloc(sizeof(N));
	pN pD=(pN)malloc(sizeof(N));
	pN pE=(pN)malloc(sizeof(N));

	pA->data = 'A';
	pB->data = 'B';
	pC->data = 'C';
	pD->data = 'D';
	pE->data = 'E';

	pA->plchild = pB;
	pA->prchild = pC;
	pB->plchild=pB->prchild = NULL;
	pC->plchild = pD;
	pC->prchild = NULL;
	pD->plchild = NULL;
	pD->prchild = pE;
	pE->plchild=pE->prchild = NULL;
	return pA;
}

void xianxu(pN p)                        //主要是递归这里  看汉诺塔那题
{
/*	先根节点；
	再先序左；
	再先序右；
*/
	putchar(p->data);
	if(p->plchild != NULL)
		xianxu(p->plchild);
	if(p->prchild !=NULL)
		xianxu(p->prchild);
}

void zhongxu(pN p)
{
	if(p->plchild != NULL)
		zhongxu(p->plchild);
	putchar(p->data);
	if(p->prchild != NULL)
		zhongxu(p->prchild);
}

void houxu(pN p)
{
	if(p->plchild != NULL)
		houxu(p->plchild);
	if(p->prchild != NULL)
		houxu(p->prchild);
	putchar(p->data);
}








