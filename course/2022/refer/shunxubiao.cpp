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
    ElemType *elem; 
    int length;
    int listsize;
}SqList;
/*ElemType elem[INIT_SIZE],注两者区别。存储空间的起始地址。*/
/*线性表中数据元素个数，即表长*/
/*线性表所申请的存储空间的大小*/

int Init_Sq(SqList &L)
/*创建一个空的线性表*/
{
	
L.elem=(int *) malloc(100*sizeof(int));
L.length = 0;
L.listsize = 100;

return 1;

//填写完整 

}



int CreateList_Sq(SqList &L, int a[], int n)

{
	int i;
   for(i=0;i<n;i++)
	{
	  L.elem[i] =a[i];
   	  L.length++;
	}
	
	return 1;
//填写完整 

}

 

void InsertList_Sq(SqList *L, int i, ElemType e)
/*在线性表的第i个位置前插入元素e*/
{  int * newbase,*q,*p;
    if ((i<1)||(i>L->length+1)) {exit(ERROR);}  // 程序鲁棒性 
    if (L->length>=L->listsize)  /*当前空间已满，增加分配空间*/
    {
        newbase=(ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if (!newbase) exit(ERROR);
        L->elem=newbase;
        L->listsize= L->listsize+LISTINCREMENT;
    }                                                                                    

q=&(L->elem[i-1]);
      
for (p=&(L->elem[L->length-1]);p>=q;--p)
{
	*(p+1)=*p;
}

*q=e;
L->length++;

//填写完整 
}


void DeleteList_Sq(SqList *L, int i)
/* 删除线性表中的第i个元素*/
{   	
	int *q,*p,*j;
    if ((i<1)||(i>L->length)) {exit(ERROR);}  // 程序鲁棒性 

q=&(L->elem[i-1]);
p=&(L->elem[L->length-1]);


for(j=q+1;j<=p;++j)
*(j-1)=*j;

L->length--;
    
//填写完整 

}



void Print_Sq(SqList L)
/*遍历顺序线性表并输出*/
{   
int i;

for(i=0;i<L.length;i++)
{
  printf("%d ",L.elem[i]);
}
//填写完整 

}




int LocateElem(SqList L,int e)
{
	
for(int i=0;i<L.length;i++)
{
	if (L.elem[i]==e) return ++i;
	
}
//填写完整 

return 0;

}



int main()
/*主函数*/
{  int i;
   int n;
   int a[n];
   SqList Lq;
 
   Init_Sq(Lq);
 	printf("输入元素个数\n");
	scanf("%d",&n);
	printf("逐个输入元素\n");
	for(i=0;i<n;i++)
	{
    	scanf("%d",&a[i]);
	}

   CreateList_Sq(Lq,a,n);
   printf("初始顺序表为\n");
   Print_Sq(Lq) ;
   
   InsertList_Sq(&Lq,3,67);
   printf("\n插入67后顺序表为\n");
   Print_Sq(Lq) ;
   
   DeleteList_Sq(&Lq, 2);
   printf("\n删除第2个元素后顺序表为\n");
   Print_Sq(Lq);
   

  printf("\n67的位置是%d",LocateElem(Lq,67));

return 1;
}

