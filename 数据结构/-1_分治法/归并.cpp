#include <stdio.h>						//Merge sort.
#include <malloc.h>
void Merge(int *a,int p,int q,int r)
{
	int *x;
	x = (int *)malloc(sizeof(int)*(r-p+1));
	int i=p,j=q,k=0;
	while(i<q && j<=r)
	{
		if(a[i]<a[j])
			x[k++] = a[i++];
		else
			x[k++] = a[j++];
	}
	while(i<q)
		x[k++] = a[i++];
	while(j<=r)
		x[k++] = a[j++];
	for(i=0,k=0;i<(r-p+1);i++,k++)
		a[i+p] = x[k];
	free(x);
}
void Merge_sort(int *a,int p,int r)		//分成两组 A[p...q]  A[q+1,r]
{
	if(p==r)
		return;
	Merge_sort(a,p,(r+p)/2);
	Merge_sort(a,(p+r)/2+1,r);
	Merge(a,p,(r+p)/2+1,r);
}
int main()
{
	int a[] = {5,4,7,2,8,6,9,3};
	Merge_sort(a,0,7);
	for(int i=0;i<8;i++)
		printf("%d ",a[i]);
	puts("");
	return 0;
}