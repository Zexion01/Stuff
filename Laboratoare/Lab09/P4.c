#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main () {
  char *s;
  int i,nr=0;
  char str[60];
  char v[30];
  fgets(str,60,stdin);
  str[strlen(str)-1]='\0';
  fgets(v,30,stdin);
  v[strlen(v)-1]='\0';
  for(i=0;i<strlen(str);i++)
  {
  	if(str[i]=='"')
  	str[i]='#';
  	
  }
  //char *p;
  char *p=malloc(100*sizeof(char));  
  p = strtok(str, " ,.-!?'#");
  while (p != NULL) {
    if(strcmp(p,v)==0)
    {
    	nr++;
    }
    p = strtok(NULL, " ,.-");
  }
  free(p);
  printf("%d\n",nr);
  return 0;
}
