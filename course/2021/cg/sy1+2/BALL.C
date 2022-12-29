#include<stdio.h>
int main()
    {
    int n,i;
    float h,s;
    scanf("%f,%d",&h,&n);
    s=h;
    h/=2;
    for (i=1;i<n;i++)
    {
        s=s+2*h;
        h/=2;        
    }
    printf("%f %f",s,h);
    return 0;
    }
