#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define STATCK_INIT_SIZE 20 /*栈存储空间的初始分配量 */
#define STATACKINCREMENT 5 /*栈存储控制的分配增量 */
#define MAXQSIZE  20   //最大队列长度

typedef int Status;
typedef int SElemType;
typedef struct{
    SElemType *base; /* 栈底指针 */
    SElemType *top;  /* 栈顶指针 */
    int stacksize;   /* 当前分配的存储容量 */
}SqStack;

typedef  int QElemType; /*定义队列元素的类型*/
typedef struct {
   QElemType *base;   //初始化的动态分配存储空间
   int  front;                    //头指针   
   int  rear;                     //尾指针
}SqQueue;  

Status InitStack(SqStack &S){
   S.base=(SElemType*)malloc(STATCK_INIT_SIZE*sizeof(SElemType));
    if(!S.base) 
        return ERROR;
    S.top=S.base;
    S.stacksize=STATCK_INIT_SIZE;
    return OK;    
}

Status Pop(SqStack &S, SElemType &e) {
    if(S.top==S.base) 
        return ERROR;
    e=*--S.top;
    S.stacksize--;
    return OK;
}

Status Push(SqStack &S, int e) {
    if((S.top-S.base)>=S.stacksize){
        S.base=(SElemType*)realloc(S.base, (S.stacksize+STATACKINCREMENT)*sizeof(SElemType));
        if(!S.base) 
            return ERROR;
        S.top=S.base+S.stacksize;
        S.stacksize += STATACKINCREMENT;
    }
    *S.top++=e;
    return OK;
} 

Status InitQueue(SqQueue &Q){
    Q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q.base) 
        return ERROR;
    Q.front=Q.rear=0;
    return OK;
}

Status EnQueue(SqQueue &Q, QElemType e)
{
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
{
	//★★★请补全代码
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1+MAXQSIZE)%MAXQSIZE;
    return OK;
}

Status CreateQueue(SqQueue &Q, int n)
{
    int i;
    InitQueue(Q);    
    for(i=1; i<=n; i++)
        EnQueue(Q, i);
    return OK;
}

void QueueTraverse(SqQueue Q)
{
    int i=Q.front;
    while(i!=Q.rear){
        printf("%d ", Q.base[i]);
        i=(i+1)%MAXQSIZE;
    }
}

Status DestroyQueue (SqQueue &Q){
    if(Q.base)
        free(Q.base);
    Q.base=NULL;
    Q.front=Q.rear=0;      
   return OK;
}// DestroyQueue

/*  未出圈者重新入队列，出圈者入栈 */
Status Delete(int n, int k, SqQueue &Q, SqStack &S) {
	//★★★请补全代码
    int i,j,m,e;
    m=0;
    while(n>0)
    {
        j=0;
        for (i=1;i<=n;i++)
        {
            m++;
            DeQueue(Q,e);
            if (m%k == 0)
            {
                Push(S,e);
                j++;
            }
            else
            {
                EnQueue(Q,e);
            }
        }
        n-=j;
    }
    return OK;
}

int main()
{
    int n,k;
    int idx;
    SqQueue Q;
    SqStack S;
    InitStack(S);
    scanf("%d%d",&n,&k);
    printf("n=%d,k=%d\n",n,k);
    CreateQueue(Q, n);
    printf("the people id is:\n");
    QueueTraverse(Q);
    printf("\n");
    printf("out sequence:\n");
    Delete(n,k,Q,S);
    printf("\n");
    Pop(S, idx);
    printf("    the winner is: %d\n", idx);
    Pop(S, idx);
    printf("the last loser is: %d\n", idx);
    
    DestroyQueue(Q);
    return OK;
}
