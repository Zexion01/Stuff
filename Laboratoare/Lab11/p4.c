#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
	FILE *f;
	void *ptr=malloc(sizeof(int));
	int i,j,k,c,s=0,si=0,sp=0;
	f=fopen("lab11p4.bin","rb");
	fseek(f,0,2);
	i=ftell(f);
	printf("Numar de numere:%d\n",i/4);
	fseek(f,0,0);
	for(j=0;j<i/4;j++)
	{
		c=0;
		fread(ptr,sizeof(int),1,f);
		s+=*(int*)ptr;
		if(*(int*)ptr%2==1)
			si+=*(int*)ptr;
		for(k=1;k<*(int*)ptr/2;k++)
		{
			if(*(int*)ptr%k==0)
			{
				c++;
			}
		}
		if(c==1)
		{
				sp+=*(int*)ptr;
		}
	}
	printf("Suma1:%d\nSuma2:%d\nSuma3:%d\n",s,si,sp);
	fclose(f);
	return 0;
}