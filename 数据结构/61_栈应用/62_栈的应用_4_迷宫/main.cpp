#include <stdio.h>
#include <stdlib.h>
//#include "stack.h"				//一种是自己写的用了栈		属于一条路走到黑  不行就退
#include "queue.h"					//一种是用了队列			属于从一个点发散到四个方向 广度搜索

#define length 10

//栈方法
//结构体声明在stack.h中			
//position是坐标 Node是一个点的信息  
//后来想其实用不到Node这样的 既然经过一个点后就变成0了， 那就没必要记录哪个方向可以走（之前并没有将路过的点设为0  后来设为0后 Node也不想删了 麻烦）
//队列方法（广度优先搜索）
//结构体只使用坐标点和记录前一个经过的点
int main()
{
	FILE *p;
	if(!(p=fopen("hehe.txt","r")))
		exit(1);
	int i,j;
	int Maze[length][length];
	for(i=0;i<length;i++)
		for(j=0;j<length;j++)
			fscanf(p,"%d",&Maze[i][j]);				//初始化整个迷宫
	for(i=0;i<length;i++)
		for(j=0;j<length;j++)
			printf("%d%c",Maze[i][j],((j+1)%10)==0?'\n':' ');

	position change[4] =							//事先写下一个模版  某点与模版上的一个点相加则向改点表示方向行进一格
	{
		{1,0},{0,1},{0,-1},{-1,0}					//分别代表向四个方向走 下 右 左 上 （为什么这个顺序呢  这个可以按照初始点和结束点来进行排序） 现在是（1，1）（8，8） 结束点在初始点的右下角 所以右下放前面，很难说吧  还是具体情况具体分析
	};
	//栈方法
	/*ps Stack = (ps)malloc(sizeof(s));
	init(Stack);
	pNode pass;
	position start = {1,1};							//初始点
	position current = start;							//变量 用来在迷宫行走
	position end = {8,8};								//结束点

	int temp_A;
	position temp_B;
	//int g=0,h;
	while((current.x!=end.x) || (current.y!=end.y) )					//依据为走到终点
	{
		//printf("( %d , %d )\n",current.x,current.y);
		pass = (pNode)malloc(sizeof(Node));
		pass->posi = current;
		for(temp_A=0;temp_A<4;temp_A++)				//记录每个方向是否可以走（程序后想想其实用不着这样）
		{
			temp_B.x = change[temp_A].x+current.x;
			temp_B.y = change[temp_A].y+current.y;
			//printf("Maze[%d][%d] = %d\n",temp_B.x,temp_B.y,Maze[temp_B.x][temp_B.y]);
			if(Maze[temp_B.x][temp_B.y] == 1 )
				pass->dire[temp_A] = 1;
			else
				pass->dire[temp_A] = 0;
		}
		//for(h=0;h<4;h++)
			//printf("%d  ",pass->dire[h]);
		//puts("");
		push(Stack,pass);								//入栈 记录到达终点的路


		temp_A = 0;
		while(temp_A<4 && !pass->dire[temp_A])
			temp_A++;
		if(temp_A < 4)					//找一个方向走
			pass->dire[temp_A] = 0;
		else											//每个方向都不能走 就退栈
		{
			while(temp_A >= 4)					//直到找到有路可走的点
			{
				pop(Stack,pass);
				free(pass);
				Gettop(Stack,pass);
				//printf("( %d , %d )\n",pass->posi.x,pass->posi.y);
				temp_A = 0;
				while(!pass->dire[temp_A])
					temp_A++;
			}
		}
		//for(h=0;h<4;h++)
		//	printf("%d  ",pass->dire[h]);
		//puts("");
		//printf("temp_A = %d\n",temp_A);
		//Maze[current.x][current.y] = 8;
		current.x = change[temp_A].x+pass->posi.x;				//按找到的方向走
		current.y = change[temp_A].y+pass->posi.y;
		//printf("( %d , %d )\n---------------\n",current.x,current.y);
		
	}
	traverse(Stack);*/

	//队列方法												//看起来更简单
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	position *qf,*qt;			//当前点 和 下一个点
	qf = (position *)malloc(sizeof(position));
	position end;
	qf->x = qf->y = 1;		//起点
	qf->previous = NULL;
	end.x = end.y = 8;			//终点
	en_queue(Queue,qf);
	int flag=1;
	//广度优先搜索明白这个搜索的具体实现下面就可以理解了
	while(!is_empty(Queue) && flag)								//如果队列空了说明找不到出口 或是 flag=0已找到 则退出循环
	{
		out_queue(Queue,qf);				//取出一个
		for(i=0;i<4;i++)									//这个点附近每个可能都试过一遍
		{
			qt = (position *)malloc(sizeof(position));
			qt->x = qf->x + change[i].x;
			qt->y = qf->y + change[i].y;
			qt->previous = NULL;
			if(Maze[qt->x][qt->y]==1)			//这个方向可以走
			{
				Maze[qt->x][qt->y] = -1;
				qt->previous = qf;												//记下这个那么找到终点后可以依据这个回顾整条路
				en_queue(Queue,qt);					//这个下线可以发展
				if(qt->x==end.x && qt->y==end.y)
				{
					flag = 0;
					break;
				}
			}
		}
	}
	while(qt)						//这里是把经过的点输出  如果想正过来输出当然方法很多 比如借用一个栈（放进去反向输出）或者再加一个队列也可以（队列和栈的相互实现）
	{
		printf("(%d,%d)\n",qt->x,qt->y);
		qt = qt->previous;
	}

	return 0;
}