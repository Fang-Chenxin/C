#include<stdio.h>
#include<string.h>
#define N 26
int main(){
    char a[N],b[N];
    char c[80];
    char ch;
    int n,i,j;
    for( i=0;i<N;i++){
        scanf("%c-->%c",&a[i],&b[i]);
        getchar();
    }
    i=0;
    while((ch=getchar())!='\n'){
        c[i++]=ch;
    }
    c[i]=0;
    n=strlen(c);
    for(i=0;i<n;i++){
        ch=c[i];
        if (ch<='Z' && ch>='A'){
            for( j=0;j<N;j++){
                if (ch==a[j]) break;
            }
            c[i]=b[j];
            }
    }
    for (i=0;i<n;i++){
        printf("%c",c[i]);
    }
    return 0;
}