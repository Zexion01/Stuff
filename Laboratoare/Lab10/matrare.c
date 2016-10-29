#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int n;
	int c;
	int l; 
	int* lin;
	int* col;
	int* val;
} mat;

void Citire(mat* m, int n, int c, int l)
{
	m->n=n;
	m->c=c;
	m->l=l;
	m->lin=(int*)malloc(n*sizeof(int));
	m->col=(int*)malloc(n*sizeof(int));
	m->val=(int*)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++)
	{
		printf("Valoarea:");
		scanf("%d",&m->val[i]);
		printf("Pozitie:");
		scanf("%d",&m->lin[i]);
		scanf("%d",&m->col[i]);
	}
}

int** Atrib(mat* m)
{
	int i;
	int** mr=(int**)calloc(m->l,sizeof(int*));
	for(i=0;i<m->c;i++)
	{
		mr[i]=(int*)calloc(m->c,sizeof(int));
	}
	for(i=0;i<m->n;i++)
	{
		mr[m->lin[i]][m->col[i]]=m->val[i];
	}
	return mr;
}

void afiMat(int** mr, mat* m)
{
	int i,j;
	for(i=0;i<m->l;i++)
	{
		for(j=0;j<m->c;j++)
			printf("%d ",mr[i][j]);
		printf("\n");
	}
}

mat* adunare(mat* m1, mat* m2)
{
	mat* mr=malloc(sizeof(mat));
	mr->
	for(i=0;i<m1->n;i++)
	{
		for(j=0;j<m2->n;j++)
		{
			if(m1->lin[i]==m2->lin[j] && m1->col[i]==m2->col[i])
			{
				mr->
			}

		}
	}
}

int main(int argc, char const *argv[])
{
	mat* m1=(mat*)malloc(sizeof(mat));
	mat* m2=(mat*)malloc(sizeof(mat));
	mat* mr1;
	Citire(m1,3,10,10);
	Citire(m2,3,10,10);
	int** mr=Atrib(mr1);
	afiMat(mr,m);
	return 0;
}