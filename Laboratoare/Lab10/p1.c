#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int n;
	int c;
	int l; 
	int *lin;
	int *col;
	float *val;
} mat;

int main()
{
	int i,j,c;
	float **A;
	mat a;
	mat b;
	scanf("%d %d %d", &a.n, &a.c, &a.l);
	scanf("%d %d %d",&b.n,&b.c,&b.l);
	a.lin=malloc(a.l * a.c *sizeof(int));
	a.col=malloc(a.l * a.c *sizeof(int));
	a.val=malloc(a.l * a.c *sizeof(float));
	b.lin=malloc(b.l * b.c *sizeof(int));
	b.col=malloc(b.c * b.l *sizeof(int));
	b.val=malloc(b.c * b.l *sizeof(float));

	for(i=0;i<a.n;i++)
	{
		scanf("%d %d %f",&a.lin[i],&a.col[i],&a.val[i]);
	}
	for(i=0;i<b.n;i++)
	{
		scanf("%d %d %f",&b.lin[i],&b.col[i],&b.val[i]);
	}
	c = a.n;
	for (i=0; i < b.n; i++)
	{
		for (j = 0; j < c; j++)
		{
			if ((b.lin[i] == a.lin[j]) && (b.col[i] == a.col[j]))
			{
				a.val[j] += b.val[i];

			}
		
			else 
			{
				a.n += 1;
				//a.lin = realloc (a.lin, a.n + 1);
				//a.col = realloc (a.col, a.n + 1);
				//a.val = realloc (a.val, a.n + 1);
				a.lin[a.n - 1] = b.lin[i];
				a.col[a.n - 1] = b.col[i];
				a.val[a.n + 1] = b.val[i];
			}
		}
	}
	A=malloc(a.l*sizeof(float*));
	for(i=0;i<a.c;i++)
	{
		A[i]=malloc(a.c*sizeof(float));

	}
	for(i=0;i<a.l;i++)
		for(j=0;j<a.c;j++)
		{
			A[i][j]=0;
		}
	for(i=0;i<a.n;i++)
	{
		A[a.lin[i]][a.col[i]]=a.val[i];
	}
	for(i=0;i<a.l;i++)
	{
		for(j=0;j<a.c;j++)
		printf("%.0f ",A[i][j]);
		printf("\n");
	}
	free(a.lin);
	free(a.col);
	free(a.val);
	free(A);
	return 0;

}
