#include <stdio.h>
#include <stdlib.h>	
int main( )
{ char c;FILE *fp;
	if(( fp=fopen("a.txt", "r"))==NULL)
 { printf("Can’t open this file! \n"); 
  exit(0);}
  while((c=fgetc(fp))!=EOF)
  printf("%c",c);
  fclose(fp); 
 return 0;} 
