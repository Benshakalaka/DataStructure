//这里是对于A*算法的一个初步了解。		通过最初级的认识，我人为算法的可提升空间很大。主要在于H值的计算
//这里的A*算法应用于  在有障碍的地形下快速寻找目标（之前使用过深度优先和广度优先，这里比前两者要好些）
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "queue.h"
#include "heap.h"

#define Length 9
#define Width 8



Location Direction[4] = {								//这里是应用于对所在点四周的点的计算
	{-1,0},{1,0},
	{0,-1},{0,1}
};

int main()
{
	Unit **Maze;
	Maze = (Unit **)malloc(sizeof(Unit*)*Width);
	for(int i=0;i<Width;i++)
		Maze[i] = (Unit*)malloc(sizeof(Unit) * Length);
	FILE *p;
	if(!(p=fopen("hehe.txt","r")))
		exit(1);							
	for(i=0;i<Width;i++)										//地图初始化
		for(int j=0;j<Length;j++)
		{
			fscanf(p,"%d",&Maze[i][j].obstacle);					//为0的时候即为有阻碍
			Maze[i][j].G = Maze[i][j].H = 0;
			Maze[i][j].parent = 0;
			Maze[i][j].x = i;
			Maze[i][j].y = j;
		}
	for(i=0;i<Width;i++)
		for(int j=0;j<Length;j++)
			printf("%d%c",Maze[i][j].obstacle,((j+1)%9)==0?'\n':' ');

	Location cat,final,current;
	cat.x = 4;	cat.y = 2;					//初始位置
	final.x = 5;final.y = 6;				//最终位置
	current = cat;
	Heaptype Open;										//利用堆来记录这个Open表。 为什么用堆呢？因为我们需要的是G+H值最小的节点来组成路径。堆比较快
	init(Open);
	pss Close = (pss)malloc(sizeof(ss));				
	init(Close);
	en_queue(Close,cat);								//利用队列来记录Close表。该表记录的是已经走过的且不会再去考虑的路。这里我们还用来确定最后的路径
	int flag = 0;										//作为判断是否结束的标志
	Location temp;
	Unit PATH;
	
	while(!flag)										//用flag作标志，看是否走到最后
	{
		for(i=0;i<4;i++)								//检测四个方向
		{
			temp.x = current.x+Direction[i].x;
			temp.y = current.y+Direction[i].y;
			if(temp.x==final.x && temp.y==final.y)					//如果找到最后目标，立刻结束
			{
				en_queue(Close,final);
				flag = 1;
				break;
			}
			if(Maze[temp.x][temp.y].obstacle != 0 && !Checkifinheap(Open,temp) && !Checkifinlist(Close,temp))				//看这个方向的点是否① 为障碍 ② 已经在close或open集合中
			{
				Maze[temp.x][temp.y].G = Maze[current.x][current.y].G+1;							//G值的计算
				Maze[temp.x][temp.y].H = abs(temp.x-final.x) + abs(temp.y-final.y);					//H值的计算
				Maze[temp.x][temp.y].key = Maze[temp.x][temp.y].G+Maze[temp.x][temp.y].H;			//F为G、H求和
				Maze[temp.x][temp.y].parent = &Maze[current.x][current.y];
				InsertHeap(Open,Maze[temp.x][temp.y]);								//若是可能选择的点，则加入堆中
			}
		}
		if(flag)
			break;
		PATH = ExtractMin(Open);									//取出key最小的节点，组成路径
		temp.x = PATH.x;
		temp.y = PATH.y;
		en_queue(Close,temp);
		current = temp;												//相当于自身移动到所选取的点 以进行以后的递归寻找
	}
	pnod result = Close->phead->pnext;
	while(result)
	{
		printf("%d %d\n",result->data.x,result->data.y);
		result = result->pnext;
	}
	return 0;
}



