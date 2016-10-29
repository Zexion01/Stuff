#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
	FILE *f;
	char s[20];
	fgets(s,20,stdin);
	s[strlen(s)-1]=0;
	f=fopen(s,"w");
	
