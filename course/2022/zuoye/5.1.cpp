#include <stdio.h>  

#include <stdlib.h>  

#include <malloc.h>

#define ERROR 0

#define OK 1

#define TRUE 1

#define FALSE 0

typedef int QElemType;  

typedef int Status;

 

// definition of array based queue

#define MAXQSIZE  100   // maximum length

typedef struct {

   QElemType     *base;   //pointer the allocated memory

   int  front;                    //front indicator

   int  rear;                     //rear indicator

}SqQueue; 

 

 

//========================================== 

// initialization of array-based queue

//=========================================== 

Status InitQueue (SqQueue &Q){
   Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
   if (!Q.base) return ERROR;
   Q.front = 0;
   Q.rear = 0;   
   return OK;
}//InitQueue

 

//========================================

//Test empty queue

//========================================

Status QueueEmpty (SqQueue Q){

    if(Q.front == Q.rear)
      return TRUE;
   return FALSE;

}

 

//===============================================

// Get the length of a queue

//==============================================

int QueueLength (SqQueue Q){

   return (Q.rear-Q.front+MAXQSIZE) % MAXQSIZE;

}

 

//=====================================

// Get front item of a queue

//====================================

Status GetHead (SqQueue Q, QElemType &e){

   if (QueueEmpty)
      return ERROR;
   e = *Q.base;
   return OK;

}

 

//===================================================

// Delete an item from the queue

//====================================================

Status DeQueue(SqQueue &Q,QElemType &e){

   if(QueueEmpty(Q))
      return ERROR;
   e = Q.base[Q.front];
   Q.front++;
   return OK;

}

 

//======================================

// Insert an item into the queue

//=======================================

Status EnQueue (SqQueue &Q, QElemType e){

   if(QueueLength(Q)+1 >= MAXQSIZE)
      return ERROR;
   Q.base[Q.rear] = e;
   Q.rear++;
   return OK;
}

 

//========================================

//Clear a Queue

//===========================================

Status ClearQueue (SqQueue &Q){

   Q.front = Q.rear;
   return OK;
}

 

//======================================

// Print the elements in a queue

//=======================================

void PrintQueue (SqQueue S){

   while (S.front != S.rear)
   {
      printf("%d ",S.base[S.front]);
      S.front++;
   }
   
}

 

int main()  

{  
   SqQueue Q;
   QElemType e;
   int n,i;
   InitQueue(Q);
   while (e != -1)
   {
      scanf("%d",&e);
      EnQueue(Q,e);
   }
   Q.rear--;
   PrintQueue(Q);
   printf("\n%d\n",QueueLength(Q));
   scanf("%d",&n);
   for (i=0;i<n;i++)
   {
      DeQueue(Q,e);
      //printf("%d",e);
   }
   PrintQueue(Q);


}

