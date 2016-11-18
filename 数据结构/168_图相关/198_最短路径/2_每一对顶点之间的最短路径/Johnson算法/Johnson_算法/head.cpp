#include "head.h"
#include "queue.h"

int LocateVex(ALGraph G,VexType u)									//若图G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息
{
	for(int i=0;i<G.vexnum;i++)
		if(!strcmp(G.vertices[i].data,u))
			return i;
	return -1;
}
//不同类型的图出现在同一个程序就需要考虑在删除的时候是否会多删除一次  在添加的时候就需要多添加一次
Edge* CreateGraph(ALGraph &G)							//一个函数构造四种图
{
	/*printf("Which kind of graph do you want to create?\n0：有向图	1：有向网\n2：无向图	3：无向网\n");
	scanf("%d",&G.kind);
	printf("How many vexes and arcs?\n");						//边和顶点数
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("Input the name of vexes : \n");													//顶点名字 
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	VexType v1,v2;
	int w;
	if(G.kind==1||G.kind==3)									//分图的种类进行输入边（是否包含权值）
		printf("Enter the two vexes (composed an arc) and its weight one after another :");
	else
		printf("Enter the two vexes of an arc one after another: ");
	int m,n;
	ArcPoint new_one;
	for(i=0;i<G.arcnum;i++)										//边的输入
	{
		if(G.kind==1||G.kind==3)
			scanf("%s%s%d",v1,v2,&w);
		else
			scanf("%s%s",v1,v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		new_one = (ArcPoint)malloc(sizeof(ArcNode));
		new_one->adjvex = n;
		new_one->info = NULL;
		if(G.kind==1||G.kind==3)
		{
			new_one->info = (int *)malloc(sizeof(int));
			*(new_one->info) = w;
		}
		new_one->nextarc = G.vertices[m].firstarc;								//这里貌似插在表头是在合适不过的了 不然会很烦或不好操作 因为表头是不同类型
		G.vertices[m].firstarc = new_one;
		if(G.kind>=2)											//无向图（网）需要两个顶点都拥有这个弧（边）
		{
			new_one = (ArcPoint)malloc(sizeof(ArcNode));
			new_one->adjvex = m;
			new_one->info = NULL;
			if(G.kind == 3)
			{
				new_one->info = (int *)malloc(sizeof(int));
				*new_one->info = w;
			}
			new_one->nextarc = G.vertices[n].firstarc;								
			G.vertices[n].firstarc = new_one;
		}
	}*/
	Edge *edge;
	char filename[20];
	strcpy(filename,"hehe.txt");
	FILE *p;
	if(!(p=fopen(filename,"r")))
		exit(1);
	fscanf(p,"%d%d%d",&G.kind,&G.vexnum,&G.arcnum);
	edge = (Edge*)malloc(sizeof(Edge)*100);
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		fscanf(p,"%s",G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	VexType v1,v2;
	int m,n,w;
	ArcPoint new_one;
	for(i=0;i<G.arcnum;i++)
	{
		fscanf(p,"%s%s%d",v1,v2,&w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		edge[i].m = m;
		edge[i].n = n;
		edge[i].w = w;
		new_one = (ArcPoint)malloc(sizeof(ArcNode));
		new_one->adjvex = n;
		new_one->info = (int *)malloc(sizeof(int));
		*new_one->info = w;
		new_one->nextarc = G.vertices[m].firstarc;								//这里貌似插在表头是在合适不过的了 不然会很烦或不好操作 因为表头是不同类型
		G.vertices[m].firstarc = new_one;
	}
	return edge;
}

void DestroyGraph(ALGraph &G)								//销毁
{
	if(G.vexnum<1)
		return;
	ArcPoint p,temp;
	int i;
	for(i=0;i<G.vexnum;i++)								//每个顶点都有一个链表 所以逐个删
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			temp = p;
			p = temp->nextarc;
			if(G.kind==1||G.kind==3)								//如果有信息 则也要记得删掉
				free(temp->info);
			free(temp);
		}
		G.vertices[i].firstarc = NULL;
	}
	G.arcnum = G.vexnum = 0;
}

VexType &GetVex(ALGraph G,int v)								//返回v的值
{
	if(v<0 || v>=G.vexnum)
		exit(1);
	return G.vertices[v].data;
}

void PutVex(ALGraph &G,VexType v,VexType value)						//对v赋值value
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	strcpy(G.vertices[k].data,value);
}

int FirstAdjVex(ALGraph G,VexType v)						//	返回v的第一个邻接顶点  若顶点在F中没有邻接顶点 则返回空
{
	int k = LocateVex(G,v);
	if(k<0)
		return -1;
	if(G.vertices[k].firstarc)
		return G.vertices[k].firstarc->adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G,VexType v,VexType w)						//	返回v的下一个邻接顶点 若w是v的最后一个邻接顶点 则返回空
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	ArcPoint p = G.vertices[m].firstarc;
	while(p && p->adjvex!=n)
		p = p->nextarc;
	if(p && p->nextarc)
		return p->nextarc->adjvex;
	else
		return -1;
}
		
