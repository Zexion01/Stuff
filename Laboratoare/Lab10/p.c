#include <stdio.h>
#include <stdlib.h>
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
	int i,j;
	float **A;
	mat a;
	scanf("%d %d %d", &a.n, &a.c, &a.l);
	a.lin=malloc(a.n*sizeof(int));
	a.col=malloc(a.n*sizeof(int));
	a.val=malloc(a.n*sizeof(float));
	for(i=0;i<a.n;i++)
	{
		scanf("%d %d %f",&a.lin[i],&a.col[i],&a.val[i]);
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
