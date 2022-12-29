#include<stdio.h>
int main(){
    int in,A[10],B[10],i,j,k,n1=0,n2=0;
    i=0;
    scanf("%d",&in);
    while(in!=-1){
        A[i]=in;
        i++;
        n1++;
        scanf("%d",&in);
    }
    i=0;
    scanf("%d",&in);
    while(in!=-1){
        B[i]=in;
        i++;
        n2++;
        scanf("%d",&in);
    }

    for(i=0;i<n1;i++){
        for(j=0;j<n2;j++){
            if (A[i]==B[j]){
                for(k=i;k<n1;k++){
                    A[k]=A[k+1];
                }
                n1--;
            }
        }
    }

    for(i=0;i<n1-1;i++){
        printf("%d ",A[i]);
    }
    printf("%d",A[i]);

    return 0;
}