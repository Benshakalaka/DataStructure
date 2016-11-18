#include <stdio.h>
#include "head.h"

int main()
{
	SLList L;
	SLCell r[] = {{"000",0},{"278",0},{"109",0},{"063",0},{"930",0},{"589",0},{"184",0},{"505",0},{"269",0},{"008",0},{"083",0}};
	int i;
	for(i=0;i<=10;i++)
		L.r[i] = r[i];
	L.keynum = 3;
	L.recnum = 10;
	RadixSort(L);
	for(i=L.r[0].next;i;i=L.r[i].next)
		printf("%s ",L.r[i].keys);
	puts("");
	return 0;
}
