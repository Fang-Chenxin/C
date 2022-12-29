#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define null 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef struct
{
    int *base;
    int front;
    int rear;
} sqQueue;

//初始化循环队列
void InitQueue(sqQueue &q)
{
    //补充完整
    q.base = (int *)malloc(sizeof(int)*MAXSIZE);
    q.front = q.rear =0;
}
//求循环队列的长度
int Queuelength(sqQueue &q)
{
    return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//循环队列的入队
int pushQueue(sqQueue &q, int num)
{
    //补充完整
    if ((q.rear+1)%MAXSIZE == q.front) return ERROR;
    q.base[q.rear] = num;
    q.rear = (q.rear+1)%MAXSIZE;
    return OK;
}
//循环队列的出队
int popQueue(sqQueue &q, int *num)
{
    //补充完整
    if ((q.rear+1)%MAXSIZE == q.front) return ERROR;
    *num = q.base[q.front];
    q.front = (q.front+1)%MAXSIZE;
    return OK;
}

//循环列表的遍历
void DispQueue(sqQueue &q)
{

    //补充完整
    int i;
    i = q.front;
    while (i != q.rear)
    {
        printf("%d ",q.base[i]);
        i = (i+1)%MAXSIZE;
    }

}

int main()
{
    sqQueue q;
    int num;
    InitQueue(q);
    printf("循环队列的基本操作：\n");
    printf("（1）初始化循环队列并入队\n");
    pushQueue(q, 10);
    pushQueue(q, 20);
    pushQueue(q, 30);
    pushQueue(q, 40);
    pushQueue(q, 50);
    pushQueue(q, 60);
    printf("（2）循环队列的遍历：");
    DispQueue(q);
    printf("\n");

    printf("（3）循环队列的出队：");
        popQueue(q,&num);
        printf("当前队头%d出队   ",num);
        popQueue(q,&num);
        printf("当前队头%d出队\n",num);
        printf("     遍历队列：");
        DispQueue(q);
}
