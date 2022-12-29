#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define null 0
#define MAXSIZE 100
#define OK 1
#define ERROR 0

//定义一个结点类型 
typedef struct node{
    int data;
    struct node *next;
}Stacknode;
//定义一个栈类型 
typedef struct stack{
    Stacknode *top;
    Stacknode *base;
}Stack;


//栈的初始化
int CreateStack(Stack &s){
// 补充完整 
s.base = (node *)malloc(sizeof(node));
s.top = s.base;
s.top->next = NULL;
return OK;
}

//进栈---不带头结点的链栈---而且当前链表最后一个节点不存数据
int pushStack(Stack &s,int num){
// 补充完整 
node *p;
p = (node *)malloc(sizeof(node));
p->data = num;
p->next = s.top;
s.top = p;
return OK;
}


//判断栈为空
int Isempty(Stack &s){
    if(s.top==s.base){
        printf("栈是空栈\n");
        return OK;
    }else{
         printf("栈不是空栈\n");
        return OK;
    }
}

//出栈---不带头结点的链栈 
int popStack(Stack &s,int *num){
    if(s.top==s.base){
        printf("栈已经是空栈\n");
        return OK;
    }
// 补充完整 
node *p;
p=s.top;
*num=p->data;
s.top=p->next;
free(p);
return OK;
}

//从栈顶输出栈
void DispStack(Stack &s){

// 补充完整 
node *p;
p=s.top;
while(p->next) 
{
    printf("%d ",p->data);
    p=p->next;
}
}
int main(){
    Stack s;
    int e,e1;
    printf("链式栈的基本操作：\n");
    printf("（1）创建一个链式栈");
    CreateStack(s);
    pushStack(s,1);
    pushStack(s,2);
    pushStack(s,3);
    pushStack(s,4);
    printf("\n（2）判断链式栈是否为空：");
    Isempty(s);
    printf("（3）输出链式栈：");
    DispStack(s);
    printf("\n（4）出栈元素：");
    popStack(s,&e);
    printf("%d\n",e);
    printf("（5）出栈元素：");
    popStack(s,&e);
    printf("%d\n",e);
    printf("（6）输出链式栈：");
    DispStack(s);
    printf("\n（7）入栈元素\n");
    pushStack(s,101);
    pushStack(s,102);
    printf("（8）输出链式栈：");
    DispStack(s);
}
