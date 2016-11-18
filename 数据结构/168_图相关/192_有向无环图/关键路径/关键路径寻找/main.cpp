#include <stdio.h>
#include "ALGraph.h"
#include "stack.h"

int ve[MAX_VEX_NUM];

void ToplogicalOrder(ALGraph &,ps &);			//求各顶点时间的最早发生时间ve A为拓扑序列栈在求vl时使用（从后往前）B为本函数使用的栈 用来求ve 并判断是否为拓扑有序（如果不是 则退出整个程序）
void CriticalPath(ALGraph );			//输出G的各项关键活动

int main()
{
	ALGraph G;
	CreateGraph(G);
	Display(G);
	CriticalPath(G);
	return 0;
}


void FindInDegree(ALGraph G,int *indegree)				//计算每一个顶点的度
{
	int i;
	ArcPoint p;
	for(i=0;i<G.vexnum;i++)				//因为是有向图 所以可以从每一个顶点开始遍历 并不会有重复的 
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->adjvex]++;			//所指向的顶点的入度加一
			p = p->nextarc;
		}
	}
}

void ToplogicalOrder(ALGraph &G,ps &Stack_A)			//求各顶点时间的最早发生时间ve
{			//整个过程与拓扑有序相类似  只是增加了一些变量   
	int indegree[MAX_VEX_NUM];
	int i;
	for(i=0;i<G.vexnum;i++)						//每一个入度置为零首先
		indegree[i] = 0;
	FindInDegree(G,indegree);					//先求得每一个顶点
	for(i=0;i<G.vexnum;i++)						//先将每一个最早开始时间置为零 之后通过活动的持续时间来增加
		ve[i] = 0;								//从第一个开始  第一个当然是0...
	ps Stack_B = (ps)malloc(sizeof(s));
	init(Stack_B);
	for(i=0;i<G.vexnum;i++)					
		if(!indegree[i])
			push(Stack_B,i);
	int temp;
	ArcPoint p;
	while(!empty(Stack_B))
	{
		pop(Stack_B,temp);
		push(Stack_A,temp);										//按顺序存储  之后通过Stack_A来反向访问每一个顶点求的其vl[i]
		for(p=G.vertices[temp].firstarc;p;p=p->nextarc)
		{
			indegree[p->adjvex]--;
			if(!indegree[p->adjvex])
				push(Stack_B,p->adjvex);
			if(ve[p->adjvex] < ve[temp]+(*(p->info)))			//要求一个事件最早发生时间  就需要时间最长的那一个（最早发生的含义就是 所有之前活动都完成之后这个才能开始 才算最早开始 否则再早的话就无法将之前的某个顺利完成）
				ve[p->adjvex] = ve[temp]+(*(p->info));			//所以需要等于花费时间最长的一个时间
		}
	}
	//这里的count在写的时候忘记了  其实挺重要的  用来判断是否满足拓扑  因为整个寻找关键路径的过程是建立在拓扑的基础上进行的
}

