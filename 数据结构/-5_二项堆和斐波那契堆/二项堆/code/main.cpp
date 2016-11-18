#include <stdio.h>
#include "head.h"

int main()
{
	BinoTree H1 = MAKE_BINOMIAL_HEAP();
	BINOMIAL_HEAP_INSERT(H1,41);
	BINOMIAL_HEAP_INSERT(H1,28);
	BinoTree H2 = MAKE_BINOMIAL_HEAP();
	BINOMIAL_HEAP_INSERT(H2,33);
	BINOMIAL_HEAP_INSERT(H2,15);
	H1 = BINOMIAL_HEAP_UNION(H1,H2);
	H2 = MAKE_BINOMIAL_HEAP();
	BINOMIAL_HEAP_INSERT(H2,7);
	BINOMIAL_HEAP_INSERT(H2,25);
	H1 = BINOMIAL_HEAP_UNION(H1,H2);
	H2 = MAKE_BINOMIAL_HEAP();
	BINOMIAL_HEAP_INSERT(H2,12);
	H1 = BINOMIAL_HEAP_UNION(H1,H2);	
	BinoTraverse(H1);
	BinoTree H3 = H1->sibling->sibling;
	BINOMIAL_HEAP_DECREASE_KEY(H1,H3,3);
	BinoTraverse(H1);
	BINOMIAL_HEAP_EXTRACT_MIN(H1);
	BinoTraverse(H1);
	return 0;
}