#include <stdio.h>                   //报数游戏
#include <malloc.h>
#define S_M "How many student ? \n"
typedef struct every                      //因为要弄成一个循环  虽然数组也可以循环但是不好删除  所以用链表
{
	int num;
	struct every *link;
}T,*pT;
int main()
{
	pT first=NULL;                      //需要找一个开始循环的地方
	pT prev=NULL;                       //中间变量
	pT new_one,current;                 //创建的时候 和 遍历的时候用
	printf(S_M);
	int s_m;
	scanf("%d",&s_m);                    //人数
	printf("to the which number ? \n");
	int max;
	scanf("%d",&max);                    //报数的最大值（即报道该数的人退出游戏）
	int i;
	for(i=1;i<=s_m;i++)
	{
		new_one=(pT)malloc(sizeof(T));
		if(first == NULL)
			first=new_one;
		else
			prev->link=new_one;
		new_one->link=NULL;
		new_one->num=i;
		prev=new_one;
		if(i==s_m)
			new_one->link=first;                   //为每个人分配一个number   并实现循环
	}
	//printf("%d   ",first->num);
	/*current=first;
	for(i=1;i<=s_m+1;i++)
	{
		printf("%d   ",current->num);
		current=current->link;
	}*/
	current=first;
	for(i=1;;i++)
	{
		if(i%max ==0 )
		{
			prev->link=current->link;         //跳过这个人
			s_m--;
			printf("%d  ",current->num);      //输出删掉的人的number
			prev=current->link;
			free(current);                  //free该结构体
			current=prev;
		}
		else
		{
			prev=current;                 //为上面删除一个人记录前一个人的地址提供方便
			current=current->link;
			
		}
		if(s_m==1)                        //一个人的时候 直接free  因为没有prev
		{
			printf("%d  ",current->num);
			free(current);
			break;
		}
	}
	return 0;
}

//这个更好  不过上面的是自己写的
/*
	while(n)
	{
		for(i=1;i<m;i++)        //掠过m－1个表元
			u=u->link;
		p=u->link;             //p指向第m个表元
		u->link=p->link;             //第m个表元从环中脱钩
		printf("%4d",p->no);
		free(p);                //释放第m个表元占用的空间
		n--;
	}
*/