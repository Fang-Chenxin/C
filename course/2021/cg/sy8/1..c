#include<stdio.h>
#define N 6
void swap(int *a, int *b)
{	int c;
	c=*a; *a=*b; *b=c;
}
void sort_c(int *a,int n)
{
    int i,j,k,m;
    for (i=0;i<n;i++)
    {
        m=a[i];
        for (j=i;j<n;j++)
            {
                if (m>a[j]) 
                {
                    m=a[j];
                    k=j;
                }
            }
        swap(&a[k],&a[i]);
    }
}
void sort_b(int *a,int n)
{
    int i,j,*p1,*p2;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n-i-1;j++)
        {
            if (a[j]<a[j+1])
            {
                swap(&a[j],&a[j+1]);
            }
        }
    }
}
int main()
{
    int a[N],i;
    for (i=0;i<N;i++)
    {
        scanf("%d",&a[i]);
    }
    sort_c(a,N);
    for ( i = 0; i < N; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    sort_b(a,N);
    for ( i = 0; i < N; i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}