void InsertVex(ALGraph &G,VexType v)						//	在图G中新增顶点v			
{
	strcpy(G.vertices[G.vexnum].data,v);
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
}
	
void DeleteVex(ALGraph &G,VexType v)							//删除G中顶点v及其相关弧						
{
	int k = LocateVex(G,v);
	if(k<0)
		return;
	int i;
	ArcPoint temp;
	ArcPoint p = G.vertices[k].firstarc;
	while(p)											//删除这个顶点所连接的边（以这个顶点为tail）
	{
		temp = p;
		p = temp->nextarc;
		if(G.kind==1 || G.kind==3)								//如果有信息 则也要记得删掉
			free(temp->info);
		free(temp);
		G.arcnum--;							//自己写的时候居然忘掉这一步了
	}
	for(i=k;i<G.vexnum-1;i++)							//名字数组也要删除
		G.vertices[i] = G.vertices[i+1];
	G.vexnum--;
	for(i=0;i<G.vexnum;i++)								//从每个顶点出发寻找与被删节点相关的边（弧）
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(p->adjvex==k)					//找到
			{
				if(p == G.vertices[i].firstarc)				//由于头结点和弧（边）节点是不同类型 所以分开讨论
				{
					G.vertices[i].firstarc = p->nextarc;
					if(G.kind==1 || G.kind==3)
						free(p->info);
					free(p);
					if(G.kind<=1)								//必须判断是否有向 否则会被删掉第二次 因为第一次已经在删除整个单链表的时候处理过了
						G.arcnum--;
				}
				else
				{
					temp->nextarc = p->nextarc;
					if(G.kind==1 || G.kind==3)
						free(p->info);
					free(p);
					if(G.kind<=1)
						G.arcnum--;
				}
				break;
			}
			else												//未找到  需要保存previous节点 以便于删除操作
			{	
				//*********************************
				if(p->adjvex>k)								//这一步尤其重要  自己写的时候被我忽视掉了*********************如果出错了就很难找出来了
					p->adjvex--;
				//************************************
				temp = p;
				p = p->nextarc;
			}
		}
	}
}

/*void InsertArc(ALGraph &G,VexType v,VexType w)							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
{
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	int weight;
	G.arcnum++;													//老是会忘掉在弧的个数上加一
	if(G.kind==1||G.kind==3)
	{
		printf("Input the weight of the arc:\n");
		scanf("%d",&weight);
	}
	ArcPoint new_one;
	new_one = (ArcPoint)malloc(sizeof(ArcNode));
	new_one->adjvex = n;
	new_one->info = NULL;
	if(G.kind==1||G.kind==3)
	{
		new_one->info = (int *)malloc(sizeof(int));
		*(new_one->info) = weight;
	}
	new_one->nextarc = G.vertices[m].firstarc;								//这里貌似插在表头是在合适不过的了 不然会很烦或不好操作 因为表头是不同类型
	G.vertices[m].firstarc = new_one;
	if(G.kind>=2)
	{
		new_one = (ArcPoint)malloc(sizeof(ArcNode));
		new_one->adjvex = m;
		new_one->info = NULL;
		if(G.kind == 3)
		{
			new_one->info = (int *)malloc(sizeof(int));
			*new_one->info = weight;
		}
		new_one->nextarc = G.vertices[n].firstarc;								
		G.vertices[n].firstarc = new_one;
	}
}*/
void InsertArc(ALGraph &G,int m,int n,int w,Edge *&edge)							//	在G中增添弧	<v,w>,若G是无向的 则还增添对称弧<w,v>
{
	edge[G.arcnum].m = m;
	edge[G.arcnum].n = n;
	edge[G.arcnum].w = w;
	G.arcnum++;													//老是会忘掉在弧的个数上加一
	ArcPoint new_one;
	new_one = (ArcPoint)malloc(sizeof(ArcNode));
	new_one->adjvex = n;
	new_one->info = (int *)malloc(sizeof(int));
	*(new_one->info) = w;
	new_one->nextarc = G.vertices[m].firstarc;								//这里貌似插在表头是在合适不过的了 不然会很烦或不好操作 因为表头是不同类型
	G.vertices[m].firstarc = new_one;
}

