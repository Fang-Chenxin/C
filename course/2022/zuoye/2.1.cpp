#include <malloc.h>

#include <stdio.h>

#include <stdlib.h>

 

#define TRUE  1

#define FALSE  0

#define OK 1

#define ERROR 0

#define OVERFLOW -2

typedef int Status;

 

#define INIT_SIZE 100

  /*初始分配空间的大小*/

#define LISTINCREMENT 10  

/*分配增量*/

 

typedef int ElemType;

 

typedef struct{

    ElemType  *elem;  //存放线性表元素的一维数组
    int length;  //线性表长度
    int listsize;  //当前分配的存储容量


}SqList;

/*存储空间的起始地址。*/

/*线性表中数据元素个数，即表长*/

/*线性表所申请的存储空间的大小*/

 

SqList CreateList_Sq(SqList L)

/*创建一个空的线性表*/

{
   L.elem=(ElemType *)malloc(INIT_SIZE*sizeof(ElemType));/*malloc 申请空间*/
   //if(!L.elem)  return ERROR;//存储分配失败
   L.length=0;/*表长为0*/
   L.listsize=INIT_SIZE;/*申请的空间为初始大小*/
   return   L;

}

 

 

void InsertList_Sq(SqList *L, int i, ElemType e)

/*在线性表的第i个位置前插入元素e*/

{  int * newbase,*q,*p;

    if ((i<1)||(i>L->length+1)) {printf("i值不合法!\n");exit(ERROR);}

    if (L->length>=L->listsize)  /*当前空间已满，增加分配空间*/

    {

        newbase=(ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));

        if (!newbase) exit(ERROR);

        L->elem=newbase;

        L->listsize=L->listsize+LISTINCREMENT;

    }

    q=&(L->elem[i-1]);                      //q为插入位置
    for(p=&(L->elem[L->length-1]);p>=q;--p) *(p+1)=*p;//插入位置及之后的元素后移
    *q=e;                                        //插入
    ++L->length;                              //表长增1
    //return OK;

}

 

void DeleteList_Sq(SqList *L, int i)

/* 删除线性表中的第i个元素*/

{         

    int *q,*p;

    if ((i<1)||(i>L->length)) {printf("i值不合法!\n");exit(ERROR);}

     p=&(L->elem[i-1]);                                 //p为被删除元素的位置
    // e=*p;                                                     //被删除元素的值赋给e
     q=L->elem+L->length-1;                          //表尾元素的位置
     for(++p; p<=q; ++p)  *(p-1)=*p;          //被删除之后的元素前移
     --L->length;                                            //表长减1
    // return OK;


 

}

 

 

void Print_Sq(SqList L)

/*遍历顺序线性表并输出*/

{   int i;

    for(i=0;i<L.length;i++)

    {

       printf("%3d ",L.elem[i]);

    }

}

 

 

int equal(ElemType e1,ElemType e2)

/*判两个元素是否相等*/

{

    if (e1==e2) return 1;

    else return 0;

}

 

int LocateElem_Sq(SqList L,ElemType e, int (* compare)(ElemType e1,ElemType e2))

{   int i;
    ElemType *p;

    i=1;
    p=L.elem;
    while(i<L.length && !((*compare)(*p++,e)))   ++i;
    if(i<=L.length) return i;
    else return 0;
}

 

void Getelem(SqList L,int i,ElemType *e)

{

    *e=L.elem[i];

}



int main()

/*主函数*/

{  int i;

   SqList Lq;

   Lq=CreateList_Sq(Lq);

   InsertList_Sq(&Lq,1,21);

   InsertList_Sq(&Lq,2,18);

   InsertList_Sq(&Lq,3,30);

   InsertList_Sq(&Lq,4,75);

   InsertList_Sq(&Lq,5,42);

   InsertList_Sq(&Lq,6,56);

   printf("初始顺序表为\n");

   Print_Sq(Lq) ;

   InsertList_Sq(&Lq,3,67);

   printf("\n插入67后顺序表为\n");

   Print_Sq(Lq) ;

   DeleteList_Sq(&Lq, 6);

   printf("\n删除第6个元素后顺序表为\n");

   Print_Sq(Lq);

   if ((i=LocateElem_Sq(Lq,75,equal)))

 

       printf("\n存在元素75且位置为%d\n",i);

   else

 

        printf("\n不存在元素75\n");

free(Lq.elem);

return 1;

}