#include<stdio.h>
#include<math.h>
int main(){
    int start,m,n,count,i,j,prime,sum;
    scanf("%d %d",&n,&m);
    sum=0;
    start=2;
    count=1;
    if (n==1) sum=2;
    i=start+1;
    do{
        prime=1;
        for (j=3;j<=sqrt(i);j+=2){
            if (i%j==0) prime=0;
        }
        if (prime) count++;
        if (n<=count && count<=m && prime) sum+=i;
        if (n<=count && count<=m && prime) printf("%d %d,",i,count);
        i+=2;
    } while (count<m);
    printf("%d",sum);
    return 0;
}