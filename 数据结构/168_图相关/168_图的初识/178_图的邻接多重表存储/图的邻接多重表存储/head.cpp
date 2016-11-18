#include "head.h"
#include "queue.h"

int LocateVex(AMLGraph G,VexType v)									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(!strcmp(G.adjmulist[i].data,v))				//等于0即相同
			return i;
	return -1;
}

void CreateGraph(AMLGraph &G)							//构造无向图
{
	printf("How many?\n");								//顶点数
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("the names : ");					//顶点名字
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.adjmulist[i].data);
		G.adjmulist[i].firstedge = NULL;
	}
	VexType v1,v2;
	int m,n;
	EBox *new_one;
	printf("the arcs : ");
	for(i=0;i<G.arcnum;i++)							//将每条边输入
	{
		scanf("%s%s",v1,v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		new_one = (EBox*)malloc(sizeof(EBox));
		new_one->mark = unvisited;
		new_one->info = NULL;
		new_one->ivex = m;
		new_one->jvex = n;
		new_one->ilink = G.adjmulist[m].firstedge;
		G.adjmulist[m].firstedge = new_one;
		new_one->jlink = G.adjmulist[n].firstedge;
		G.adjmulist[n].firstedge = new_one;
	}
}

void DestroyGraph(AMLGraph &G)							//信息部分这里并没有所以就没有指针的free
{
	for(int i =0;i<G.vexnum;i++)
		DeleteVex(G,G.adjmulist[i].data);
}

VexType &GetVex(AMLGraph G,int v)								//返回v的值
{
	if(v<0 || v>=G.vexnum)
		exit(1);
	return G.adjmulist[v].data;
}

void PutVex(AMLGraph &G,VexType v,VexType value)							//对v赋值value
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	strcpy(G.adjmulist[k].data,value);
}

int FirstAdjVex(AMLGraph G,VexType v)						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空
{
	int k = LocateVex(G,v);
	if(k<0)
		return -1;
	if(G.adjmulist[k].firstedge)
	{
		if(G.adjmulist[k].firstedge->ivex!=k)				//需判断节点中的i,j哪一个是k
			return G.adjmulist[k].firstedge->ivex;
		else
			return G.adjmulist[k].firstedge->jvex;
	}
	else
		return -1;
}

int NextAdjVex(AMLGraph G,VexType v,VexType w)					//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	EBox *p = G.adjmulist[m].firstedge;
	while(p)									//现在要找到一个 弧 的一个点为m 一个为n  但是在寻找的过程中会有几种情况出现
	{
		if(p->ivex==m && p->jvex!=n)			//节点肯定与m,n中的一个相同（并未找到（两组情况）） 或者 是全相同（找到）
			p = p->ilink;
		else if(p->jvex==m && p->ivex!=n)
			p = p->jlink;
		else								//找到
			break;
	}
	//下面两个if很容易理解  是结构体的定义造成的，但很难避免掉 毕竟一个无向图的节点可能出现在两个顶点的单链表中
	if(p&&p->ivex==m&&p->jvex==n)
	{
		p = p->ilink;
		if(p&&p->ivex==m)
			return p->jvex;
		else if(p&&p->jvex==m)
			return p->ivex;
		else
			return -1;
	}
	if(p&&p->jvex==m&&p->ivex==n)
	{
		p = p->jlink;
		if(p&&p->ivex)
			return p->jvex;
		else if(p&&p->jvex==m)
			return p->ivex;
		else
			return -1;
	}
	return -1;
}
		
void InsertVex(AMLGraph &G,VexType v)						//	在图G中新增顶点v			
{
	strcpy(G.adjmulist[G.vexnum].data,v);
	G.adjmulist[G.vexnum].firstedge = NULL;
	G.vexnum++;
}

