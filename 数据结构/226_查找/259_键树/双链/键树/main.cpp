#include <stdio.h>
#include "head.h"
void visit(Record* p)
{
	for(int i=0;i<p->key.num;i++)
		printf("%c",p->key.ch[i]);
	puts("");
}
int main()
{
	DLTree DT;Record *t;
	Record r[] = {{"CAI",3},{"CAO",3},{"LI",2},{"LAN",3},{"CHANG",5},{"CHA",3},{"WEN",3},{"CHAO",4},{"YUN",3},{"YANG",4},{"LONG",4},{"WANG",4},{"ZHAO",4},{"LIU",3},{"WU",2},{"CHEN",4}};
	//Record r[] = {{"CAI",3}};
	InitDSTable(DT);
	for(int i=0;i<16;i++)
	{
		t = SearchDLTree(DT,r[i].key);
		if(!t)
			InsertDSTable(DT,&r[i]);
	}
	TraverseDSTable(DT,visit);
	DestroyDSTable(DT);
	return 0;
}