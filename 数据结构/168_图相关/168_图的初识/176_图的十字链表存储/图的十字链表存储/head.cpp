#include "head.h"
#include "queue.h"

int LocateVex(OLGraph G,VexType u)									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(!strcmp(G.xlist[i].data,u))
			return i;
	return -1;
}

void CreateGraph(OLGraph &G)							//构造有向图
{
	printf("How many vexes and arcs?\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("the name of %d vexes:\n",G.vexnum);
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.xlist[i].data);
		G.xlist[i].firstin=G.xlist[i].firstout= NULL;
	}
	VexType v1,v2;
	int m,n;
	ArcBox *new_one;
	printf("Input the two vexes of one arc ono by one:\n");
	for(i=0;i<G.arcnum;i++)							//根据弧来建立节点ArcBox
	{
		scanf("%s%s",v1,v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		new_one = (ArcBox *)malloc(sizeof(ArcBox));
		new_one->tailvex = m;												//由于弧节点中存了两个顶点序号和两个指针域
		new_one->headvex = n;
		new_one->tlink = G.xlist[m].firstout;
		G.xlist[m].firstout = new_one;
		new_one->hlink = G.xlist[n].firstin;
		G.xlist[n].firstin = new_one;
		new_one->info = NULL;
	}
}

void DestroyGraph(OLGraph &G)	
{
	int i;
	ArcBox *p;
	for(i=0;i<G.vexnum;i++)
	{
		p = G.xlist[i].firstout;					//只处理每个顶点的出 （当然也可以只处理每个节点的入）
		while(p)
		{
			G.xlist[i].firstout = p->tlink;							//每次删除第一个 避免声明一个新的指针
			if(p->info)
				free(p->info);
			free(p);
			p = G.xlist[i].firstout;
		}
	}
}

VexType &GetVex(OLGraph G,int v)								//返回v的值
{
	if(v<0 || v>=G.vexnum)
		exit(1);
	return G.xlist[v].data;
}

void PutVex(OLGraph &G,VexType v,VexType value)						//对v赋值value
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	strcpy(G.xlist[k].data,value);
}

int FirstAdjVex(OLGraph G,VexType v)						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空
{
	int k = LocateVex(G,v);
	if(k<0)
		return -1;
	if(G.xlist[k].firstout)
		return G.xlist[k].firstout->headvex;
	else
		return -1;
}

int NextAdjVex(OLGraph G,VexType v,VexType w)						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	ArcBox *p = G.xlist[m].firstout;
	while(p && p->headvex!=n)
		p = p->tlink;
	if(p && p->tlink)
		return p->tlink->headvex;
	else
		return -1;
}
		
void InsertVex(OLGraph &G,VexType v)						//	在图G中新增顶点v			
{
	strcpy(G.xlist[G.vexnum].data,v);
	G.xlist[G.vexnum].firstin = G.xlist[G.vexnum].firstout = NULL;
	G.vexnum++;
}

void DeleteVex(OLGraph &G,VexType v)							//删除G中顶点v及其相关弧						
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	ArcBox *p = G.xlist[k].firstout;
	ArcBox *q,*temp;
	while(p)												//从要删除的节点的出考虑  
	{
		G.arcnum--;
		G.xlist[k].firstout = p->tlink;
		q = G.xlist[p->headvex].firstin;			//十字链表较为复杂 所以在删除一个节点时候需要考虑里面存在前和后的关系
		while(q&&q->tailvex!=k)
		{
			temp = q;
			q = q->hlink;
		}										//找到弧尾是k的节点
		if(q == G.xlist[p->headvex].firstin)
			G.xlist[p->headvex].firstin = p->hlink;
		else
			temp->hlink = p->hlink;
		if(p->info)
			free(p->info);
		free(p);
		p = G.xlist[k].firstout;
	}
	p = G.xlist[k].firstin;									//从要删的节点的入 考虑   与该节点有关的弧只有两种 一种是出另一种就是入
	while(p)
	{
		G.arcnum--;
		G.xlist[k].firstin = p->hlink;
		q = G.xlist[p->tailvex].firstout;
		while(q&& q->headvex!=k)			//找到弧头是k 的节点
		{
			temp = q;
			q = q->tlink;
		}
		if(q == G.xlist[p->tailvex].firstout)
			G.xlist[p->tailvex].firstout = p->tlink;
		else
			temp->tlink = p->tlink;
		if(p->info)
			free(p->info);
		free(p);
		p = G.xlist[k].firstin;
	}
	int i;
	for(i=k;i<G.vexnum-1;i++)
		G.xlist[i] = G.xlist[i+1];
	G.vexnum--;
	for(i=0;i<G.vexnum;i++)											//删除一个顶点后，每个链表里的节点的序号大于被删节点序号的必须减小
	{
		p = G.xlist[i].firstout;
		while(p)
		{
			if(p->headvex>k)			//每个节点里有两个涉及顶点序号 都需要考虑
				p->headvex--;
			if(p->tailvex>k)
				p->tailvex--;
			p = p->tlink;
		}
	}
}

