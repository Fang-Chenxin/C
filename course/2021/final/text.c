#include<stdio.h>
int main(){
    int i;
    while (i<5)
    {   
        getchar();
        printf("0");
        i++;
    }
    char c;
    while(c=getchar()){
        printf("%c",c);
    }
}