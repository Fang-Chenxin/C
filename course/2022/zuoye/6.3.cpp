#include <stdio.h>   

#include <stdlib.h>   

#include <malloc.h>



#define ERROR 0

#define OK 1

#define TRUE 1

#define FALSE 0

typedef int ElemType;   

typedef int Status;



  

// definition of node structure of singly linked list

typedef struct L_node

{   

    ElemType data;           // data field 

    struct L_node *next;       // pointer field

}LNode, *LinkedList;

  

//===========================================

// Initialize  a singly linked list L with head node

//===========================================

Status InitList_L(LinkedList &L)

{

    L = (LinkedList)malloc(sizeof(LinkedList));
    if (!L) return ERROR;
    L->data = NULL;
    L->next = NULL;
    return OK;

}

 

//===========================================

// Create a singly linked list L with head node, and with n elements

//===========================================

Status CreateList_L(LinkedList &L, ElemType a[ ], int n)

{
    static LNode *p,*q;
    q = L;
    if (n == 0) return OK;
        CreateList_L(L,a,n-1);
        p = (LNode *)malloc(sizeof(LNode));
        if (!p) return ERROR;
        q->next = p;
        p->data = a[n-1];
        p->next = NULL;
        q = p;
    return OK;
}



//===========================================

// 合并两个有序单链表，返回最终链表的头指针

//===========================================

LinkedList MergeLinkList(LinkedList L1, LinkedList L2)

{
    ElemType data[10];
    LinkedList L;
    InitList_L(L);
    int i;
    i = 0;
    while(L1->next || L2->next)
    {
        if (L1->data > L2->data)
        {
            data[i] = L1->data;
            L1 = L1->next;
            i++;
        }
        else if (L2->data > L1->data)
        {
            data[i] = L2->data;
            L2 = L2->next;
            i++;
        }
    }    
    CreateList_L(L,data,i);
    return L;
}

//======================================

// Print the elements in a list

//=======================================

void LinkedListPrint(LinkedList L)

{
    L = L->next;
    while (L)
    {
        printf("%d ",L->data);
        L = L->next; 
    }

}





int main()   

{   
    int n1,n2,i;
    LinkedList L1,L2;
    InitList_L(L1);
    InitList_L(L2);
    scanf("%d",&n1);
    int a1[n1];
    for (i = 0 ;i<n1 ;i++) scanf("%d",&a1[i]);
    scanf("%d",&n2);
    int a2[n2];
    for (i = 0 ;i<n2 ;i++) scanf("%d",&a2[i]);
    CreateList_L(L1,a1,n1);
    CreateList_L(L2,a2,n2);
    LinkedListPrint(MergeLinkList(L1,L2));


}  