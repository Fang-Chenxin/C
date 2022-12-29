#include<stdio.h>
int main(){
    int n,i=0,j=0;
    scanf("%d",&n);
    int s[n];
    while (i<n){
        scanf("%d",&s[i]);
        i++;
    }

    i=0;
    int temp;
    while (i<n){
        while (j<n-i-1){
            if (s[j]<s[j+1]){
                temp=s[j];s[j]=s[j+1];s[j+1]=temp;
            }
            j++;
        }
        j=0;
        i++;
    }

    i=0;
    while (i<n-1){
        printf("%d ",s[i]);
        i++;
    }
    printf("%d",s[i]);
    return 0;
}