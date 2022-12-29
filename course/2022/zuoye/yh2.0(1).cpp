#include <iostream>

#include <string.h>

#include <time.h>

#include <stdio.h>

using namespace std;

int closeTime; //营业结束时间

int arriveTime; //两个到达事件之间的间隔上限

int dealTime; //客户之间交易的时间上限

int dealMoney = 5000; //交易额上限

int currentTime = 0; //当前时间

double totalTime = 0; //客户逗留总时间

double counter = 0; //客户总数

int number = 1; //初始客户序列号

long amount = 10000;

bool state = 1; //用于判断是否有窗口在处理

int currentTimeOfDeal = 0;

int judgetime=0;
int judgetime2=0;
 

#define ERROR 0;
#define OK 1;

  //文件读写初始化
FILE * pFile;//文件指针
int days,i,j;
float all,temp;
char *buffer,num[20];//读入暂存

//初始化三个队列
struct service

{

  int num; //客户号

  char type[20]; //到达或离开

  int beginTime;

  int endTime;

  long money; //正数为存款，负数为取款

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
  if (!(q.head && q.rear))
    return ERROR;
  q.head->next = NULL;
  return OK;
}

void push(queue &q, int d) // fq用这个

{ // 插入元素d为Q的新的队尾元素,d是service里的money
  service *p;
  p = (service *)malloc(sizeof(service));
  p->next = NULL;
  if (!p)
    exit(0);
  p->money = d;
  p->num = number;

  q.rear->next = p;
  q.rear = p;
}
void pop(queue &q)

{ // 若队列不空,出对列函数，只是单纯的出队列
  service *p;
  p = q.head->next;
  if (p->next)
    q.head->next = p->next;
  if (q.rear == p)
  {  q.rear = q.head;q.head->next=NULL;}
  free(p);
}

void pusheq(queue &aq, service *q)
{ // q为要进入eq队列的人 ；eq,sq用这个
  service *p;
  p = (service *)malloc(sizeof(service));
  p->next = NULL;
  	p->money = q->money;
  p->num = q->num;
  p->beginTime = q->beginTime;
  p->endTime = q->endTime;

  aq.rear->next = p;
  aq.rear = p;
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
  int t;
  t = 1;
  while (p )
  {

    if (p->money + amount > 0)
      return t;
    t++;
    p = p->next;
  }
  return 0;
}

void putMoney(queue &q);
void getMoney();

void arrive(queue &q)

{ /*"到达"函数 随机产生顾客，进入队列一

 产生到达事件 进入事件队列*/
  printf("请输入要存/取钱的金额，存钱为正数，取钱为负数\t");
  scanf("%d", &dealMoney);
  push(q, dealMoney);
  pusheq(eq, q.rear);
  state = 1;
  
  strcpy(back(eq)->type, "到达");

  back(fq)->beginTime = arriveTime;
  back(eq)->beginTime = arriveTime;
}
int randomTemp;
void putMoney(queue &q)

{ /*存款函数 ,
需要 ：更新资金总额 加入事件队列 离开 更新客户总数（未完成）
更新逗留时间 删除第一队列第一个业务（已完成）*/
  if(front(fq)->endTime<closeTime)
  amount = amount + front(fq)->money;
  pusheq(q, front(fq));
  counter++;

  //---------------------------------------------------------------------

  printf("请输入序号为%d的客户的存钱时间:\t", number - 1);

  scanf("%d", &dealTime);
  if(judgetime<front(fq)->beginTime||judgetime==0)
  back(eq)->endTime = (front(fq)->beginTime + dealTime);
  else
  back(eq)->endTime = (judgetime + dealTime);
  

  
  
 if(back(eq)->beginTime<closeTime)
  pop(fq); //删除第一队列第一个业务

  strcpy(back(eq)->type, "离开");
  judgetime=back(eq)->endTime;

  currentTimeOfDeal = back(eq)->endTime;
  randomTemp=back(eq)->endTime;
  totalTime += (back(eq)->endTime - back(eq)->beginTime); //更新逗留时间
  state = 0;
}

void getMoney()

{ /*取款函数，若资金短缺 加入第二队列，
 需要：加入事件队列 离开 更新客户总数
 更新逗留时间 删除第一队列第一个业务*/
 if(front(fq)->endTime<closeTime)
  amount = amount + front(fq)->money;

  if (-front(fq)->money > amount)
  { //资金短缺
    pop(fq);
    pusheq(sq, front(fq));
    back(sq)->beginTime = front(fq)->beginTime;
  }

  else
  {
    pusheq(eq, front(fq));
    counter++;
    strcpy(back(eq)->type, "离开");

    //-------------------------------

    printf("请输入序号为%d的客户的取钱时间:\t", back(eq)->num);

    scanf("%d", &dealTime);
  if(judgetime<back(eq)->endTime||judgetime==0)
  back(eq)->endTime = (front(fq)->beginTime + dealTime);
  else
   back(eq)->endTime = (judgetime + dealTime);
    judgetime=back(eq)->endTime;

    back(eq)->beginTime = 0;

    currentTimeOfDeal = back(eq)->endTime;

    totalTime += (back(eq)->endTime - back(eq)->beginTime); //更新逗留时间
    if(back(eq)->beginTime<closeTime)
    pop(fq); //删除第一队列第一个业务

    state = 0;
  }
}



void findAndDeal()

