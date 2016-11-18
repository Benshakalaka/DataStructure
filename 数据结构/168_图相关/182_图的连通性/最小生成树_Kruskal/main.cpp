#include <stdio.h>							//这里是针对无向网的最小生成树
#include "MGraph.h"

typedef struct Arc						//这个结构体存放的是无向图的每一条边（无重复）以及其权值  为的是在做kruskal时快速得到最短路径
{
	VexType m,n;		//路径的两端	
	int weight;			//权值
}Arc,pArc[30];
typedef struct Vex
{
	VexType v;			//这个结构体数组将所有顶点存入  放下所有边 重新挑选以构成最短树
	int num;			//这个num放在这里算作标记		为零则表示尚未归入分量中	不为0则表示已经被分配到其他分量中	（标记的作用是将不同的顶点分到不同的分量）
}Vex,pV[30];

void MiniSpanTree(MGraph G);						//Kruskal算法
void Extract(MGraph G,pArc arcs);					//将所有边挑选出来 并排好序 这样易于将最短路径拿出来

int main()
{
	MGraph G;
	CreateGraph_UDN(G);					//为了方便 这个程序的输入为文本读入
	Display(G);
	
	/*for(int i=0;i<G.arcnum;i++)
		printf("%d  %s  %s\n",arcs[i].weight,arcs[i].m,arcs[i].n);*/
	MiniSpanTree(G);			//最小生成树
	return 0;
} 

