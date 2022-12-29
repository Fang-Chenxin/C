
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef int Status; 
typedef  int QElemType; /*定义队列元素的类型*/
typedef struct QNode    /*定义队列单链表存储*/
{
    QElemType data;
    struct QNode *next;
} QNode,*QueuePtr;

typedef struct LinkQueue{
    QueuePtr front, rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front) 
        return ERROR;
    Q.front->next=NULL;
    return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
//★★★请补全代码
QNode *p;
p=(QNode *)malloc(sizeof(QNode));
p->data=e;
p->next=Q.rear->next;
Q.rear->next=p;
Q.rear=p;
return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if(Q.front==Q.rear)
        return ERROR;
    QueuePtr p;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    return OK;
}

//创建一个包含数字1,2,...,n的队列。
Status CreateQueue(LinkQueue &Q, int n)
{
    int i;
    InitQueue(Q);    
    for(i=1; i<=n; i++)
        EnQueue(Q, i);
    return OK;
}

void QueueTraverse(LinkQueue Q)
{
    QueuePtr p;
    p=Q.front->next;
    while(p){
        printf("%d ", p->data);
        p=p->next;
    }
}

Status DestroyQueue (LinkQueue &Q){
while(Q.front){
      Q.rear=Q.front->next;
      free(Q.front);
      Q.front=Q.rear;
   }    
   return OK;
}

// 将k-1个人员出队列，再重新入队列
Status Start(LinkQueue &Q, int k) /* 用于跳过k-1个人员 */
{
	//★★★请补全代码
    int i,tmp[k];
    for (i=1;i<k;i++)
    {
        DeQueue(Q,tmp[i]);
    }
    for (i=1;i<k;i++)
    {
        EnQueue(Q,tmp[i]);
    }
    return OK;
}

int main()
{
    int n,m;
    int idx;
    LinkQueue Q;
    scanf("%d%d",&n,&m);
    //printf("n=%d,m=%d\n",n,m);
    CreateQueue(Q, n);
    QueueTraverse(Q);
    printf("\n");
    Start(Q,m);
    QueueTraverse(Q);
    printf("\n");
    DestroyQueue(Q);
    return OK;
}