{ /*在对列中寻找可处理元素，对其进行处理，
 需要查找可处理取款，更新资金总额，加入事件队列 离开，（未完成）
 更新逗留时间(已完成) */
  int dealn;

  while (dealn = search(sq, amount))
  { // search如果没有返回0，有符合的返回要处理的人在sq的第几个
    counter++;
    
    int i;
    service *p, *t;
    p = sq.head;
    
    for (i = 1; i < dealn; i++)
    {
      p = p->next;
    }
    amount = amount + p->next->money;

    t = p->next;
    pusheq(eq, p->next);
    strcpy(back(eq)->type, "离开");
    //删除该结点
    if (dealn == 1 || (!p->next->next->num))
      p->next = NULL;
    else
      p->next = p->next->next;
    free(t);

    //-------------------------------------------------------------

    printf("请输入序号为%d的客户的取钱时间:\t", dealn);

    scanf("%d", &dealTime);


    back(eq)->endTime = dealn + randomTemp;

    currentTimeOfDeal += randomTemp;

    totalTime += (back(eq)->endTime - back(eq)->beginTime); //更新逗留时间
    judgetime=back(eq)->endTime;

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

  int arrivet;

  buffer = (char *)malloc(sizeof(char));
  pFile = fopen ("amount.txt","r");
  fseek(pFile,-1,SEEK_END);
  while(*buffer!=' ')
  {
    fseek(pFile,-2,SEEK_CUR);
    fread(buffer,sizeof(char),1,pFile);
    //printf("%c",*buffer);
  }

  while(1)
  {
      fread(buffer, sizeof(char), 1,pFile);
      if (*buffer!='\n')
      {
          //printf("%c", *buffer);
          num[j] = *buffer;
          j++;
      }
      else
      {
          printf("\n");
          amount = atoi(num);
          printf("当前银行金额：%d\n",amount);
          break;
      }
  }
  fclose(pFile);


  while (1)

  {

    printf("输入银行的营业时间：\t");

    scanf("%d", &closeTime);

    printf("请输入第1位客户到达的间隔时间：\t");
    scanf("%d", &arriveTime);

    currentTime += arriveTime; //首次到达时间

    while (currentTime < closeTime)

    {
      if (number != 1)
      {
        printf("请输入第%d位客户到达的间隔时间：\t", number);
        scanf("%d", &arrivet);
        currentTime += arrivet;
        arriveTime+=arrivet;
        
      }
      //到达事件
      if (currentTime < closeTime)
      {
        if (number == 1)
        {
          arrive(fq);
          number++;
        }
        else
        {

          arrive(fq);
//          currentTime += arriveTime;
          number++;
        }
      }

      if (1 == state && NULL != fq.head)

      {

        if (fq.head->next->money >= 0)

        {

          putMoney(eq);

          findAndDeal(); //处理
        }

        else if (fq.head->next->money + amount >= 0)
          getMoney();

        else
        {
          pusheq(sq, back(fq));
          pop(fq);
        }
      }
    }

    cout << endl
         << "客户序列"
         << "\t"
         << "事件类型"
         << "\t\t"
         << " 时间"
         << "\t\t"
         << " 处理金额" << endl;

    while ((NULL != eq.head->next) && (eq.head->next->num > 0)) //清除事件队列

    {

      if (strcmp(eq.head->next->type, "离开") == 0)

        cout << eq.head->next->num << "\t\t" << eq.head->next->type << "\t"
             << "\t\t" << eq.head->next->endTime << "\t\t" << eq.head->next->money << endl;

      if (strcmp(eq.head->next->type, "到达") == 0)

        cout << eq.head->next->num << "\t\t" << eq.head->next->type << "\t"
             << "\t\t" << eq.head->next->beginTime << "\t\t" << eq.head->next->money << endl;

      pop(eq);
    }

    cout << "未处理客户:"
         << "" << endl;

    while (NULL != fq.head->next)

    {

      totalTime += (closeTime - fq.head->next->beginTime);  //更新结束时第一队列中未处理的客户

      cout << fq.head->next->num << " " << endl;

      ++counter;

      pop(fq);
    }
    while (NULL != sq.head->next)

    {

      totalTime += (closeTime - sq.head->next->beginTime); //更新结束时第一队列中未处理的客户

      cout << sq.head->next->num << " " << endl;

      ++counter;

      pop(sq);
    }

    printf("客户逗留平均时间为: %.4f\n", totalTime / (counter));

    cout << "银行当前余额：" << amount << endl;

    break;
  }

  pFile = fopen("amount.txt","a");
  fprintf(pFile,"银行当前余额： %d\n",amount);
  fclose(pFile);

  pFile = fopen ("myfile.txt","r+");
  fseek(pFile,0,SEEK_END);
  fprintf (pFile, "客户逗留平均时间为 %.4f\n",totalTime / (counter));
  fseek(pFile,0,SEEK_SET);
  i = 0;j = 0;all = 0;
  for (i=0;i<20;i++)
    num[i]=0;
  while(1)//获取读入数据数量
  {
      fread(buffer, sizeof(char), 1,pFile);
      if (*buffer!='\n')
      {
          //printf("%c", *buffer);
          num[j] = *buffer;
          j++;
      }
      else
      {    
          days = atoi(num);
          printf("\n与前%d日一起计算平均逗留时间\n", days);
          break;
      }
  }
  days++;//加上当前数据
  fseek(pFile,0,SEEK_CUR);
  for(i=0;i<days;i++)
  {
      j = 0;
      printf("第%d日平均逗留时间:",i+1);
      fseek(pFile,28,SEEK_CUR);
      while(1)
      {
          fread(buffer, sizeof(char), 1,pFile);
          if (*buffer!='\n')
          {
              printf("%c", *buffer);
              num[j] = *buffer;
              j++;
          }
          else
          {
              printf("\n");
              temp = atof(num);
              all += temp;
              break;
          }
      }
  }
  
  fseek(pFile,0,SEEK_SET);
  fprintf (pFile, "%d\n",days);
  fclose (pFile);
  printf("平均时间%.4f",all/days);

  return 0;
}
