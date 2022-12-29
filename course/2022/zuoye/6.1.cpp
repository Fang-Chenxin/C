
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

 

int JieCheng(int n)

{
    if (n > 15)
    {
        printf("无法计算\n");
        return 0;
    }
    if (n == 0) return 1;
    else
    {
        return JieCheng(n-1)*n;
    }

}

 

int main()

{

    int a;

    int n;

    a=0;

    printf("Input n:\n");

    scanf("%d",&n);

    a = JieCheng(n);

    printf("%d的阶乘为%d",n,a);

}