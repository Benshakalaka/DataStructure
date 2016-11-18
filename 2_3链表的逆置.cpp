//作业
/*#include <stdio.h>			//数组的逆置

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	int len = 9,i;
	int n = len/2;
	for(i=0;i<n;i++)
		swap(&a[i],&a[len-1-i]);
	for(i=0;i<len;i++)
		printf("%d  ",a[i]);
	puts("");
	return 0;
}*/

#include <malloc.h>						//链表的逆置  这我不知道怎么搞 所以就简单的用数组从前往后存储继而从后往前赋值
#include <stdio.h>
typedef int Infotype;
typedef struct Node
{
	Infotype x;
	struct Node *next;
}N,*pN;

void swap(pN a, pN b)
{
	int temp = a->x;
	a->x = b->x;
	b->x = temp;
}

int main()
{
	pN head = (pN)malloc(sizeof(N));
	head->next = NULL;
	int count,i;
	printf("How many nodes do you wanna create ? \n");
	scanf("%d",&count);
	printf("Input the elements .\n");
	pN current = head,new_one;
	for(i=0;i<count;i++)
	{
		new_one = (pN)malloc(sizeof(N));
		scanf("%d",&(new_one->x));
		new_one->next = NULL;
		current->next = new_one;
		current = new_one;
	}
	int *array = (int *)malloc(sizeof(int)*count);
	i = 0;
	current = head->next;
	while(current)
	{
		array[i++] = current->x;
		current = current->next;
	}
	current = head->next;
	i--;
	while(current)
	{
		current->x = array[i--];
		current = current->next;
	}
	current = head->next;
	while(current)
	{
		printf("%d ",current->x);
		current = current->next;
	}
	current = head->next;
	while(current)
	{
		new_one = current->next;
		free(current);
		current = new_one;
	}
	return 0;
}