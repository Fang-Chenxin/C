#include<stdio.h>

int main(){
    int n,i=0;
    scanf("%d",&n);
    int s[n];
    while (i<n){
        scanf("%d",&s[i]);
        i++;
    }

    i=n-1;
    while (i>0){
        printf("%d ",s[i]);
        i--;
    }
    printf("%d",s[i]);
    return 0;
}