#include<stdio.h>
#include<math.h>
int main(){
    int n=0,num,k,s;
    scanf("%d",&k);
    num=k;
    while(k!=0){
        n++;
        k/=10;
    }
    while(n!=0){
        s=num/pow(10,n-1);
        s=s%10;
        printf("%d,",s);
        n--;
    }
    return 0;
}
