#include <stdio.h>
void fun(int *a, int *b)
{	int *c;
	c=a; a=b; b=c;
}
int main()
{	int x=3,y=5,*p=&x,*q=&y;
	fun(p,q);  printf(" %d, %d, ", *p,*q);
	fun(&x,&y);   printf(" %d, %d\n ", *p,*q);
}
