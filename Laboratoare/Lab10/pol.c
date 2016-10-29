#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int n;
	int* coef;
}TPol;


int max(int x, int y)
{
	if(x>=y)
		return x;
	if(x<y)
		return y;
}

void citPol(TPol* pol,int grad, int* coef)
{
	int i;
	printf("Coeficientii:\n");
	for(i=0;i<grad+1;i++)
	{
		scanf("%d",&coef[i]);
	}
	pol->coef=coef;
	pol->n=grad;
}

void afiPol(TPol* pol)
{
	int i;
	printf("pol->n=%d\n",pol->n);
	for(i=pol->n;i>=-1;i--)
	{
		if(pol->coef[i]==0)
			continue;
		else if(i==0)
			printf("%d",pol->coef[i]);
		else if(pol->coef[i]==1 && i==1)
			printf("X+");
		else if(pol->coef[i]==1 && i>1)
		{
			printf("X^%d+",i);
		}
		else if(pol->coef[i]>1 && i==1)
			printf("%dX+",pol->coef[i]);
		else if(pol->coef[i]>1 && i>1)
			printf("%dX^%d+",pol->coef[i],i);
	}
	printf("\n");
}

TPol* adunare(TPol* p1, TPol* p2)
{
	int i=0;
	TPol* polr=(TPol*)malloc(sizeof(TPol));
	polr->n=p2->n;
	polr->coef=(int*)malloc(polr->n*sizeof(int));
	if(polr->n == p1->n)
	{
		for(i=0;i<=p2->n;i++)
			polr->coef[i]=p1->coef[i]+p2->coef[i];
		for(;i<=p1->n;i++)
		{
			polr->coef[i]=p1->coef[i];
		}
	}
	else if(polr->n == p2->n)
	{
		for(i=0;i<=p1->n;i++)
			polr->coef[i]=p1->coef[i]+p2->coef[i];
		for(;i<=p2->n;i++)
		{
			polr->coef[i]=p2->coef[i];
		}
	}
	return polr;
}


int main(int argc, char const *argv[])
{
	TPol* pol1=(TPol*)malloc(sizeof(TPol));
	TPol* pol2=(TPol*)malloc(sizeof(TPol));
	TPol* polr=(TPol*)malloc(sizeof(TPol));
	int grad1=3;
	int grad2=4;
	int* coef1=(int*)malloc((grad1+1)*sizeof(int));
	int* coef2=(int*)malloc((grad2+1)*sizeof(int));
	citPol(pol1,grad1,coef1);
	citPol(pol2,grad2,coef2);
	//afiPol(pol2);
	polr=adunare(pol1,pol2);
	afiPol(polr);
	return 0;
}