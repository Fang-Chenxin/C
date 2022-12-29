

#include <string>

#include <time.h>

using namespace std;

int total; //初始时银行现存资金总额

int closeTime; //营业结束时间

int arriveTime; //两个到达事件之间的间隔上限

int dealTime; //客户之间交易的时间上限

int dealMoney = 5000; //交易额上限

int currentTime = 0; //当前时间

int totalTime = 0; //客户逗留总时间

int counter = 0; //客户总数

int number = 0; //初始客户序列号

int amount = 10000; //金额

bool state = 1; //用于判断是否有窗口在处理

int currentTimeOfDeal = 0;

int theArriveTime = 0;

//初始化三个队列
struct service

{

    int num; //客户号

    string type; //到达或离开

    int beginTime;

    int endTime;

    int money; //正数为存款，负数为取款

    service *next;
};

struct queue

{ //队列

    service *head;

    service *rear;
};
queue eq; //事件队列

queue fq; //队列一

queue sq; //队列二
int Initqueue(queue &q)
{
    q.head = q.rear = (service *)malloc(sizeof(service));
    q.head->next == NULL;
    return 1;
}

void push(queue &q, int d) // fq用这个

{ // 插入元素d为Q的新的队尾元素,d是service里的money
    service *p;
    p = (service *)malloc(sizeof(service));
    p->money = d;
    p->num = number;
    q.rear->next = p;
    q.rear = p;
}

void pop(queue &q)

{ // 若队列不空,出对列函数，只是单纯的出队列
    service *p;
    p = q.head->next;
    q.head->next = p->next;
    if (q.rear == p)
        q.rear = q.head;
    free(p);
}

void pusheq(queue &eq, service *q)
{ // q为要进入eq队列的人 ；eq,sq用这个
    service *p;
    p = (service *)malloc(sizeof(service));
    p->money = q->money;
    p->num = q->num;
    eq.rear->next = p;
    eq.rear = p;
}

service *front(queue &q)

{ //返回队首元素，已完成

    return q.head->next;
}

service *back(queue &q)

{ //返回队尾元素，已完成

    return q.rear;
}

int search(queue &q, int m)

{ //在队列中寻找是否有可处理元素
    service *p;
    p = front(sq);
    int n;
    n = 1;
    while (p)
    {
        if (p->money > m)
            return n;
        n++;
        p = p->next;
    }
    return 0;
}

void arrive(queue &q)

{ /*"到达"函数 随机产生顾客，进入队列一

 产生到达事件 进入事件队列*/
    int money;
    printf("请输入要存/取钱的金额，存钱为正数，取钱为负数\n");
    scanf("%d", money);
    push(q, money);

    back(fq)->beginTime = currentTime;
    back(eq)->beginTime = currentTime;
}

void putMoney(queue &q)

{ /*存款函数 ,
需要 ：更新资金总额 加入事件队列 离开 更新客户总数（未完成）
更新逗留时间 删除第一队列第一个业务（已完成）*/

    amount = amount + front(fq)->money;
    pusheq(q, front(fq));
    pop(fq);
    counter++;

    //---------------------------------------------------------------------

    printf("请输入序号为%d的客户的存钱时间", number - 1);

    scanf("%d", &dealTime);
    back(eq)->endTime = (front(fq)->beginTime + dealTime);

    ++counter; //更新客户总数

    totalTime += (back(eq)->endTime - front(fq)->beginTime); //更新逗留时间

    pop(fq); //删除第一队列第一个业务

    currentTimeOfDeal = back(eq)->endTime;

    state = 0;
}

void getMoney()

{ /*取款函数，若资金短缺 加入第二队列，
 需要：加入事件队列 离开 更新客户总数
 更新逗留时间 删除第一队列第一个业务*/

    if (-front(fq)->money > amount)
    { //资金短缺
        pop(fq);
        pusheq(sq, front(fq));
    }

    else
    {
        pusheq(eq, front(fq));
        counter++;
        pop(fq);

        //-------------------------------

        back(sq)->beginTime = front(fq)->beginTime;

        printf("请输入序号为%d的客户的取钱时间", number - 1);
        scanf("%d", &dealTime);

        back(eq)->endTime = (front(fq)->beginTime + dealTime);

        back(eq)->beginTime = 0;

        currentTimeOfDeal = back(eq)->endTime;

        totalTime += (back(eq)->endTime - back(fq)->beginTime); //更新逗留时间

        pop(fq); //删除第一队列第一个业务

        state = 0;
    }
}

