#include<stdio.h>
void swap(int *a, int *b)
{	int c;
	c=*a; *a=*b; *b=c;
}
void sort_c(int *a,int n)
{
    int i,j,k;
    for (i=0;i<n;i++)
    {
        k=i;
        for (j=i;j<n;j++)
            {
                if (a[k]>a[j]) 
                {
                    k=j;
                }
            }
        swap(&a[k],&a[i]);
    }
}