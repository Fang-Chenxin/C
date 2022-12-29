#include<stdio.h>
int main()
{
int i = 4, j;
while (i>0)
 	{
	 j = i-1;
	while (j>0)
		{
		printf("* ");
		j--;
		}
	printf("*\n");
	i--;
	}
} 