void CriticalPath(ALGraph G)						//输出G的各项关键活动
{
	ps Stack_A = (ps)malloc(sizeof(s));						//这个栈是用来到拓扑排序里去存储访问顺序的  以便于下面的反向访问
	//为什么要反向访问呢？ 因为是求最迟发生时间  如果从第一个开始的话 并不知道这个活动推迟几天是否影响整体的计划  但是从最后一个开始的话 从最后一个开始 都是按最迟在计算的 那往前访问自然存下的是最迟的
	init(Stack_A);
	ToplogicalOrder(G,Stack_A);			//得到ve  和求vl的栈
	int vl[MAX_VEX_NUM];
	int temp;
	pop(Stack_A,temp);
	int i;
	for(i=0;i<G.vexnum;i++)
		vl[i] = ve[G.vexnum-1];			//这一步尤其要说说  一开始本以为是vl[i]=ve[i]的  只是真正落实的时候发现这样根本不可行 因为ve是最早 永远是比最迟的时间短的 所以经历下面的比较的话是完全错误的  本想将vl[G.vexnum-1]=ve[G.vexnum-1];v[0,1,2,...,G.vexnum-2]=1000;的 后来看了书上写的都等于ve[G.vexnum-1]  觉得确实更好些（其实也没什么差别 只是如果活动持续时间为0 就多执行一次赋值）  因为最后一个永远是最大的 下面的比较选取适合的较小的
	ArcPoint p;
	while(!empty(Stack_A))					//栈里存了所有数 当然以空为依据
	{
		pop(Stack_A,temp);
		for(p=G.vertices[temp].firstarc;p;p=p->nextarc)			//必须跟这个点之后的每一个进行如下比较
		{
			if(vl[temp]  > vl[p->adjvex]-(*(p->info)))				//要求一个事件最迟发生时间  就需要时间最短的一个 （最迟发生的含义是  如果这个活动在这个最迟发生的时候发生 就正好赶在所有进度完成时完成 如果再晚就会延迟 这里是从后往前的 所以如果后面有两项工程开始时间一个为5，一个为6 这个工程耗时2 那么最迟开始必须是3 如果为4 第一个就不能按时开始 会导致总体的延迟（这里的一个5和另一个6都是最迟 递归的思想））
				vl[temp] = vl[p->adjvex]-(*(p->info));				//所以需要最小的一个才能保障
		}
	}
	int ee,el;
	char tag;

	//这一段是在复习时候修改的备注(注意只修改了备注)
		//看本文件夹的图示（CriticalPath最后for循环的含义.png）
	//下面的循环将在点的ve,vl算出来之后将数据放到边上去，即算出每条边的ee,el以用来比较判断是否是关键路径
	for(i=0;i<G.vexnum;i++)	
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)			//因为是有向图，并且满足拓扑有序，所以每个点在邻接表存储结构中存储的边都是不同的，即这条点连接边a,b，其余点不可能再涉及到a,b ，这样就可以将每条边的ee,el算出来且不重复。（注意是有向图，还满足拓扑有序是主要原因）
		{
			//处理每条边
			ee = ve[i];
			el = vl[p->adjvex]-(*(p->info));		//得到从这个弧尾的最迟减去弧长得到的弧头的最迟
			tag = (ee==el)?'*':' ';			//看弧头的最迟是否和弧头的最早相等 相等就是关键路径
			printf("%d  %d  %d  %d  %d  %c\n",i,p->adjvex,*(p->info),ee,el,tag);
		}//for循环主要是将点的数据转化为边的数据从而进行判断 


		 
		  /*//下面是一开始写的时候的理解 ，上面为之后复习时的理解
	//看本文件夹的图示（CriticalPath最后for循环的含义.png）
	for(i=0;i<G.vexnum;i++)								//这一步是对活动的开始和最迟进行比较  （我自己想想是不必要的 因为只要有ve[i] == vl[i]（注意下面的比较是ve[i]和vl[j]-dut<i,j>） 就能确定这个顶点是关键路径上的点  所以这也是我一个比较矛盾的点）
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			ee = ve[i];
			el = vl[p->adjvex]-(*(p->info));		//得到从这个弧尾的最迟减去弧长得到的弧头的最迟
			tag = (ee==el)?'*':' ';			//看弧头的最迟是否和弧头的最早相等 相等就是关键路径
			printf("%d  %d  %d  %d  %d  %c\n",i,p->adjvex,*(p->info),ee,el,tag);
		}//之所以有这个for循环我觉得主要是将注意力放在边上而不是点上（若在点上 则寻找每一个ve=vl的点串在一起）  注意力放在边上的话就要考虑这个点到下一个点 这个点的ve是否等于相连接的点的vl-dut（dut是指弧长，活动时长）（这个相连接的点的vl-dut其实就等于弧头点的vl 判断弧头点的ve是否与这个相等 就是判断最早和最迟是否相等）
*/
 }