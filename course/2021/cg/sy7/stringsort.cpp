#include<stdio.h>
int main(){
    int a[256]={0};
    char ch;
    while((ch=getchar())!='\n')
    {
        a[ch]=1;
    }
    for(int i=0;i<256;i++){
        if (a[i])
        {
            ch=i;printf("%c",ch);
        }
    }
}