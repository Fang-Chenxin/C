#include<stdio.h>
void delint(int *s,int c,int n)
{
    int *p;
    int i;
    for(i=0;i<n;i++)
    {
            if(s[i]!=c)
        {
    printf("%d ", s[i]);
        }
    }
}
int main()
{
    int n,i,c;
    scanf("%d",&n);
    int a[n+1];
    for (i = 0;i < n;i++)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&c);
    printf("after delete:\n");
    delint(a,c,n);
    return 0;
}