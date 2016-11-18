#include <stdio.h>
void insert(int *a,int len)
{
	int i,j,k,temp;
	for(i=0;i<len-1;i++)
	{
		temp = a[i+1];
		for(j=0;j<=i;j++)
		{
			if(temp<a[j])
			{
				for(k=i+1;k>j;k--)
					a[k]=a[k-1];
				a[j] = temp;
				temp = a[i+1];
			}
		}
	}
}
int main()
{
	int a[6] = {7,4,1,9,3,6};
	insert(a,6);
	for(int i=0;i<6;i++)
		printf("%d%c",a[i],((i+1)%6==0)?'\n':' ');
	return 0;
}