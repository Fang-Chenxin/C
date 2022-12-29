#include<stdio.h>
int main(){
    int bjt,utc,b[5],h,m,H;
    scanf("%d",&bjt);
    h=bjt/100;
    m=bjt%100;
    H=h-8;
    if (H<0) H=H+24;
    b[0]=0;
    b[1]=H/10;
    b[2]=H%10;
    b[3]=m/10;
    b[4]=m%10;
    int i=1;
    while (i!=5 && (b[4]!=0 || b[2]!=0)){
        utc=utc*10+b[i];
        i++;
    }
    printf("%d",utc);
    return 0;
}