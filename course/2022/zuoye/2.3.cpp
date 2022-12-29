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

#define LISTINCREMENT 10  

typedef int ElemType;

typedef struct{

    ElemType *elem;

    int length;

    int listsize;

}SqList;

// Create an empty list

Status InitList_Sq(SqList &L)

{
    L.elem=(ElemType*)malloc(INIT_SIZE*sizeof(ElemType));
    if(!L.elem) return ERROR;
    L.length=0;
    L.listsize=INIT_SIZE;
    return OK;
}



//Create an array based list with n elements

Status CreateList_Sq(SqList &L, int a[], int n)

{
    int i;
    if(n>L.listsize) return ERROR;
    for(i=0;i<n;i++)
    {
        
        L.elem[i]=a[i];
        L.length++;
    }
    return OK;


}



// Get the maximum element of sequential list L

Status MaxList_Sq(SqList L, ElemType &max_element, int &max_num)

{    
    int i;
    max_element=0;
    max_num=0;
    for(i=0;i<L.length;i++)
    {
        if(L.elem[i]>max_element)
        {
            max_element=L.elem[i];
            max_num=i; 
        }
    }
         
return OK;
}





int main()

{ 
    int i,n;
    int max,m;
    scanf("%d",&n);
    ElemType a[n];
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    SqList L;
    InitList_Sq(L);
    CreateList_Sq(L,a,n);
    MaxList_Sq(L,max,m);
    printf("%d %d",max,m+1);


}

