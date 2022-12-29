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


//��ʼ��ջ
void initStack(SeqStack &s){
  
// �������� 
s.base=(int*)malloc(MAXSIZE*sizeof(int));
if(!s.base) exit(1);

s.top=s.base;
s.size=MAXSIZE;

}
//�ж�ջ�Ƿ�Ϊ��
int stackempty(SeqStack &s){
    if(s.top==s.base){
        printf("ջ�ǿ�ջ\n");
        return OK;
    }
	else
	{
        printf("ջ���ǿ�ջ\n");
        return OK;
    }
}
//��ȡջ��Ԫ��
int Gettop(SeqStack &s,int &e){
    if(s.top==s.base){
        printf("ջ�ǿ�ջ\n");
        return OK;
    }
	else
	{
		e=*(s.top-1);
		return OK;
		
		
// �������� 
    }
}
//����˳��ջ
void DispStack(SeqStack &s){
	
// �������� 
int i;

for(i=s.top-s.base;i>0;i--)
 {
 printf("%d ",s.base[i-1]);
 }

}

//��ջ
int pushStack(SeqStack &s,int e){
    if(s.top-s.base==MAXSIZE){
        printf("ջ����ջ\n");
        return OK;
    }
	else
	{
// �������� 
   *s.top=e;
    s.top++;
   return OK;
   
    }
}
//��ջ--����ǿ�ջ��printf��ʱջ�ǿ�ջ 
int popStack(SeqStack &s,int &e){
    if(s.top==s.base){
        printf("��ʱջ�ǿ�ջ\n");
        return OK;
    }
	else
	{
	
		e=*(s.top-1);
		s.top--;
		return OK;
	
// �������� 
    }
}
int main(){
    SeqStack s;

    int num;
    Elemtype e;
    printf("˳��ջ����ز���:\n");
    printf("��1�����ν�ջ��1 2 3 4 \n");
    initStack(s);
    pushStack(s,1);
    pushStack(s,2);
    pushStack(s,3);
    pushStack(s,4);
    printf("��2����ջ������ջ��");
    DispStack(s);
    printf("\n");
    
    printf("��3���ж�ջ�Ƿ�Ϊ�գ�");
    stackempty(s);
    printf("��4����ȡջ��Ԫ��:");
    Gettop(s,num);
    printf("%d\n",num);
    printf("��5����ջջ��Ԫ�أ�");
    popStack(s,num);
    printf("%d\n",num);
    printf("��6����ȡջ��Ԫ�أ�");
   Gettop(s,num);
    printf("%d\n",num);
    printf("��7����ջ����Ԫ��:");
   popStack(s,num);
    printf("��ջ%d ",num);
    popStack(s,num);
    printf("��ջ%d ",num);
    popStack(s,num);
    printf("��ջ%d ",num);
    popStack(s,num);
    printf("��8����ȡջ��Ԫ�أ�");
    popStack(s,num);
    printf("��9���ж�ջ�Ƿ�Ϊ�գ�");
    stackempty(s);
    return 0;
}

