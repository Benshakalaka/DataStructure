#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <malloc.h>

typedef struct STUDENT
{
	int data;
	struct STUDENT *next;
}S,*pS;


pS InitList()						//初始化链表
{
	pS root = (pS)malloc(sizeof(S));
	root->next = NULL;
	return root;
}

void DestroyList(pS &root)					//销毁链表
{
	pS current = root->next;
	pS prev = NULL;
	while(current != NULL)
	{
		prev = current ->next;
		free(current);
		current = prev;
	}
	free(root);
	root = NULL;
	printf("The List has been destroyed!\n");
}



bool GetList(pS &root,int i,int &e)					//得到链表某位置节点的内容
{
	pS current = root->next;
	while(current != NULL && (i-1) != 0)
	{
		current = current->next;
		i--;
	}
	if((i-1) != 0) 
		return false;
	else 
	{
		e = current->data;
		return true;
	}
}

bool EmptyList(pS &root)								//判断为空
{
	if(root->next == NULL)
		return true;
	else
		return false;
}

int ListLength(pS &root)								//链表长度
{
	int counts = 0;
	pS current = root->next;
	while(current != NULL)
	{
		current = current->next;
		counts++;
	}
	return counts;
}


bool InsertList(pS &root,int i,int e)					//在i位置插入e这个值
{
	pS one = (pS)malloc(sizeof(S));
	one->data = e;
	one->next = NULL;
	pS current = root;
	while(current != NULL  && --i>0)
	{
		current = current->next;
	}
	if(current == NULL)
		return false;
	else
	{
		one->next = current->next;
		current->next = one;
		return true;
	}
}

bool DeleteList(pS &root,int i)
{
	if(i<1 || i>ListLength(root))
		return false;
	pS current = root;
	while(current != NULL  && --i>0)
	{
		current = current->next;
	}
	pS temp = current->next;
	current->next = temp->next;
	free(temp);
	return true;
}


void print(pS &root)					//作为函数指针
{
	if( root == NULL  ||root->next == NULL )
	//if( root->next == NULL ||root == NULL  )  //这句话先判断root->next  但如果root=NULL 就会出现对NULL解引用的现象从而出错
	{
		printf("NO DATA !\n");
		return;
	}
	pS current = root->next;
	while(current != NULL)
	{
		printf("%d ",current->data);
		current = current->next;
	}
	putchar('\n');
}
void Traverse(pS &root,void (*print)(pS &))						//遍历
{
	print(root);
}

#endif