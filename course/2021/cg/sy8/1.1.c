#include <stdio.h> 
#define N 6
void sort_c(int *a,int n);
void swap(int *a,int *b);
int  main()
{
int a[N],i;
for(i=0;i<N;i++)
{
scanf("%d",&a[i]);
}
sort_c(a,N);
for (i=0;i<N;i++)
{
printf("%d ",a[i]);
}
printf("\n");
//sort_c(a,N);
//for ( i=0;i<N;i++)
//{
//printf("%d ",a[i]);
//}
return 0;}

void sort_c(int *a,int n)
{
int i,j,m,p;
for (i=0;i<n-1;i++)
{
   //m=a[i];
   p=i;
 for (j=i+1;j<n;j++)
  {
   //if(m>a[j])
  //  {m=a[j];p=j;}}
    if(a[j]<a[p]) 
     p=j; }     //**************
   if(p!=i)
   swap(&a[p],&a[i]);
  
}
}
void swap(int *a, int *b)
{int c;
 c=*a; *a=*b; *b=c;
}