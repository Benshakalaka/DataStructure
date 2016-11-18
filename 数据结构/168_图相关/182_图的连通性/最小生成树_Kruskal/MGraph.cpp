#include "MGraph.h"
#include "queue.h"


/*bool CreateGraph_UDN(MGraph &G)								//无向网
{
	int i,j;
	VexType v1,v2;
	scanf("%d%d",&G.vexnum,&G.arcnum);
	for(i=0;i<G.vexnum;i++)
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j].adj = INFINITY;
	int k,w;
	for(k=0;k<G.arcnum;k++)
	{
		scanf("%s",v1);
		getchar();
		scanf("%s",v2);
		getchar();
		scanf("%d",&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = G.arcs[j][i].adj = w;
	}
	return true;
}*/

void CreateGraph_UDN(MGraph &G)
{
	FILE *p;
	VexType v1,v2;
	if(!(p=fopen("hehe.txt","r")))
		exit(1);
	fscanf(p,"%d",&G.kind);
	fscanf(p,"%d%d",&G.vexnum,&G.arcnum);
	int i,m,n,w;
	for(i=0;i<G.vexnum;i++)
		fscanf(p,"%s",G.vexs[i]);
	for(i=0;i<G.vexnum;i++)
		for(int j=0;j<G.vexnum;j++)
			G.arcs[i][j].adj = INFINITY;
	for(i=0;i<G.arcnum;i++)
	{
		fscanf(p,"%s%s%d",v1,v2,&w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = G.arcs[n][m].adj = w;
	}
}

void DestroyGraph(MGraph &G)								//信息部分这里并没有所以就没有指针的free
{
	G.vexnum = G.arcnum = 0;
}

int LocateVex(MGraph G,VexType u)							//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息
{
	for(int i=0;i<G.vexnum && strcmp(G.vexs[i],u)!=0;i++);		
	if(i>=G.vexnum)
		return -1;
	return i;
}
			
VexType &GetVex(MGraph G,int v)								//返回v的值		这里如果不用引用的话会出现这样的错误：error C2090: function returns array
{	
	if(v<0 || v>=G.vexnum)
		exit(1);
	return G.vexs[v];
}

//这函数的形参要用到引用或指针 否则就是传值调用 并不能起到作用
void PutVex(MGraph &G,VexType v,VexType value)							//对v赋值value
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	strcpy(G.vexs[k],value);
}

//这个函数和下面一个函数是为了遍历的方便
int FirstAdjVex(MGraph G,VexType v)						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空
{
	int k = LocateVex(G,v);
	if(k<0)
		return -1;
	int j = 0;
	if(G.kind==DN || G.kind==UDN)
		j = INFINITY;
	for(int i=0;i<G.vexnum;i++)
		if(G.arcs[k][i].adj != j)
			return i;
	return -1;
}

int NextAdjVex(MGraph G,VexType v,VexType w)						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	if(m<0||n<0)
		return -1;
	int j = 0;
	if(G.kind==DN || G.kind==UDN)
		j = INFINITY;
	for(int i=n+1;i<G.vexnum;i++)
		if(G.arcs[m][i].adj != j)
			return i;
	return -1;
}

void InsertVex(MGraph &G,VexType v)						//	在图G中新增顶点v			
{
	strcpy(G.vexs[G.vexnum],v);
	G.vexnum += 1;													//顶点个数加一
	int i;
	for(i=0;i<G.vexnum;i++)									//新增一个点后看一下CreateGraph函数应该增加些什么 初始化是必须的
	{
		if(G.kind == DG || G.kind == UDG)						//如果是图
		{
			G.arcs[G.vexnum-1][i].adj = 0;
			G.arcs[i][G.vexnum-1].adj = 0;
		}
		else														//如果是网
		{
			G.arcs[G.vexnum-1][i].adj = INFINITY;
			G.arcs[i][G.vexnum-1].adj = INFINITY;
		}
	}
}

void DeleteVex(MGraph &G,VexType v)							//删除G中顶点v及其相关弧						
{																//删除一个顶点要考虑很多 尤其在这种有四种图的情况下
	int k = LocateVex(G,v);								//首先找到这个点
	if(k<0)		
		return;
	int i,j;
	j = 0;
	if(G.kind == DN || G.kind == UDN)					//如果是网的话 判定就有区别 （图的不连通用0表示 网用 无穷大表示）
		j = INFINITY;
	for(i=0;i<G.vexnum;i++)								//如果有弧 需要改变弧的总数 （可能是有向的就需要横纵都查一遍 无向的话只要横或者纵查一遍 ）
	{
		if(G.arcs[i][k].adj != j)
			G.arcnum--;
	}
	if(G.kind == DN || G.kind == DG)					//如果是有向 那么仍需纵向遍历一遍
		for(i=0;i<G.vexnum;i++)
			if(G.arcs[k][i].adj != j)
				G.arcnum--;
	for(i=k;i<G.vexnum-1;i++)							//删除的顶点之后的组都向前移动一个位置+顶点向量数组也要去掉这个顶点
	{
		strcpy(G.vexs[i],G.vexs[i+1]);
		for(j=0;j<G.vexnum;j++)
			G.arcs[j][i] = G.arcs[j][i+1];
	}
	for(i=k;i<G.vexnum-1;i++)							//在k,k+1，...行往前移的时候 如果同时移动k,k+1...列 容易出错 所以分开处理
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j] = G.arcs[i+1][j];
	G.vexnum--;
}


