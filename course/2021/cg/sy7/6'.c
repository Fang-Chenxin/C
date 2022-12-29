#include<stdio.h>
int main(){
    char a='A';
    char b='Z';
    for (int i=0;i<26;i++){
        printf("%c-->%c ",a+i,b-i);
    }
}