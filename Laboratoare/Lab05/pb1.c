#include <stdio.h>

int min(int n,int v[])
{
	int i,minim=v[0];
	for(i=0;i<n;i++)
	 {
		if(v[i]<minim)
		{
		minim=v[i];
		}
	}
return minim;
}

int pmax(int n,int v[])
{
	int poz,i,maxim=v[0];
	for(i=0;i<n;i++)
	{
		if(v[i]>maxim)
		{
		maxim=v[i];
		poz=i;
		}
	}
return poz;
}

float ma(int n,int v[])
{
	int s,i;
	s=0;
	for(i=0;i<n;i++)
	{
		s+=v[i];
	}
return (float)s/n;
}

int gt(int n,int v[])
{
	int count,i,med;
	med=ma(n,v);
	count=0;
	for(i=0;i<n;i++)
	{
		if(v[i]>med)
		count+=1;
	}
return count;
} 
	
int main()
{

int v[100],n,i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	scanf("%d",&v[i]);
	}
		printf("min=%d\n",min(n,v));
		printf("pmax=%d\n",pmax(n,v));
		printf("medie=%.2f\n",ma(n,v));
		printf("gt_ma=%d\n",gt(n,v));
return 0;
}














