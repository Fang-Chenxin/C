/*
给定一个字符串，采用堆栈将其进行翻转. 例如 "ILoveChina, ILoveBJTU, ILoveGJCXSJXL" 
 应被转换成 "LXJSXCJGevoLI ,UTJBevoLI ,anihCevoLI".
【编程提示】：
1）	建一个空栈；
2）	将字符串数组的元素逐一进栈；
3）	将堆栈元素逐一出栈，依次存入字符串数组中。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct Stack
{
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = 0;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(struct Stack stack)
{
	int full = 0;
    full = (stack.top == (int)stack.capacity )?1:0;
	return full;
} 

int isEmpty(struct Stack stack)
{
    return stack.top == 0;
} 

void push(struct Stack &stack, char item)
{
  /***补全函数****/
    if (isFull(stack))
        exit(1);
    stack.array[stack.top] = item;
    stack.top++;

}

char pop(struct Stack &stack)
{
    if (isEmpty(stack))
        return CHAR_MIN;
    return stack.array[--stack.top];
}

void reverseStr(char str[])
{
/***补全函数****/
    struct Stack *s;
    s = createStack(40);
    while(strlen(str)>s->top)
    {
        push(*s,str[s->top]);
    }
    int i;
    i=0;
    while(i<strlen(str))
    {
        str[i] = pop(*s);
        i++;
    }

}

int main()
{
    char str[] = "ILoveChina, ILoveBJTU, ILoveGJCXSJXL";
    printf("The given string %s has %d characters.\n", str, strlen(str));

    reverseStr(str);
    printf("Reversed string is %s\n", str);

    return 0;
}


