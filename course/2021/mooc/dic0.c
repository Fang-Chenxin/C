#include<stdio.h>
int main(){
    int a,b;
    scanf("%d/%d",&a,&b);
int c=0;
    printf("0.");
    while((float)a/b && c<200){
        a*=10;
        printf("%d",a/b);
        a=a%b;
        c++;
    }
    printf("\n");
    return 0;
}
