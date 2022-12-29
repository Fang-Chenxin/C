#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0


typedef int Elemtype;

typedef struct{
    int *base;
    int *top;
    int size;
}SeqStack;


//初始化栈
void initStack(SeqStack &s){
  
// 补充完整 
s.base = (Elemtype *)malloc(sizeof(Elemtype)*MAXSIZE);
if(!s.base) exit(1);
s.top = s.base;
s.size = MAXSIZE;

}
//判断栈是否为空
int stackempty(SeqStack &s){
    if(s.top==s.base){
        printf("栈是空栈\n");
        return OK;
    }
	else
	{
        printf("栈不是空栈\n");
        return OK;
    }
}
//获取栈顶元素
int Gettop(SeqStack &s,int &e){
    if(s.top==s.base){
        printf("栈是空栈\n");
        return OK;
    }
	else
	{
// 补充完整 
    e =*(s.top-1);
    return OK;
    }
}
//遍历顺序栈
void DispStack(SeqStack &s){
	
// 补充完整
/* int *p;
for(p=--s.top;p-s.base>=0;p--)
{
    printf("%d",*p);
}  */
int i;
for (i=s.top-s.base;i>0;i--)
{
    printf("%d",s.base[i-1]);
}

}

//进栈
int pushStack(SeqStack &s,int e){
    if(s.top-s.base==MAXSIZE){
        printf("栈是满栈\n");
        return OK;
    }
	else
	{
// 补充完整 
    *s.top = e;
    s.top++;
    return OK;
    }
}
//出栈--如果是空栈，printf此时栈是空栈 
int popStack(SeqStack &s,int &e){
    if(s.top==s.base){
        printf("此时栈是空栈\n");
        return OK;
    }
	else
	{
	
// 补充完整 
    s.top--;
    e = *s.top;
    return OK;
    }
}
int main(){
    SeqStack s;

    int num;
    Elemtype e;
    printf("顺序栈的相关操作:\n");
    printf("（1）依次进栈：1 2 3 4 \n");
    initStack(s);
    pushStack(s,1);
    pushStack(s,2);
    pushStack(s,3);
    pushStack(s,4);
    printf("（2）从栈顶遍历栈：");
    DispStack(s);
    printf("\n");
    
    printf("（3）判断栈是否为空：");
    stackempty(s);
    printf("（4）获取栈顶元素:");
    Gettop(s,num);
    printf("%d\n",num);
    printf("（5）出栈栈顶元素：");
    popStack(s,num);
    printf("%d\n",num);
    printf("（6）获取栈顶元素：");
    Gettop(s,num);
    printf("%d\n",num);
    printf("（7）出栈所有元素:");
    popStack(s,num);
    printf("出栈%d ",num);
    popStack(s,num);
    printf("出栈%d ",num);
    popStack(s,num);
    printf("出栈%d ",num);
    popStack(s,num);
    printf("（8）获取栈顶元素：");
    popStack(s,num);
    printf("（9）判断栈是否为空：");
    stackempty(s);
    return 0;
}
