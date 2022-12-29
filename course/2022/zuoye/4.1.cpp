#include<stdio.h>

#include<stdlib.h>

#define STACK_INIT_SIZE   100        //存储空间的初始分配量
#define STACKINCREMENT  10          //存储空间的分配增量


typedef int SElemType;

 

typedef struct StackNode

{

    SElemType *base;
    SElemType *top;
    int stacksize;

}LinkStack;

 

void InitStack(LinkStack &S)

{


S.base = (SElemType *) malloc(STACK_INIT_SIZE*sizeof(SElemType));
S.top = S.base;
S.stacksize=STACK_INIT_SIZE; 

}

 

int StackEmpty(LinkStack &S)

{

         if(S.top==S.base)

         {

                   return 1;

         }

         else

         {

                   return 0;

         }

}

 

void Push(LinkStack &S,SElemType e)

{

    if(S.top-S.base>=S.stacksize){      //栈满,追加存储空间
        S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;



}

 

void Pop(LinkStack &S,SElemType &e)

{

    e=*--S.top;

}

 

void Conversion()

{

         LinkStack S;

         InitStack(S);

         printf("请输入非负十进制数\n");

         int N;

         N=1348;

         while(N!=0)

         {

                   int mod=N%8;

                   Push(S,mod);

                   N=N/8;

         }

         printf("八进制形式为: ");

        

         int e;

         while(StackEmpty(S)!=1)

         {

                   Pop(S,e);

                   printf("%d",e);

         }

         printf("\n");

}

 

int main()

{

         Conversion();

         return 1;

}

 