void DeleteArc(ALGraph &G,VexType v,VexType w)							//	在G中删除弧<v,w> 若G是无向的 则还删除对称弧<w,v>	
{
	G.arcnum--;
	int m = LocateVex(G,v);
	int n = LocateVex(G,w);
	ArcPoint temp;
	ArcPoint p = G.vertices[m].firstarc;
/*	while(p)
	{
		if(p->adjvex==n)
		{
			if(p==G.vertices[m].firstarc)
			{
				G.vertices[m].firstarc = p->nextarc;
				if(G.kind>=2)
					free(p->info);
				free(p);
			}
			else
			{
				temp->nextarc = p->nextarc;
				if(G.kind>=2)
					free(p->info);
				free(p);
			}
		}
		else
		{
			temp = p;
			p = p->nextarc;
		}
	}
	if(G.kind == 1||G.kind==3)
	{
		ArcPoint p = G.vertices[n].firstarc;
	while(p)
	{
		if(p->adjvex==m)
		{
			if(p==G.vertices[n].firstarc)
			{
				G.vertices[n].firstarc = p->nextarc;
				if(G.kind>=2)
					free(p->info);
				free(p);
			}
			else
			{
				temp->nextarc = p->nextarc;
				if(G.kind>=2)
					free(p->info);
				free(p);
			}
		}
		else
		{
			temp = p;
			p = p->nextarc;
		}
	}
	}*/
	while(p && p->adjvex!=n)
	{
		temp = p;
		p = p->nextarc;
	}
	
	if(p&&p->adjvex==n)													//删边（弧）的话需要先找到然后删除之后考虑是否无向（删除两次 但是边数减1）
	{
		if(p==G.vertices[m].firstarc)
			G.vertices[m].firstarc = p->nextarc;
		else
			temp->nextarc = p->nextarc;
		if(G.kind==1||G.kind==3)
			free(p->info);
		free(p);
	}
//	printf("Where\n");
	if(G.kind>=2)							//如果是无向图（网）  那么需要从另一个点也找一条这样的边删去
	{
		p = G.vertices[n].firstarc;
		while(p && p->adjvex!=m)
		{
			temp = p;
			p = p->nextarc;
		}
		if(p&&p->adjvex==m)
		{
			if(p==G.vertices[n].firstarc)
				G.vertices[n].firstarc = p->nextarc;
			else
				temp->nextarc = p->nextarc;
			if(G.kind>=2)
				free(temp->info);
			free(temp);
		}
	}
}

int visit[MAX_VEX_NUM];
void Visitfun(VexType v)
{
	printf("%s ",v);
}
void DFS(ALGraph G,int v)									//从第v个顶点出发递归遍历树	
{
	Visitfun(G.vertices[v].data);
	visit[v] = 1;
	ArcPoint p;
	for(p = G.vertices[v].firstarc;p;p=p->nextarc)
		if(!visit[p->adjvex])
			DFS(G,p->adjvex);
}

void DFSTraverse(ALGraph G,void (*Visitfun)(VexType))							//	进行深度优先搜索			
{
	int i;
	for(i=0;i<G.vexnum;i++)
		visit[i]=0;
	for(i=0;i<G.vexnum;i++)
		if(!visit[i])
			DFS(G,i);
	puts("");
}

void BFSTraverse(ALGraph G,void (*Visitfun)(VexType))							//	进行广度优先搜索
{
	pss Queue = (pss)malloc(sizeof(ss));
	init(Queue);
	int i,temp;
	ArcPoint p;
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
			Visitfun(G.vertices[temp].data);
			for(p=G.vertices[temp].firstarc;p;p=p->nextarc)
				if(!visit[p->adjvex])
				{
					en_queue(Queue,p->adjvex);
					visit[p->adjvex] = 1;
				}
		}
	}
	puts("");
}

void Display(ALGraph G)								//  输出邻接矩阵
{
	char s[20],s1[10];
	switch(G.kind)
	{
	case DG:
		strcpy(s,"Direction Graph\0");					//这里数组越界了 导致我花了好久菜才找出问题在哪里**** 问题虽小 但也很严重
		strcpy(s1,"Arc\0");
		break;
	case DN:
		strcpy(s,"Direction Network\0");
		strcpy(s1,"Edge\0");
		break;
	case UDG:
		strcpy(s,"Undirection Graph\0");
		strcpy(s1,"Arc\0");
		break;
	case UDN:
		strcpy(s,"Undirection Network\0");
		strcpy(s1,"Edge\0");
		break;
	}
	printf("This is a %s with %d vexes and %d %s\n",s,G.vexnum,G.arcnum,s1);
	int i;
	for(i=0;i<G.vexnum;i++)
		printf(" %s ",G.vertices[i].data);
	puts("");
	ArcPoint p;
	for(i=0;i<G.vexnum;i++)				//将整个存储结构输出出来
	{
		p = G.vertices[i].firstarc;
		while(p)																	//一个节点的单链表占一行
		{
			if(G.kind<=1)							//是有向图（网），那么直接输出
			{
				printf("%s -> %s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN)
					printf("%d   ",*(p->info));
			}
			else
			{
				if(i<p->adjvex)						//是无向图（网），则避免重复输出
				{
					printf("%s -- %s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==UDN)
						printf("%d",*(p->info));
				}
			}
			p = p->nextarc;
		}
		puts("");
	}
}
