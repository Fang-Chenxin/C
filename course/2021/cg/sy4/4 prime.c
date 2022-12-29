#include<stdio.h>
#include<math.h>
int main(){
    int m,n,i,j,k,l;
    scanf("%d %d",&m,&n);
    if (m==2) {
        printf("2");
        k=1;
        }
    m=m/2*2+1;
    for (i=m;i<=n;i=i+2){
        l=1;
        for (j=3;j<=sqrt(i);j=j+2){
            if (i%j==0) {
                l=0;
                break;
                }
            }
            if (l && k) printf(" %d",i);
            else if (l) {
                printf("%d",i);
                k=1;
        }
    }
    return 0;
}