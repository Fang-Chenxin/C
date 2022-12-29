#include<stdio.h>
#include<math.h>
int main()
{
int money, year;
float rate, sum;
scanf("%d %d %f",&money,&year,&rate);
sum=money*pow((1+rate),year);
printf("sum=%.2f",sum);
return 0;
 } 
