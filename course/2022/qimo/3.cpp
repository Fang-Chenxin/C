
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define STACK_SIZE 100  //顺序栈容量 
#define  STACKINCRMENT 20
#define OK 1
#define ERROR 0
typedef char SElemType;
typedef struct
{
	SElemType *base;//栈底位置 
	SElemType *top;//栈顶位置
	int stacksize;//存储分配容量，以元素为单位。 
}SqStack;

//初始化 
//如果成功，返回OK，如果失败，返回ERROR
int InitStack(SqStack &S)//初始化
{
	
S.base=(SElemType *)malloc(STACK_SIZE*sizeof(SElemType));
	if(!S.base)
	   return ERROR;
	S.top=S.base;
	S.stacksize=STACK_SIZE;
	return OK; 
}

//入栈 
//如果成功，返回OK，如果失败，返回ERROR
int Push(SqStack &S, SElemType e)//入栈 
{
//★★★请补全代码
//★★★请补全代码
if (S.stacksize <= S.top - S.base)
{
    S.base = (SElemType *)realloc(S.base,sizeof(SElemType) * (STACK_SIZE+STACKINCRMENT));
    if(!S.base)
	   return ERROR;
	S.top=S.base + STACK_SIZE;
    S.stacksize += STACKINCRMENT;
}
S.top++;
*S.top = e;
return OK;


}
int StackEmpty(SqStack S)
{
	return (S.top==S.base);
}
//出栈 
//如果成功，返回OK，如果失败，返回ERROR
int Pop(SqStack &S,SElemType &e)//出栈 
{
	if(S.top==S.base)
	    return ERROR;
	e=*(S.top-1);
	S.top--;
	return OK;
}

// 获取栈顶元素
// 如果成功，返回OK，如果失败，返回ERROR
int GetTop(SqStack S, SElemType &e)
{
//★★★请补全代码
if (!S.top) return ERROR;
e=*S.top;
return OK;



}
 
int main()
{
	char str[100];
	gets(str);
	SqStack S;
	InitStack(S);
	
    /******************删除重复元素，并输出操作后的字符串*********************/
//★★★请补全代码

	
int i;
char e;
for (i = 0;i<strlen(str);i++)
{
    GetTop(S,e);
    if (e != str[i])
        Push(S,str[i]);
    else
        Pop(S,str[i]);
}
SElemType *p;
p = S.base++;
while(p != S.top)
{
    printf("%c",*p);
    p++;
}
printf("%c",*p);
return OK;


}