//这个是自己根据理解写的  没有参照所以会显得很繁琐
/*void MiniSpanTree(MGraph G)					//kruskal算法求最小生成树
{
	pArc arcs;
	Arc temp;
	pV vexes;
	int i,count=0,kinds=1,j,k;
	Extract(G,arcs);
	printf("----------------------------\n");
	for(i=0;i<G.arcnum;i++)								//Extract之后将所有边展示出来
		printf("%d  %s  %s\n",arcs[i].weight,arcs[i].m,arcs[i].n);
	printf("----------------------------\n");
	for(i=0;i<G.vexnum;i++)
	{
		strcpy(vexes[i].v,G.vexs[i]);
		vexes[i].num = 0;								//为零则表示尚未归入分量中	不为0则表示已经被分配到其他分量中  下面的一个循环主要是根据这个标记做主要情况依据的
	}
	int p,q;
	for(i=0;i<G.vexnum-1;i++)
	{
		temp = arcs[count];												//可以根据顺序一一拿出来 因为已经从小到大排序好了
		p = LocateVex(G,temp.m);			//弧两头的顶点的数组下标
		q = LocateVex(G,temp.n);
		if(!vexes[p].num || !vexes[q].num)										//情况①（两个点的标记都为0或有其中一个为0）							
		{
			if(!vexes[p].num && !vexes[q].num)					//都为0 表示都未曾归入任何分量 可以任意结合
				vexes[p].num = vexes[q].num = kinds++;
			else												//其中一个为0
			{
				if(!vexes[p].num)					//一个为0  这两个结合后 为0的一个的标记需要等于(归入)另一个不为0的分量中
					vexes[p].num = vexes[q].num;
				else
					vexes[q].num = vexes[p].num;
			}
			printf("%s --- %s   %d\n",temp.m,temp.n,temp.weight);
		}
		else if(vexes[p].num == vexes[q].num){}									//情况② （不为0（不是闲置的）并且相等（属于同一分量 不能连接 否则会构成回路））
		else																	//情况③ （都不为0）
		{
			if(vexes[p].num > vexes[q].num)						//一个大于另一个 则不仅要将A归入B 还要将A的整个分量归入B（所有与A标记相同的都需要等于B）
			{
				k = vexes[q].num;
				for(j=0;j<G.arcnum;j++)
					if(vexes[j].num==k)
						vexes[j].num = vexes[p].num;
			}
			else												//B归入A
			{
				k = vexes[p].num;
				for(j=0;j<G.arcnum;j++)
					if(vexes[j].num==k)
						vexes[j].num = vexes[q].num;
			}
			printf("%s --- %s   %d\n",temp.m,temp.n,temp.weight);

		}
		count++;															//处理下一个最短路径
	}
}*/
//下面这个是经过一点点点点点加工的（精简）
void MiniSpanTree(MGraph G)					//kruskal算法求最小生成树
{
	pArc arcs;
	Arc temp;
	pV vexes;
	int i,count=0,kinds=1,j,k;
	Extract(G,arcs);
	printf("----------------------------\n");
	for(i=0;i<G.arcnum;i++)								//Extract之后将所有边展示出来
		printf("%d  %s  %s\n",arcs[i].weight,arcs[i].m,arcs[i].n);
	printf("----------------------------\n");
	for(i=0;i<G.vexnum;i++)
	{
		strcpy(vexes[i].v,G.vexs[i]);
		vexes[i].num = 0;								//为零则表示尚未归入分量中	不为0则表示已经被分配到其他分量中  下面的一个循环主要是根据这个标记做主要情况依据的
	}
	int p,q;
	for(i=0;i<G.vexnum-1;i++)
	{
		temp = arcs[count];												//可以根据顺序一一拿出来 因为已经从小到大排序好了
		p = LocateVex(G,temp.m);			//弧两头的顶点的数组下标
		q = LocateVex(G,temp.n);
		if(!vexes[p].num || !vexes[q].num)										//情况①（两个点的标记都为0或有其中一个为0）							
		{
			if(!vexes[p].num && !vexes[q].num)					//都为0 表示都未曾归入任何分量 可以任意结合
				vexes[p].num = vexes[q].num = kinds++;
			else												//其中一个为0
			{
				if(!vexes[p].num)					//一个为0  这两个结合后 为0的一个的标记需要等于(归入)另一个不为0的分量中
					vexes[p].num = vexes[q].num;
				else
					vexes[q].num = vexes[p].num;
			}
			printf("%s --- %s   %d\n",temp.m,temp.n,temp.weight);
		}
		else if(vexes[p].num == vexes[q].num){}									//情况② （不为0（不是闲置的）并且相等（属于同一分量 不能连接 否则会构成回路））
		else																	//情况③ （都不为0）
		{
			if(vexes[p].num < vexes[q].num)
			{
				k = p;
				p = q;
				q = k;
			}
			k = vexes[q].num;
			for(j=0;j<G.arcnum;j++)
				if(vexes[j].num==k)
					vexes[j].num = vexes[p].num;
			printf("%s --- %s   %d\n",temp.m,temp.n,temp.weight);

		}
		count++;															//处理下一个最短路径
	}
}

void Extract(MGraph G,pArc arc)
{
	int i,j,k=0;
	Arc temp;
	for(i=0;i<G.vexnum;i++)											//因为是无向图 所以左下三角 和 右上三角所存放的是同样的数据 
		for(j=0;j<i;j++)
			if(G.arcs[i][j].adj)
			{
				arc[k].weight = G.arcs[i][j].adj;
				strcpy(arc[k].m,GetVex(G,i));
				strcpy(arc[k++].n,GetVex(G,j));
			}
	for(i=0;i<G.arcnum-1;i++)											//选择排序
		for(j=i+1;j<G.arcnum;j++)
			if(arc[i].weight>arc[j].weight)
			{
				temp = arc[i];
				arc[i] = arc[j];
				arc[j] = temp;
			}
}


//以上自己写的大致思路是正确的   不过查了下，还可以更精简 效率更高
/*
KRUSKAL(V, E, w)

A ← { }           ? Set A will ultimately contains the edges of the MST
for each vertex v in V
    do MAKE-SET(v)
sort E into nondecreasing order by weight w
for each (u, v) taken from the sorted list
    do if FIND-SET(u) = FIND-SET(v)
        then A ← A ∪ {(u, v)}
            UNION(u, v)
return A

 */