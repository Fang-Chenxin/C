#include<stdio.h>
int main(){
    int i=0,n,sum=0,in;
    double aver;
    scanf("%d",&n);
    while (i<n){
        scanf("%d",&in);
        sum+=in;
        i++;
    }
    aver=(double)sum/n;
    printf("average=%.2lf",aver);
    return 0;
}