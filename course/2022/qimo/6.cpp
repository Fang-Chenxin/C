#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

#define VEXNUM 8 /* 顶点数量 */
#define MAX_VERTEX_NUM 20 /* 最大顶点数量 */
#define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
#define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */

typedef struct {
    char name[MAX_NAME]; /* 城市名称 */
    int infectnum;  /* 感染者数量 */
    int flag;  /* 游戏回合中是否爆发过疫情：1：是；0：否 */    
} VertexType;  /* 顶点类型 */

typedef int VRType;
typedef char InfoType;
 
typedef enum{DG,DN,UDG,UDN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct
{
    VRType adj;  /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
                /* 对带权图，c则为权值类型 */
    InfoType *info; /* 该弧相关信息的指针(可无) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];  /* 顶点数组 */
    AdjMatrix arcs;     /* 邻接矩阵 */
    int vexnum,arcnum; /* 图的当前顶点数和弧数 */
    GraphKind kind;   /* 图的种类标志 */
}MGraph;

int total;  /* 统计所有感染者数量 */

// 根据顶点的名称返回顶点的数组下标
int LocateVex(MGraph G, char *u)
 { /* 初始条件:图G存在,u和G中顶点有相同特征 */
   /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vexs[i].name)==0)
       return i;
   return -1;
 }

/* 初始化*/
void InitUDG(MGraph &G, int vexnum)
{
    int i,j;
    G.vexnum = vexnum;
printf("请依次输入%d个城市名称:", vexnum);


//请继续完成以下操作：
//1.构造顶点向量(读入顶点名称，并完成顶点数组的初始化） 
//2.初始化邻接矩阵
//3.初始化图结构体中的其他变量

    //★★★请补全代码

/* 构造顶点向量 */
for (i=0;i<vexnum;i++)
{
    for (j=0;j<MAX_NAME;j++)
        G.vexs[i].name[j] = NULL;
    scanf("%c",&G.vexs[i].name);
    getchar();
    G.vexs[i].flag=0;
    G.vexs[i].infectnum=0;
    // for (i=0;i<vexnum;i++)
    // {
    //     for (j=1;j<MAX_NAME;j++)
    //         G.vexs[i].name[j] = 0;
    // }
    
}




/* 初始化邻接矩阵 */
for (i=0;i<vexnum;i++)
{
    for (j=0;j<vexnum;j++)
    {
        G.arcs[i][j].adj = 0;
        G.arcs[i][j].info = NULL;
    }
}
G.arcnum=0;


/* 初始化图结构体的其他变量 */
G.kind=UDG;



}

/*创建邻接矩阵*/
void CreateAdjArray(MGraph &G, int *h, int vexnum)
{
  int i, j;
  for(i=0; i<vexnum; i++){
    for(j=0; j<vexnum; j++){
      if(*(h+i*vexnum+j)==1){
        G.arcs[i][j].adj=1;
        G.arcnum++;
      }
    }
  }  
}

/*输出图所有顶点相关信息*/
void Display(MGraph G)
{
  int i,j;
  /* printf("%d个顶点: \n",G.vexnum); */
  for(i=0;i<G.vexnum;++i)  /* 输出G.vexs */
    printf("%s(%d) ",G.vexs[i].name, G.vexs[i].infectnum);
  printf("\n");
}

