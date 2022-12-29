#include<stdio.h>
#include<math.h>
int main(int argc, char const *argv[])
{
    int in,read,n,t;
    scanf("%d",&in);
    t=in;
    do{
        t/=10;
        n++;
    }while (t!=0);
    if (in<0){
    printf("fu ");
    in=-in;
    }
    while (n>1){
        read=in/pow(10,n-1);
        read=read%10;
        switch (read)
        {
        case 1:
            printf("yi ");
            break;
        case 2:
            printf("er ");
            break;
        case 3:
            printf("san ");
            break;
        case 4:
            printf("si ");
            break;
        case 5:
            printf("wu ");
            break;
        case 6:
            printf("liu ");
            break;
        case 7:
            printf("qi ");
            break;
        case 8:
            printf("ba ");
            break;
        case 9:
            printf("jiu ");
            break;
        default:
            printf("ling ");
            break;
        }
    n--;
    }
    read=in%10;
     switch (read)
        {
        case 1:
            printf("yi");
            break;
        case 2:
            printf("er");
            break;
        case 3:
            printf("san");
            break;
        case 4:
            printf("si");
            break;
        case 5:
            printf("wu");
            break;
        case 6:
            printf("liu");
            break;
        case 7:
            printf("qi");
            break;
        case 8:
            printf("ba");
            break;
        case 9:
            printf("jiu");
            break;
        default:
            printf("ling");
            break;
        }
    return 0;
}
