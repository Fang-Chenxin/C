#include<stdio.h>
void delchar(char *s,char c)
{
char *p;
for(p=s;*s;s++)
    if(*s!=c)
        *p++=*s;
*p='\0';
}