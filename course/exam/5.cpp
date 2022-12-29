/* 利用队列编写程序模拟计算机操作系统的分时任务调度。

结构体QElemType定义了队列中任务的各个数据元素，其中成员id为任务编号，cycle为任务需要消耗的CPU计算资源，rescycle记录任务完成还需要的CPU计算资源，wait统计任务完成总共等待的调度周期。
函数create_task（int id, QElemType *t）用于生成随机任务，参数id为任务id，t为新生成的任务。新生成任务的cycle及rescycle为[1,CYCLEMAX]之间的随机数，wait初始化为0。

已知计算机的CPU核数为N，则被调度任务（即出队列任务）的rescycle值将减少N，如果该任务的rescycle值仍大于0，则需要将该任务重新入队列等待下次调度，如果小于等于0，则该任务完成并将recycle赋值0。如图所示，假设CPU核数为4，程序初始化后开始。队列头成员a0出队列后，判断（recycle-4=3）仍大于0，a0重新入队列。每个调度周期需要更新队列中所有成员的wait值，即wait值加1变为1。

补全函数说明如下：
（1）int EnQueue(LinkQueue &Q, QElemType t)
入队列基本操作。
（2）int ProcQueue(LinkQueue &Q, QElemType &t, int N)
取出队列元素将rescycle减 N，判断rescycle值是否大于0，如果大于0则将任务重新入队列，否则将recycle赋值为0。
（3）int QueueTraverse(LinkQueue &Q)
遍历队列中所有成员并将其wait值加1。
 */

#include <stdio.h>
#include <stdlib.h>

#define TASKMAX 10
#define CYCLEMAX 10
#define TASKINIT 5
#define OK 1
#define ERROR 0

typedef struct
{
    int id;       // task id
    int cycle;    // task complexity: cpu cycles
    int rescycle; // count residual cpu cycles
    int wait;     // count the wait times to finish task
} QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
    int len;
} LinkQueue;

/***  create random new task  ***/
int create_task(int id, QElemType &t)
{
    t.id = id;
    t.cycle = rand() % CYCLEMAX + 1;
    t.rescycle = t.cycle;
    t.wait = 0;
    return OK;
}

/* Initialize a link queue */
int InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
        return ERROR;
    Q.front->next = NULL;
    Q.len = 0;
    return OK;
} // InitQueue

/* insert element to link queue */
int EnQueue(LinkQueue &Q, QElemType t)
{
    QueuePtr q;
    q = (QNode *)malloc(sizeof(QNode));
    if (!q)
        return ERROR;
    q->data = t;
    q->next = NULL;
    Q.rear->next = q;
    Q.rear = q;
    Q.len++;
    return OK;
}

/* delete element from link queue */
int DeQueue(LinkQueue &Q, QElemType &t)
{
    QueuePtr p;
    if (Q.front == Q.rear)
        return ERROR;
    p = Q.front->next;
    t = p->data;
    Q.front->next = p->next;
    Q.len--;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}

/* process the task in link queue */
int ProcQueue(LinkQueue &Q, QElemType &t, int N)
{
    /*补全函数*/
    QueuePtr q;
    q = Q.front->next;
    q->data.rescycle -= N;
    if (q->data.rescycle <= 0)
    {
        q->data.rescycle = 0;
        DeQueue(Q, t);
    }
    else
    {
        DeQueue(Q,t);
        EnQueue(Q,t);
    }
    return OK;
}

/* traverse link queue to update the element value of wait by adding one */
int QueueTraverse(LinkQueue &Q)
{
    /*补全函数*/
    QNode *q;
    q = Q.front->next;
    while (q)
    {
        q->data.wait++;
        q = q->next;
    }
    return OK;
}

int main()
{

    int i;
    int N;
    int taskid;
    QElemType t;
    LinkQueue Q;
    InitQueue(Q);
    for (i = 1; i <= TASKINIT; i++)
    {
        create_task(i, t);
        EnQueue(Q, t);
    }

    taskid = TASKINIT + 1;
    printf("Please input the number of CPU cores of your computer: ");
    scanf("%d", &N);

    while (Q.front != Q.rear)
    {
        ProcQueue(Q, t, N);
        if (t.rescycle == 0)
            printf("task %4d with %4d cycles has finished and wait %4d schedule times.\n", t.id, t.cycle, t.wait);

        QueueTraverse(Q);
        if (taskid <= TASKMAX)
        {
            create_task(taskid, t);
            EnQueue(Q, t);
            taskid++;
        }
    }

    return 0;
}