void DeleteVex(AMLGraph &G,VexType v)							//删除G中顶点v及其相关弧						
{
	int m = LocateVex(G,v);
	if(m<0)
		return;
	/*int n,i;															//这是我自己写的 是要从被删顶点开始 一条条的删除 但是书上的更简洁
	EBox *p = G.adjmulist[m].firstedge;
	while(p)
	{
		if(p->ivex==m)
		{
			n = p->jvex;
			p = p->jlink;
		}
		else
		{
			n = p->ivex;
			p = p->ilink;
		}
		DeleteArc(G,v,G.adjmulist[n].data);
	}	*/
	VexType temp;	
	EBox *p;
	int i;
	for(i=0;i<G.vexnum;i++)							//这个循环很容易理解 就是利用了删除边的函数  但是这里曾出现过很严重的问题
	{												//问题就是这个循环是v与每一个其他点组成的边 但这条边不一定存在 这就导致了潜在的问题
		if(i==m)									//解决方法就是225行的一个判断  主要问题是自己写程序时候的粗心大马哈  怎么能不注意细节？
			continue;
		DeleteArc(G,v,G.adjmulist[i].data);
	}	


	for(i=m;i<G.vexnum-1;i++)						//名字删除
	{
		G.adjmulist[i] = G.adjmulist[i+1];
	}
	G.vexnum--;
	for(i=0;i<G.vexnum;i++)							//每一个下标超过k的都要减一  这个for循环是我自己写的 较下面的明显复杂冗余
	{													//对每个点都询问一遍 之后还要i,j都判断一遍
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex==i)
			{
				if(p->ivex>m)
					p->ivex--;
				if(p->jvex>m)
					p->jvex--;
				p = p->ilink;
			}
			else if(p->jvex==i)
			{
				if(p->ivex>m)
					p->ivex--;
				if(p->jvex>m)
					p->jvex--;
				p = p->jlink;
			}
		}
	}
	/*for(i=m;i<G.vexnum;i++)					//这个循环与上面一个循环类似 但更高明   这里i是从m开始的
	{											
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex>i)							//每个if都只是对一个数（i或j）处理  因为是从m开始的 如果另一个也大于m 那之后	
			{										//循环依旧会回到这个点 对其进行减一操作
				p->ivex--;
				p = p->ilink;
			}
			else
			{
				p->jvex--;
				p = p->jlink;
			}
		}
	}*/
}

void InsertArc(AMLGraph &G,VexType v,VexType w)							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	EBox *new_one = (EBox*)malloc(sizeof(EBox));
	new_one->mark = unvisited;
	new_one->info = NULL;
	new_one->ivex = m;
	new_one->jvex = n;
	new_one->ilink = G.adjmulist[m].firstedge;
	G.adjmulist[m].firstedge = new_one;
	new_one->jlink = G.adjmulist[n].firstedge;
	G.adjmulist[n].firstedge = new_one;
	G.arcnum++;
}

void DeleteArc(AMLGraph &G,VexType v,VexType w)							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	if(m<0 || n<0)
		return;
	EBox *p = G.adjmulist[m].firstedge;				//先从顶点m里找这条弧  把该改的指针域全改掉  但不释放节点
	EBox *temp;
	if(p && p->jvex==n)									//如果是顶点的第一个节点 且 ivex==m 
		G.adjmulist[m].firstedge = p->ilink;
	else if(p&&p->ivex==n)								//如果是顶点的第一个节点 且 jvex==m 
		G.adjmulist[m].firstedge = p->jlink;
	else												//不是第一个
	{
		while(p)
		{
			if(p->ivex==m && p->jvex!=n)
			{
				temp = p;
				p = p->ilink;
			}
			else if(p->jvex==m && p->ivex!=n)
			{
				temp = p;
				p = p->jlink;
			}
			else
				break;
		}									//找到表示该弧的节点
		if(!p)															//我草！！！！！问题就在这里！！！！！！！没有这句话 没有找到对应的弧当然就不能进行下去！！！
			return;
		if(temp->ivex==m)					//开始修改链域   需要考虑m、n哪个是顶点 那个是另一个
		{
			
			if(p->ivex==m)
				temp->ilink = p->ilink;
			else if(p->jvex==m)
				temp->ilink = p->jlink;
		}
		else
		{
			
			if(p->ivex==m)
				temp->jlink = p->ilink;
			else if(p->jvex==m)
				temp->jlink = p->jlink;
		}
		
	}
	
	//从另一个顶点开始寻找这条弧（之前不删正是因为那之后还要修改另一个顶点的链域  这里就可以删了）
	p = G.adjmulist[n].firstedge;					//与上面的过程大致一致
	if(p && p->jvex==m)
	{
		G.adjmulist[n].firstedge = p->ilink;
		if(p->info)										//开始删除弧节点
			free(p->info);
		free(p);
	}
	else if(p&&p->ivex==m)
	{
		G.adjmulist[n].firstedge = p->jlink;
		if(p->info)
			free(p->info);
		free(p);
	}
	else
	{
		while(p)
		{
			if(p->ivex==n && p->jvex!=m)
			{
				temp = p;
				p = p->ilink;
			}
			else if(p->jvex==n && p->ivex!=m)
			{
				temp = p;
				p = p->jlink;
			}
			else
				break;
		}
		if(temp->ivex==n)
		{
			if(p->ivex==n)
				temp->ilink = p->ilink;
			else
				temp->ilink = p->jlink;
			if(p->info)
				free(p->info);
			free(p);
		}
		else
		{
			if(p->ivex==n)
				temp->jlink = p->ilink;
			else
				temp->jlink = p->jlink;
			if(p->info)
				free(p->info);
			free(p);
		}
	}
	G.arcnum--;
}

