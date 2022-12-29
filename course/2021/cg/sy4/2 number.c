#include<stdio.h>
int main(){
    int n=0,m,s=0,i,a;
    scanf("%d",&m);
    a=m;
    do{
        a/=10;
        n++;
    }while (a!=0);
    for (i=1;i<=n;i++){
        s=s*10+m%10;
        printf("%d",m%10);
        if (i!=n) printf(" ");
        else printf("\n");
        m/=10;
    }
    printf("%d\n%d",s,n);
    return 0;
}