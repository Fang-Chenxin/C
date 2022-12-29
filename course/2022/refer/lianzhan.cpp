#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define null 0
#define MAXSIZE 100
#define OK 1
#define ERROR 0

//����һ��������� 
typedef struct node{
    int data;
    struct node *next;
}Stacknode;

//����һ��ջ���� 
typedef struct stack{
    Stacknode *top;
    Stacknode *base;
}Stack;


//ջ�ĳ�ʼ��
int CreateStack(Stack &s){
// �������� 

s.base=(Stacknode*)malloc(sizeof(Stacknode));
s.top=s.base;

s.top->next=NULL;

return 1;

}

//��ջ---����ͷ������ջ---���ҵ�ǰ�������һ���ڵ㲻������
int pushStack(Stack &s,int num){
// �������� 
Stacknode *p;

p=(Stacknode*)malloc(sizeof(Stacknode));
p->data=num;

p->next=s.top;

s.top=p; 

}


//�ж�ջΪ��
int Isempty(Stack &s){
    if(s.top==s.base){
        printf("ջ�ǿ�ջ\n");
        return OK;
    }else{
         printf("ջ���ǿ�ջ\n");
        return OK;
    }
}

//��ջ---����ͷ������ջ 
int popStack(Stack &s,int *num){
    if(s.top==s.base){
        printf("ջ�Ѿ��ǿ�ջ\n");
        return OK;
    }
// �������� 
 Stacknode *p;
 p=s.top;

*num=s.top->data;
s.top=s.top->next;

free(p);

return 1;

}

//��ջ�����ջ
void DispStack(Stack &s){

// �������� 
 Stacknode *p;
 
 p=s.top;
 
 while(p!=s.base){
 printf("%d ",p->data);
 p=p->next;
 
}
 
 
}
int main(){
    Stack s;
    int e,e1;
    printf("��ʽջ�Ļ���������\n");
    printf("��1������һ����ʽջ");
    CreateStack(s);
    pushStack(s,1);
    pushStack(s,2);
    pushStack(s,3);
    pushStack(s,4);
    printf("\n��2���ж���ʽջ�Ƿ�Ϊ�գ�");
    Isempty(s);
    printf("��3�������ʽջ��");
    DispStack(s);
    printf("\n��4����ջԪ�أ�");
    popStack(s,&e);
    printf("%d\n",e);
    printf("��5����ջԪ�أ�");
    popStack(s,&e);
    printf("%d\n",e);
    printf("��6�������ʽջ��");
    DispStack(s);
    printf("\n��7����ջԪ��\n");
    pushStack(s,101);
    pushStack(s,102);
    printf("��8�������ʽջ��");
    DispStack(s);
}