int visit[MAX_VEX_NUM];
void Visitfun(VexType v)
{
	printf("%s ",v);
}
void DFS(AMLGraph G,int v)									//从第v个顶点出发递归遍历树	
{
	visit[v] = visited;
	Visitfun(G.adjmulist[v].data);
	EBox *p = G.adjmulist[v].firstedge;
	int i;
	for(i=FirstAdjVex(G,G.adjmulist[v].data);i&&p;i=NextAdjVex(G,G.adjmulist[v].data,G.adjmulist[i].data))
	{
		if(p->mark==unvisited)
		{
			p->mark = visited;
			if(!visit[i])
				DFS(G,i);
		}
		if(p->ivex == v)
			p = p->ilink;
		else if(p->jvex==v)
			p = p->jlink;
	}
}
	
void DFSTraverse(AMLGraph G,void (*Visitfun)(VexType))							//	进行深度优先搜索			
{
	MarkInitial(G);
	int i;
	for(i=0;i<G.vexnum;i++)
		visit[i]=0;
	for(i=0;i<G.vexnum;i++)
		if(!visit[i])
			DFS(G,i);
	puts("");

}

//这里出现的两种是否被访问的mark着实让人头疼  需要谨慎处理
void BFSTraverse(AMLGraph G,void (*Visitfun)(VexType))							//	进行广度优先搜索
{
	MarkInitial(G);
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	EBox *p;
	int i,temp;
	for(i=0;i<G.vexnum;i++)
		visit[i]=0;
	for(i=0;i<G.vexnum;i++)
	{
		if(visit[i]==visited)
			continue;
		en_queue(Queue,i);
		while(!is_empty(Queue))
		{
			out_queue(Queue,temp);
			if(visit[temp]==visited)
				continue;
			visit[temp] = visited;
			Visitfun(G.adjmulist[temp].data);
			p = G.adjmulist[temp].firstedge;
			while(p)
			{
				if(p->mark==unvisited)
				{
					p->mark = visited;
					if(p->ivex == temp)
						en_queue(Queue,p->jvex);
					else if(p->jvex==temp)
						en_queue(Queue,p->ivex);
				}
				if(p->ivex == temp)
					p = p->ilink;
				else if(p->jvex==temp)
					p = p->jlink;
			}
		}
	}
}

void MarkInitial(AMLGraph G)							//将所有被之前访问标记过的节点初始化 以便于下一次访问
{
	EBox *p;
	for(int i=0;i<G.vexnum;i++)
	{
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			p->mark=unvisited;
			if(p->ivex==i)
				p = p->ilink;
			else if(p->jvex==i)
				p = p->jlink;
		}
	}
}

void Display(AMLGraph G)								//  输出邻接矩阵
{
	printf("This is %d vexes and %d arc\n",G.vexnum,G.arcnum);
	int i;
	EBox *p;
	for(i=0;i<G.vexnum;i++)
		printf(" %s ",G.adjmulist[i].data);
	puts("");
	MarkInitial(G);
	for(i=0;i<G.vexnum;i++)
	{
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex==i)
			{
				if(p->mark==unvisited)
				{
					printf(" %s -- %s  ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					if(p->info)
						printf("%s",p->info);
					p->mark = visited;
				}
				p = p->ilink;
			}
			else if(p->jvex==i)
			{
				if(p->mark==unvisited)
				{
					printf(" %s -- %s  ",G.adjmulist[i].data,G.adjmulist[p->ivex].data);
					if(p->info)
						printf("%s",p->info);
					p->mark = visited;
				}
				p = p->jlink;
			}
		}puts("");
	}
}
