#include <stdio.h>
#include <math.h>
int main()
{
    int A=43,B=A/2, C=B/2,x,y,i=B,j=-C,k=0;
    printf("\n\n\n");
    for(y=0; y<B; j=(++y)-(C+C/8))
    {
        for(k=0;k<10;k++)printf(" ");
        for(x=0; x<A; i= fabs((++x)-B)+j)
        {
            (i*i /2+j*j<(C*C*2)/3)?printf("#"):printf("*");
        }
        printf("\n") ;
    }
    printf("\n\n\n") ;
    return 0;
}