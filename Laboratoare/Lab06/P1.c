#include <stdio.h>
#define MAX 50

void readmtr(int a[MAX][MAX],int m, int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
}

int main()
{

	int a[MAX][MAX],b[MAX][MAX],c[MAX][MAX],nl1,nl2,nc1,nc2,i,j,k;
	printf("linii A=");
	scanf("%d",&nl1);
	printf("coloane A=");
	scanf("%d",&nc1);
	printf("linii B=");
	scanf("%d",&nl2);
	printf("coloane B=");
	scanf("%d",&nc2);
	if(nc1==nl2)
	{
		readmtr(a,nl1,nc1);
		readmtr(b,nl2,nc2);
	}
	for(i=0;i<nl1;i++)
	{
		for(j=0;j<nc2;j++)
		{
		c[i][j]=0;
			for(k=0;k<nc1;k++)
			{
				c[i][j]+=a[i][k] * b[k][j];
			}
		}
	}
	for(i=0;i<nl1;i++)
	{
		for(j=0;j<nc2;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
			
