#include <stdio.h>
#include <string.h>
 
int main ()
{
	char str[30];
	char *p;
	gets(str);
	p = strtok(str, " ,.-");
	while (p != NULL) 
	{
		printf("%s\n",p);
		p = strtok(NULL, " ,.-");
  	}
	return 0;
}
