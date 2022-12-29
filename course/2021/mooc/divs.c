#include<stdio.h>
int getGCD(int m,int n){
	if (m%n==0) return n;
	else
	    return getGCD(n,m%n);
}

main{
    int a,b,c;
    scanf("%d/%d",&a,&b);
    if (a<b){
    c=getGCD(b,a);
    a/=c;
    b/=c;
    }
    printf("%d/%d",a,b);
    return 0;
}