#include<stdio.h>
int main(){
    int n,s[10]={0},max,i,t;
    scanf("%d",&n);

    i=0;
    while (i<n){
    scanf("%d",&t);
    s[t-1]++;
    i++;
    }

    i=1;max=0;
    while(i<10){
        if (s[i]>s[max]) {max=i;}
        i++;
    }

    printf("%d appears %d times",max+1,s[max]);
    return 0;
}