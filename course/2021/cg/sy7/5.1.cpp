#include <stdio.h>
#include <string.h>
void delchar(char *s,char c)
{
char *p;
for(p=s;*s;s++)
if(*s!=c)
*p++=*s;
*p='\0';
}

int main() {
	char ch[20];	
	char c;int i=0;
	while(scanf("%c", &c) && c != '\n')
    {
        ch[i++] = c;
    }
    ch[i] = '\0';
	c=getchar();
    delchar(ch,c);
    int n=strlen(ch);
	for (int i = 0; i < n; i++) {
		printf("%c", ch[i]);
	}
	return 0;
}
