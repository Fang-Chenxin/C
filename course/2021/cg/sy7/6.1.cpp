#include<stdio.h>
#include<string.h>
#define N 26
int main(){
    char c[80];
    char ch;
    int n,i;
    i=0;
    while((ch=getchar())!='\n'){
        c[i++]=ch;
    }
    c[i]=0;
    n=strlen(c);
    for(i=0;i<n;i++){
        ch=c[i];
        if (ch<='Z' && ch>='A'){
            c[i]='Z'-c[i]+'A';
            }
    }
    for (i=0;i<n;i++){
        printf("%c",c[i]);
    }
    return 0;
}