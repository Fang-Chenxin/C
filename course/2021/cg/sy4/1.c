#include<stdio.h>
int main(void)
{
 double e,item=1;
 int i,n;
 scanf("%d",&n);
 e = 1;
 for(i = 1; i <= n; i++) {                        
    item = item * i; 
  e = e + 1.0 / item;      /*调试时设置断点*/
 }
 printf("e = %.4f\n",e);       /*调试时设置断点*/

 return 0;
}