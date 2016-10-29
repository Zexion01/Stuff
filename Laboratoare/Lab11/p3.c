#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	int n,a,i;
	srand(time(NULL));
	FILE *f;
	f=fopen("fisier","wb");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		a=rand()%100;
		printf("%d\n",a);
		fwrite(&a,4,1,f);
	}
	fclose(f);
	return 0;
}