void InsertArc(OLGraph &G,VexType v,VexType w)							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	G.arcnum++;
	ArcBox *new_one;					//与Create函数中类似
	new_one = (ArcBox *)malloc(sizeof(ArcBox));
	new_one->tailvex = m;
	new_one->headvex = n;
	new_one->tlink = G.xlist[m].firstout;
	G.xlist[m].firstout = new_one;
	new_one->hlink = G.xlist[n].firstin;
	G.xlist[n].firstin = new_one;
	new_one->info = NULL;
}

void DeleteArc(OLGraph &G,VexType v,VexType w)							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	G.arcnum--;
	ArcBox *p = G.xlist[m].firstout;
	ArcBox *temp;
	while(p&&p->headvex!=n)					//找到节点（或前节点）
	{
		temp = p;
		p = p->tlink;
	}
	if(p == G.xlist[m].firstout)
		G.xlist[m].firstout = p->tlink;
	else										//这里少了个判定p这个是否存在（也就是输入是否合理）
		temp->tlink = p->tlink;
	p = G.xlist[n].firstin;
	while(p->tailvex!=m)						//由于每个顶点有出和入两条链 所以可以依据这个特点进行增删
	{
		temp = p;
		p = p->hlink;
	}
	if(p == G.xlist[n].firstin)
		G.xlist[n].firstin = p->hlink;
	else
		temp->hlink = p->hlink;
	if(p->info)
		free(p->info);
	free(p);
}

void Visitfun(VexType v)
{
	printf("%s ",v);
}
int visit[MAX_VEX_NUM];

void DFS(OLGraph G,int v)									//从第v个顶点出发递归遍历树	
{
	visit[v] = 1;
	Visitfun(G.xlist[v].data);
	ArcBox *p = G.xlist[v].firstout;
	for(;p;p=p->tlink)
		if(!visit[p->headvex])
			DFS(G,p->headvex);
}

void DFSTraverse(OLGraph G,void (*Visitfun)(VexType))							//	进行深度优先搜索			
{
	int i;
	for(i=0;i<G.vexnum;i++ )								//遍历的时候需要判定这个点是否已经被遍历过 因为这是图不是树。。
		visit[i] = 0;
	for(i=0;i<G.vexnum;i++)
		if(!visit[i])
			DFS(G,i);
	puts("");

}

void BFSTraverse(OLGraph G,void (*Visitfun)(VexType))							//	进行广度优先搜索
{
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	int i,temp;
	ArcBox *p;
	for(i=0;i<G.vexnum;i++)
		visit[i]=0;
	for(i=0;i<G.vexnum;i++)
	{
		if(visit[i])
			continue;
		en_queue(Queue,i);
		visit[i] = 1;
		while(!is_empty(Queue))
		{
			out_queue(Queue,temp);
			Visitfun(G.xlist[temp].data);
			for(p=G.xlist[temp].firstout;p;p=p->tlink)
				if(!visit[p->headvex])
				{
					en_queue(Queue,p->headvex);
					visit[p->headvex] = 1;
				}
		}
	}
}

void Display(OLGraph G)								//  输出邻接矩阵
{
	printf("This is %d vexes and %d arc\n",G.vexnum,G.arcnum);
	int i;
	for(i=0;i<G.vexnum;i++)
		printf(" %s ",G.xlist[i].data);
	puts("");
	ArcBox *p;
	for(i=0;i<G.vexnum;i++)
	{
		p = G.xlist[i].firstout;
		while(p)
		{
			printf(" %s --> %s  ",G.xlist[i].data,G.xlist[p->headvex].data);
			p = p->tlink;
		}
		puts("");
	}
}

