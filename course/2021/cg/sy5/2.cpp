#include<stdio.h>

int main(){
    int n,i=0;
    scanf("%d",&n);
    int s[n];
    while (i<n){
        scanf("%d",&s[i]);
        i++;
    }

    int min,max;
    i=0;min=0;max=0;
    while(i<n){
        if (s[i]>s[max]) max=i;
        if (s[i]<s[min]) min=i;
        i++;
    }

    int x;
    x=s[0];s[0]=s[min];s[min]=x;
    if (0==max) max=min;
    x=s[n-1];s[n-1]=s[max];s[max]=x;
    
    printf("After swapped:");

    i=0;
    while (i<n-1){
        printf("%d ",s[i]);
        i++;
    }
    printf("%d",s[i]);
    return 0;
}