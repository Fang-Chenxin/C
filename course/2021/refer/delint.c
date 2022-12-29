#include<stdio.h>
void delint(int *s,int c,int n)
{
    int *p;
    for(int i=0;i<n;i++)
    {
        s++;
        if (*s!=c)
        {
            *p++=*s;
        }
    }
}