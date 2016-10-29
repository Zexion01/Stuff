#include <stdio.h>

int main(void)
{
	int x;
	scanf("%d",&x);
	char *p=(char*)&x;
	if(*p+48)
	{
		printf("little edian\n");
	}
	else printf("big edian\n");
	return 0;
}
