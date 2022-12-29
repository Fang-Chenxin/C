#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE  100
typedef int Status;
typedef char SElemType;
typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//初始化顺序栈
Status InitStack(SqStack &S)	
{
	S.base = (SElemType*)malloc(sizeof(SElemType)*MAXSIZE);
	if(!S.base)
		return OVERFLOW;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;

}
//入栈
Status Push(SqStack &S,SElemType e)		{
	if(S.top-S.base == S.stacksize)
		return ERROR;
	*(S.top++) = e;
	return OK;
}

//出栈
Status Pop(SqStack &S, SElemType &e)		{
	if(S.base == S.top)
		return ERROR;
	e = *(--S.top);
	return OK;
}
//销毁顺序栈
Status DestroyStack (SqStack &S){
	//★★★请补全代码
    S.top = S.base;
    S.stacksize = NULL;
    free(S.base);
    return OK;
}

//判断字符序列是否为“回文”, 如果是返回1，否则返回0 
//提示：需要调用堆栈的基本操作来实现，如果未使用堆栈，答题无效。
int IsPalindrome(char *t)	{
	//★★★请补全代码
    SqStack S;
    InitStack(S);
    int i,n;
    i = 0;
    n = strlen(t);
    for (i=0;i<n/2;i++)
    {
        Push(S,t[i]);
    }
    for (i=n-n/2;i<n;i++)
    {
        char e;
        Pop(S,e);
        if (e != t[i])
            return 0;
    }
    return 1;
}


int main()
{
	char p[MAXSIZE];
	scanf("%s",p);
	if(IsPalindrome(p)) 
	{
		printf("Yes");
	}
	else
	{
		printf("No");
	}
	return 0;
}
