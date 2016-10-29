#include <stdio.h>
#define MAX 50

void readmtr(int a[MAX][MAX],int nl, int nc)
{
	int i,j;
	for(i=0;i<nl;i++)
	{
		for(j=0;j<nc;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
}

int main()
{
	int n,nl,nc,a[MAX][MAX],i,j;
	scanf("%d%d",&nl,&nc);
	printf("Dati valorile matricei \n");
	readmtr(a,nl,nc);
	printf("Indicele(0-%d) n=",nc);
	scanf("%d",&n);
	for(i=0;i<(nc-n);i++)
	{
		a[i][n+i]=0;
	}
	for(i=0;i<n;i++)
	{
		a[i][n-i]=0;
	}
	for(i=0;i<nl;i++)
	{
		for(j=0;j<nc;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}	

