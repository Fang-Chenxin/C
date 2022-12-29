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
  /*��ʼ����ռ�Ĵ�С*/
#define LISTINCREMENT 10   
/*��������*/

typedef int ElemType;


typedef struct{
    ElemType *elem; 
    int length;
    int listsize;
}SqList;
/*ElemType elem[INIT_SIZE],ע�������𡣴洢�ռ����ʼ��ַ��*/
/*���Ա�������Ԫ�ظ���������*/
/*���Ա�������Ĵ洢�ռ�Ĵ�С*/

int Init_Sq(SqList &L)
/*����һ���յ����Ա�*/
{
	
L.elem=(int *) malloc(100*sizeof(int));
L.length = 0;
L.listsize = 100;

return 1;

//��д���� 

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
//��д���� 

}

 

void InsertList_Sq(SqList *L, int i, ElemType e)
/*�����Ա�ĵ�i��λ��ǰ����Ԫ��e*/
{  int * newbase,*q,*p;
    if ((i<1)||(i>L->length+1)) {exit(ERROR);}  // ����³���� 
    if (L->length>=L->listsize)  /*��ǰ�ռ����������ӷ���ռ�*/
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

//��д���� 
}


void DeleteList_Sq(SqList *L, int i)
/* ɾ�����Ա��еĵ�i��Ԫ��*/
{   	
	int *q,*p,*j;
    if ((i<1)||(i>L->length)) {exit(ERROR);}  // ����³���� 

q=&(L->elem[i-1]);
p=&(L->elem[L->length-1]);


for(j=q+1;j<=p;++j)
*(j-1)=*j;

L->length--;
    
//��д���� 

}



void Print_Sq(SqList L)
/*����˳�����Ա����*/
{   
int i;

for(i=0;i<L.length;i++)
{
  printf("%d ",L.elem[i]);
}
//��д���� 

}




int LocateElem(SqList L,int e)
{
	
for(int i=0;i<L.length;i++)
{
	if (L.elem[i]==e) return ++i;
	
}
//��д���� 

return 0;

}



int main()
/*������*/
{  int i;
   int n;
   int a[n];
   SqList Lq;
 
   Init_Sq(Lq);
 	printf("����Ԫ�ظ���\n");
	scanf("%d",&n);
	printf("�������Ԫ��\n");
	for(i=0;i<n;i++)
	{
    	scanf("%d",&a[i]);
	}

   CreateList_Sq(Lq,a,n);
   printf("��ʼ˳���Ϊ\n");
   Print_Sq(Lq) ;
   
   InsertList_Sq(&Lq,3,67);
   printf("\n����67��˳���Ϊ\n");
   Print_Sq(Lq) ;
   
   DeleteList_Sq(&Lq, 2);
   printf("\nɾ����2��Ԫ�غ�˳���Ϊ\n");
   Print_Sq(Lq);
   

  printf("\n67��λ����%d",LocateElem(Lq,67));

return 1;
}

