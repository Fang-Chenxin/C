#include<stdio.h>
#include<math.h>
int main()
{
    int a,b,c,d;
    float l;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    l=sqrt((c-a)*(c-a)+(d-b)*(d-b));
    printf("%.2f",l);
}