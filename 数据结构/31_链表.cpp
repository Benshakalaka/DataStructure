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

void ClearList(pS &root)				//链表各节点内容都置为0
{
	pS current = root->next;
	pS prev = NULL;
	while(current != NULL)
	{
		prev = current ->next;
		free(current);
		current = prev;
	}
	root->next =NULL;
}

void AddData(pS &root,int a)				//在链表尾端增加节点
{
	pS one = (pS)malloc(sizeof(S));
	one->data = a;
	one->next = NULL;
	pS Find = root;
	while(Find->next != NULL)
		Find = Find->next;
	Find->next = one;
	/*pS &Find = root->next;
	while(Find != NULL)
		Find = Find->next;
	Find = one;*/
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
void traverse(pS &root,void (*print)(pS &))						//遍历
{
	print(root);
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

int comparebigger(const void *a,const void *b)             // 作为函数指针  大于
{
	return (*(int *)a)>(*(int *)b)?1:0;
}
int compareequal(const void *a,const void *b)             // 作为函数指针  等于
{
	return (*(int *)a)==(*(int *)b)?1:0;
}
int Locate(pS &root,int e,int (*compare)(const void *,const void *))       //返回第一个与e满足compare关系的数的位置
{
	pS current = root->next;
	int count = 1;
	while(current != NULL && compare(&(current->data),&e) == 0)
	{
		current = current->next;
		count++;
	}
	if(current == NULL)
		return 0;
	else
		return count;
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



void DeleteList(pS &root,int i)
{
	pS current = root;
	while(current != NULL  && --i>0)
	{
		current = current->next;
	}
	pS temp = current->next;
	current->next = temp->next;
	free(temp);
}



void CpyList(pS &x,pS y)					// 复制y到x
{
	pS p = x->next;
	pS q = y->next;
}

void Union(pS &a,pS &b)							//联合两个链表 相同元素不再增加
{
	pS current = b->next;
	while(current != NULL)
	{
		if(Locate(a,current->data,compareequal) == 0)	//用到compareequal函数指针
			AddData(a,current->data);
		current = current->next;
	}
	DestroyList(b);
}

void Union2(pS &a,pS &b,pS &c)						//联合两个链表 相同元素依旧增加  不管两链表长度是否相等
{
	pS x=a->next, y=b->next;
	while(x && y)
	{
		if(x->data < y->data) 
		{
			AddData(c,x->data);
			x = x->next;
		}
		else
		{
			AddData(c,y->data);
			y = y->next;
		}
	}
	while(x) 
	{AddData(c,x->data);x=x->next;}
	while(y) 
	{AddData(c,y->data);y=y->next;}
}

void Union3(pS &a,pS &b,pS &c)						//联合两个链表 相同元素依旧增加  不管两链表长度是否相等
{
	pS x=a->next, y=b->next, z;
	z = c = a;
	while(x && y)
	{
		if(x->data < y->data) 
		{
			z->next = x;
			z = z->next;
			x = x->next;
		}
		else
		{
			z->next = y;
			z = z->next;
			y = y->next;
		}
	}
	while(x) 
	{z->next = x;z = z->next;x = x->next;}
	while(y) 
	{z->next = y;z = z->next;y = y->next;}
}





/*int main(void)
{
	pS X = InitList();
	traverse(X,print);
	AddData(X,5);
	AddData(X,3);
	AddData(X,9);
	AddData(X,1);
	traverse(X,print);															//测试遍历

	int m;
	if(GetList(X,3,m))														//测试 得到某个位置的数字
		printf("the %d number is : %d\n",3,m);
	else
		printf("NO Such Data!\n");


	m=6;
	printf("The %d number is bigger than %d\n",Locate(X,m,comparebigger),m);			//测试 哪个位置的数与该数满足compare关系

	printf("The length of the list is %d\n",ListLength(X));						//测试链表长度


	if(InsertList(X,2,4));												//测试插入
	else
		printf("Please choose a appropriate location next time\n");
	traverse(X,print);


	if(InsertList(X,1,111));
	else
		printf("Please choose a appropriate location next time\n");
	traverse(X,print);

	if(InsertList(X,7,7777));
	else
		printf("Please choose a appropriate location next time\n");
	traverse(X,print);

	printf("\n\nY\n");													//测试两联表联合
	pS Y = InitList();
	AddData(Y,4);
	AddData(Y,3);
	AddData(Y,64);
	AddData(Y,-6);
	traverse(Y,print);
	Union(X,Y);
	traverse(X,print);
	printf("Y\n\n");


	ClearList(X);															//测试置为0
	traverse(X,print);


	printf("The length of the list is %d\n",ListLength(X));				

	DestroyList(X);																//测试销毁链表
	traverse(X,print);
	return 0;
}
*/

/*int main()										//测试Union2  两链表合并  不去除相同 归并
{
	pS A,B,C;
	A = InitList();
	B = InitList();
	C = InitList();
	AddData(A,1);
	AddData(A,3);
	AddData(A,5);
	AddData(A,7);
	AddData(A,13);
	traverse(A,print);
	AddData(B,2);
	AddData(B,4);
	AddData(B,6);
	AddData(B,8);
	AddData(B,10);
	AddData(B,12);
	AddData(B,14);
	traverse(B,print);
	Union2(A,B,C);
	traverse(C,print);
	DestroyList(A);
	DestroyList(B);
	DestroyList(C);
	return 0;
}*/


/*int main()								//测试Union3   不新建节点 利用已有的
{
	pS A,B,C;
	A = InitList();
	B = InitList();
	AddData(A,1);
	AddData(A,3);
	AddData(A,5);
	AddData(A,7);
	traverse(A,print);
	AddData(B,2);
	AddData(B,4);
	AddData(B,6);
	AddData(B,8);
	traverse(B,print);
	Union3(A,B,C);
	traverse(C,print);
	traverse(A,print);
//	DestroyList(A);
//	DestroyList(B);
//	DestroyList(C);
	return 0;
}*/

int main()
{
	pS X = InitList();
	traverse(X,print);
	AddData(X,5);
	AddData(X,3);
	AddData(X,9);
	AddData(X,1);
	traverse(X,print);
	DeleteList(X,4);
	traverse(X,print);
	ClearList(X);
	traverse(X,print);
	return 0;
}