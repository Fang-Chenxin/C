#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i,n;
    scanf("%d",&n);
    i=1;
    while (i<n-1){
        printf("%d ",i);
        i+=2;
    }
    printf("%d",i);
    return 0;
}
 