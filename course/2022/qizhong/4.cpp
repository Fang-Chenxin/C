#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;

//定义链栈结构
typedef struct StackNode{
	char data;
	struct StackNode *next;
}StackNode,*LinkStack;

//初始化链栈
Status InitStack(LinkStack &S){
  S=NULL;
  return OK;
}

//判断链栈是否为空，是则返回TRUE，不是则返回FALSE
Status StackEmpty(LinkStack S)
{
	if (NULL == S)
		return TRUE;
	else
		return FALSE; 
}

//将元素e入栈
Status Push(LinkStack &S, char e)
{    
	LinkStack temp;
	temp = (LinkStack)malloc(sizeof(StackNode));
	temp->data = e;
	temp->next = S;
	S=temp;
	return OK;
}

//出栈，出栈元素赋值给e
Status Pop(LinkStack &S, char &e)
{
	LinkStack temp;
	if (StackEmpty(S)==TRUE)
		return ERROR;
	e = S->data;
	temp=S;
	S =S->next;
	free(temp);
	return OK;
}

int main()
{
	LinkStack s;
	InitStack(s);
	char str[20];
	scanf("%s",str);

	//★★★请补全代码
    int i,j,n;
    char e;
    i=0;
    while(str[i]!=',')
    {
        Push(s,str[i]);
        i++;
    }
    n=i;
    i++;
    for(j=n;j>0;j--)
    {
        Pop(s,e);
        printf("%c",e);
    }
    printf(",");
    while(i<strlen(str))
    {
        Push(s,str[i]);
        i++;
    }
    n=i-n-1;
    for(j=n;j>0;j--)
    {
        Pop(s,e);
        printf("%c",e);
    }
	return 0;
}
