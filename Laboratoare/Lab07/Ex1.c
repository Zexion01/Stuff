#include <stdio.h>

int main()
{
	int x=1024*1024*4;
	char *p;
	p = (char*)&x;
	if (*p == 0)
		printf("Big endian \n");
	else
		printf("Little endian \n");
	return 0;
}
		
