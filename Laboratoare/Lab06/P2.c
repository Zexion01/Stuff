#include <stdio.h>
#define MAX 50

void readmtr(int a[MAX][MAX],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
}

void inmultire(int a[MAX][MAX],int b[MAX][MAX],int c[MAX][MAX],int nl1,int nl2,int nc1,int nc2)
{
	int i,j,k;
	int a1[MAX][MAX];
	for(i=0;i<nl1;i++)
	{
		for(j=0;j<nc1;j++)
		{
			a1[i][j]=a[i][j];
		}
	}
	for(i=0;i<nl1;i++)
	{
		for(j=0;j<nc2;j++)
		{
			c[i][j]=0;
			for(k=0;k<nc1;k++)
			{
				c[i][j]+=a1[i][k] * b[k][j];
			}
		}
	}
}

int main(void)
{
	int a[MAX][MAX],i,j,n,p,x[MAX][MAX];
	printf("n=");
	scanf("%d",&n);
	printf("p=");
	scanf("%d",&p);
	printf("Cofiguratia matricei \n");
	readmtr(a,n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			x[i][j]=a[i][j];
		}
	}
	for(i=0;i<p-1;i++)
	{
		inmultire(a,x,a,n,n,n,n);
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
