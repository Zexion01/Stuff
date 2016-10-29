#include <stdio.h>

int string_ln(char*p)
{
   int count = 0;
   while (*p != '\0') 
   {
      count++;
      p++;
   }
   return count;
} 

char * strins(char *s1, int pos, char *s2)
{
	int i,j,k;
	for(i=pos;i<string_ln(s1)-pos;i++)
	{
		s1[i+string_ln(s2)]=s1[i];
	}
	for(i=pos;i<pos+string_ln(s2);i++)
	{
		s1[i]=s2[i-pos];
	}
	return s1;
}

int main(void)
{
	char s1[50],s2[50];
	int pos;
	scanf("%s",s1);
	scanf("%s",s2);
	scanf("%d",&pos);
	printf("%s\n",strins(s1,pos,s2));
	return 0;
}