service *temped; /*全局变量可能比较好，
temped用来存储删掉客户的信息，
并处理他的相关业务 */
int randomTemp;

void findAndDeal()

{ /*在对列中寻找可处理元素，对其进行处理，
 需要查找可处理取款，更新资金总额，加入事件队列 离开，（未完成）
 更新逗留时间(已完成) */
    int n;

    while (n = search(sq, amount))
    { // search如果没有返回0，有符合的返回要处理的人在sq的第几个

        int i;
        service *p, *t;
        p = sq.head;
        for (i = 1; i < n; i++)
        {
            p = p->next;
        }
        amount = amount - p->next->money;

        t = p->next;
        pusheq(eq, p->next);
        //删除该结点
        p->next = p->next->next;
        free(t);

        //-------------------------------------------------------------

        printf("请输入序号为%d的客户的取钱时间", n);

        scanf("%d", &dealTime);

        randomTemp = dealTime;

        back(eq)->endTime = currentTime + randomTemp;

        currentTimeOfDeal += randomTemp;

        totalTime += (back(eq)->endTime - temped->beginTime); //更新逗留时间
        delete temped;                                        //删除节点

        temped = NULL;

        state = 0;
    }
}

int main()

{
    Initqueue(fq);
    Initqueue(eq);
    Initqueue(sq);

    printf(" ********************************************\n");

    printf(" 欢迎进入银行模拟系统\n");

    printf(" ********************************************\n");


    while (1)

    {

        printf("输入银行的初始存款：\n");

        scanf("%d", &total);

        printf("输入银行的营业时间：\n");

        scanf("%d", &closeTime);

        printf("输入最大到达时间间隔：\n");

        scanf("%d", &arriveTime);

        printf("输入最大的处理时间：\n");

        scanf("%d", &dealTime);

        printf("请输入客户到达的间隔时间：\n");
        scanf("%d", &arriveTime);

        theArriveTime += arriveTime + 1; //首次到达时间

        while (currentTime < closeTime)

        {

            ++currentTime;

            if (currentTimeOfDeal < currentTime)
                currentTimeOfDeal = currentTime;

            if (currentTimeOfDeal == currentTime)
                state = 1;

            if (currentTime == theArriveTime) //到达事件

            {

                arrive(fq);
                number++;

                printf("请输入客户到达的间隔时间：\n");
                scanf("%d", &arriveTime);

                theArriveTime += arriveTime + 1;
            }

            if (1 == state && NULL != fq.head)

            {

                if (fq.head->money >= 0)

                {

                    putMoney(eq);

                    findAndDeal(); //处理
                }

                else

                    getMoney();
            }
        }

        cout << endl
             << "客户序列"
             << "\t"
             << "事件类型"
             << "\t\t"
             << " 时间"
             << "\t"
             << " 处理金额" << endl;

        while (NULL != eq.head) //清除事件队列

        {

            if (eq.head->type == "离开")

                cout << eq.head->num << "\t\t" << eq.head->type << "\t\t"
                     << "\t\t" << eq.head->endTime << "\t\t" << eq.head->money << endl;

            if (eq.head->type == "到达")

                cout << eq.head->num << "\t\t" << eq.head->type << "\t\t"
                     << "\t\t" << eq.head->beginTime << "\t\t" << eq.head->money << endl;

            pop(eq);
        }

        cout << "未处理客户:"
             << "" << endl;

        while (NULL != fq.head)

        {

            totalTime += (closeTime - fq.head->beginTime); //更新结束时第一队列中未处理的客户

            cout << fq.head->num << " " << endl;

            ++counter;

            pop(fq);
        }

        cout << "客户逗留平均时间为: " << totalTime / counter << endl;

        cout << "银行当前余额：" << total << endl;

        break;
    }

    return 0;
}
