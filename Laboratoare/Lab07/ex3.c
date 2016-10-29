#include <stdio.h>

char * strdel(char *s, int pos, int n)
{
	int i;
	for(i=pos;i>=0;i--)
	{
		s[i+n]=s[i];
	}
	return s+n;
}
	

int main(void)
{
	char x[50]="ssdffnfDf";
	int pos,n,k;
	scanf("%d",&pos);
	scanf("%d",&n);
	k=(pos-2);
	printf("%s\n",strdel(x,k,n));
	return 0;
}
