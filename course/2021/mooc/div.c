#include<stdio.h>
void di(int,int);
int main(){
    int a,b;
    scanf("%d/%d",&a,&b);
    void di(a,b);
    return 0;
}

void di(int a,int b){
    int c=0;
    printf("0.");
    while((float)a/b && c<200){
        a*=10;
        printf("%d",a/b);
        a=a%b;
    }
    printf("\n");
}