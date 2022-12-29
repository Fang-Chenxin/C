#include<stdio.h>
int main(int argc, char const *argv[])
{
    int odd=-1,even=0,a=0;
    while(a!=-1){
        scanf("%d",&a);
        if (a%2) odd++;
        else even++;
    }
    printf("%d %d",odd,even);
    return 0;
}