void InsertArc(MGraph &G,VexType v,VexType w)							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	if(m<0||n<0)
		return;
	if(G.kind==DG || G.kind==UDG)					//插入一条边在矩阵存储（非压缩矩阵）中很容易
		G.arcs[m][n].adj = 1;
	else
	{
		int weight;
		scanf("%d",&weight);
		G.arcs[m][n].adj = weight;
	}
	if(G.kind==UDG||G.kind==UDN)
		G.arcs[n][m].adj = G.arcs[m][n].adj;
	G.arcnum++;
}

void DeleteArc(MGraph &G,VexType v,VexType w)						//在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	if(m<0||n<0)
		return;
	int j=0;
	if(G.kind==DN ||G.kind==UDN)
		j = INFINITY;
	G.arcs[m][n].adj = j;
	if(G.kind==UDG||G.kind==UDN)
		G.arcs[n][m].adj=G.arcs[m][n].adj;
	G.arcnum--;
}

void Visitfun(VexType v)
{
	printf("%s ",v);
}
int visit[MAX_VERTEX_NUM];
void DFS(MGraph G,int v)
{	
	Visitfun(G.vexs[v]);
	visit[v] = 1;
	for(int i=FirstAdjVex(G,G.vexs[v]);i>=0;i=NextAdjVex(G,G.vexs[v],G.vexs[i]))		//深度遍历相当于先序（中、后）遍历  
		if(!visit[i])
			DFS(G,i);
}


void DFSTraverse(MGraph G,void (*Visitfun)(VexType))							//	进行深度优先搜索			
{
	int i;
	for(i=0;i<G.vexnum;i++ )								//遍历的时候需要判定这个点是否已经被遍历过 因为这是图不是树。。
		visit[i] = 0;
	for(i=0;i<G.vexnum;i++)
		if(!visit[i])
			DFS(G,i);
	puts("");
}

void BFSTraverse(MGraph G,void (*Visitfun)(VexType))							//	进行广度优先搜索
{
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	int temp = 0,i,j;
	for(i=0;i<G.vexnum;i++ )								//遍历的时候需要判定这个点是否已经被遍历过 因为这是图不是树。。
		visit[i] = 0;
	for(i=0;i<G.vexnum;i++)
	{
		if(!visit[i])								//广度遍历相当于树的层序遍历	利用队列的先进先出  有秩序的遍历
		{
			visit[i] = 1;
			en_queue(Queue,i);
			while(!is_empty(Queue))
			{
				out_queue(Queue,temp);
				Visitfun(G.vexs[temp]);
				for(j=FirstAdjVex(G,G.vexs[temp]);j>=0;j=NextAdjVex(G,G.vexs[temp],G.vexs[j]))
					if(!visit[j])
					{
						visit[j] = 1;
						en_queue(Queue,j);
					}
			}
		}
	}
	puts("");
}

void Display(MGraph G)
{
	char s[10],s1[10];
	switch(G.kind)								//只是为了下面的一句话。。。
	{
	case DG:
		strcpy(s,"有向图\0");
		strcpy(s1,"弧\0");
		break;
	case DN:
		strcpy(s,"有向网\0");
		strcpy(s1,"边\0");
		break;
	case UDG:
		strcpy(s,"无向图\0");
		strcpy(s1,"弧\0");
		break;
	case UDN:
		strcpy(s,"无向网\0");
		strcpy(s1,"边\0");
		break;
	}
	printf("This is a %s with %d vexes and %d %s\n",s,G.vexnum,G.arcnum,s1);
	int i;
	for(i=0;i<G.vexnum;i++)
		printf(" %s ",G.vexs[i]);
	puts("");
	int j;
	for(i=0;i<G.vexnum;i++)						//由于矩阵的存储方式十分简单（并未有节省空间的打算） 所以输出的时候也不必考虑什么
	{
		for(j=0;j<G.vexnum;j++)
			printf(" %d ",G.arcs[i][j]);
		puts("");
	}
}
