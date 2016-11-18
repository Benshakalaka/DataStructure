#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
	char x;
	struct Node *Lnode;
	struct Node *Rnode;
}N,*pN;

void traverse(pN root)            //先序遍历
{
	printf("%c  ",root->x);
	if(root->Lnode != NULL)
		traverse(root->Lnode);
	if(root->Rnode != NULL)
		traverse(root->Rnode);
}

void find(pN root,pN &result,char c)            //其中是否有不易察觉的bug我还不知道
{
	if(root->x == c )
	{
		result = root;
		return;
	}
	else
	{
		if(root->Lnode!= NULL)
			find(root->Lnode,result,c);
		if(root->Rnode != NULL)
			find(root->Rnode,result,c);
	}
}


pN createroot(char a)                 //创建根节点
{
	pN root;
	root = (pN)malloc(sizeof(N));
	root->x = a;
	root ->Lnode = root->Rnode = NULL;
	return root;
}





void Addnode(pN root,char a)     //增加节点
{
	pN new_one;
	new_one = (pN)malloc(sizeof(N));
	new_one ->x = a;
	new_one->Lnode = new_one->Rnode =NULL;
	printf("Which node do you want to follow ?(It's data) _\b");
	char c;
	scanf(" %c",&c);
	pN temp=NULL;
	find(root,temp,c);
	if(temp == NULL)
	{
		printf("NO DATA !\n");
		return;
	}
	printf("Which side ? (l or r) _\b");
	scanf(" %c",&c);
	if(c == 'l')
	{
		if(temp->Lnode != NULL)
		{
			printf("It has been used !\n");
			free(new_one);
		}
		else
		{
			temp->Lnode = new_one;
			printf("OK!\n");
		}
	}
	else if(c == 'r')
	{
		if(temp->Rnode != NULL)
		{
			printf("It has been used !\n");
			free(new_one);
		}
		else
		{
			temp->Rnode = new_one;
			printf("OK!\n");
		}
		
	}
	else
	{
		printf("Are you kidding ?\n");
		free(new_one);
	}
}




int main()
{
	char ch;
	printf("Please input the root's data: _\b");
	scanf("%c",&ch);
	fflush(stdin);
	pN root = createroot(ch);
	char select;
	printf("Do you want to add node ? (y or n)\n: _\b");
	while((select=getchar()) != 'n')
	{
		printf("Enter the data first please _\b");
		scanf(" %c",&ch);                 //这里%c前面有空一格也是有必要的 虽然不明所以
		Addnode(root,ch);
		fflush(stdin);
		printf("Do you still want to add node ? (y or n)\n: _\b");
	}
	traverse(root);
	return 0;
}













/*void find(pN root,pN &result,char c,int *b)            
{
	if(root->x == c  &&  *b)
	{
		result = root;
		*b=0;return;
	}
	if(root->Lnode != NULL)
		find(root->Lnode,result,c,b);
	if(root->Rnode != NULL)
		find(root->Rnode,result,c,b);
}*/






