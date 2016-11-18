#ifndef QUEUE_H
#define QUEUE_H

typedef struct Location
{
	int x;
	int y;
}Location;

typedef struct NODE
{
	Location data;
	struct NODE *pnext;
}nod, * pnod;


typedef struct S
{
	pnod phead;
	pnod ptail;
}ss, * pss;


void init(pss);
void en_queue(pss,Location );
void out_queue(pss,Location &);
bool is_empty(pss);





void init(pss Y)
{
	Y->phead=(pnod)malloc(sizeof(nod));
	if(Y->phead == NULL)
		return;
	Y->phead->pnext=NULL;
	Y->ptail=Y->phead;
}


void en_queue(pss Y,Location val)
{
	pnod new_x=(pnod)malloc(sizeof(nod));
	if(new_x == NULL)
		return;
	new_x->data=val;
	new_x->pnext=NULL;
	Y->ptail->pnext=new_x;
	Y->ptail=new_x;
}


bool is_empty(pss Y)
{
	if(Y->phead == Y->ptail)
		return true;
	else
		return false;
}


void out_queue(pss Y,Location &temp)
{
	if(is_empty(Y))
		return;
	else
	{
		pnod r=Y->phead->pnext;
		Y->phead->pnext=r->pnext;
		if(Y->phead->pnext==NULL)         //我就觉得这里需要注意一下  就是只剩下一个没有val的头结点和一个尾节点指向的节点的时候   没有这一步的话无法判断 is_empty
			Y->ptail=Y->phead;
		temp = r->data;
		free(r);
	}
}

bool Checkifinlist(pss Queue,Location temp)
{
	if(is_empty(Queue))
		return false;
	pnod current = Queue->phead->pnext;
	while(current)
	{
		if(current->data.x==temp.x && current->data.y==temp.y)
			return true;
		current = current->pnext;
	}
	return false;
}
#endif