typedef int QElemType;
/* 单链队列－－队列的链式存储结构 */
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{ /* 构造一个空队列Q */
   Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
   if(!Q.front)
     return ERROR;
   Q.front->next=NULL;
   return OK;
}

 Status EnQueue(LinkQueue &Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* 存储分配失败 */
     return ERROR;
   p->data=e;
   p->next=NULL;
   Q.rear->next=p;
   Q.rear=p;
   return OK;
 }

 Status DeQueue(LinkQueue &Q,QElemType &e)
 { /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   e=p->data;
   Q.front->next=p->next;
   if(Q.rear==p)
     Q.rear=Q.front;
   free(p);
   return OK;
 }

 Status QueueEmpty(LinkQueue Q)
 { /* 若Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear)
     return TRUE;
   else
     return FALSE;
 }


/* 游戏初始化 */
void InitGame(MGraph &G)
{
    int i;
    int idx;
    int infectnum;
    char cityname[MAX_NAME];
    printf("游戏初始化：\n");
    for(i=0; i<2; i++) //输入两个城市的名称及感染者数量并更新顶点信息
    {
       //★★★请补全代码
         printf("请输入城市和感染者数量：");
         int j;
         for (j=0;j<MAX_NAME;j++)
            cityname[j]=NULL;
        infectnum = 0;
        scanf("%c %d",&cityname,&infectnum);  
        getchar();     
        G.vexs[LocateVex(G,cityname)].infectnum = infectnum;
        total+=infectnum;
    }
    printf("目前有 %d 感染者\n", total);
}

/* 模拟游戏过程 */
void ProcGame(MGraph &G)
{
    int i,j,k,m;
    int idx;
    int cnt=1;
    char cityname[MAX_NAME];
    LinkQueue Q;
    InitQueue(Q); /* 置空的辅助队列Q */
    int flag = 0; /* 游戏结束标志 */
    k=1;
    printf("游戏开始:\n");
    while(!flag) {
        printf("第 %d 回合游戏:\n", k);
        for(i=0; i<G.vexnum;i++)
            G.vexs[i].flag = 0;

        printf("请输入增加病毒城市：");
        scanf("%s", cityname);
        idx=LocateVex(G, cityname);
        if(G.vexs[idx].infectnum==3)
        {   /* 疫情爆发 */ 
            m=1;
            EnQueue(Q, idx);
            while(!QueueEmpty(Q)) /* 队列不空 */
            {
                //★★★请补全代码
                DeQueue(Q,idx);
                printf("本回合第%d次疫情爆发，城市%c",m,G.vexs[idx].name);
               for (i=0;i<VEXNUM;i++)
               {
                    if (G.arcs[idx][i].adj==1)
                    {
                        if (G.vexs[i].flag==0 && G.vexs[i].infectnum==3)
                            EnQueue(Q,i);
                        if (G.vexs[i].infectnum<3)
                          G.vexs[i].infectnum ++;
                    }
               }
                m++;
                


                Display(G);
           } //while(!QueueEmpty(Q))
        }// if(G.vexs[idx].infectnum==3)
        else{
            G.vexs[idx].infectnum++;
            total++;
            printf("本回合无疫情爆发\n");
            Display(G);
        }

        if (total >= 3*G.vexnum)
            flag = 1;

        k++;
        printf("目前感染者数量：%d\n", total);
        printf("\n");
    } //while(!flag) 
    printf("游戏进行了 %d 回合，疫情爆发 %d 次\n", k-1, cnt);
}

int main()
{
    int i;
    MGraph G;
    int arcnum;
    char cityname[MAX_NAME];
    int infectnum;  /*  感染者数量 */
    int H[VEXNUM][VEXNUM]={
      {0,1,1,1,0,0,0,0},{1,0,1,0,0,1,0,0},{1,1,0,1,1,0,1,0},{1,0,1,0,0,1,1,1},
      {0,0,1,0,0,0,1,0},{0,1,0,1,0,0,0,0},{0,0,1,1,1,0,0,1},{0,0,0,1,0,0,1,0}
    }; /* 邻接矩阵（二维数组） */
    InitUDG(G, VEXNUM);
    Display(G);
    CreateAdjArray(G, &H[0][0], VEXNUM);
    printf("总共有 %d 条边\n", G.arcnum/2);
    printf("\n");
    fflush(stdin);
    InitGame(G);
    Display(G);
    printf("\n");
    fflush(stdin);
    ProcGame(G);
}
