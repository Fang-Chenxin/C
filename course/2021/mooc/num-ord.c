#include<stdio.h>
#include<math.h>
int main(int argc, char const *argv[])
{
    int num,ord=1,n,ans;
    scanf("%d",&n);
    while(n!=0){
        num=n%10;
        if (num%2==ord%2) ans+=pow(2,ord-1);
        n/=10;
        ord++;
    }
    printf("%d",ans);
    return 0;
}
