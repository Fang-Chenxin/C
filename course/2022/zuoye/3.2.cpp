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

}Node, *LinkList;

  

//===========================================

// Create a singly linked list L with head node, and with n elements

//===========================================

Status CreateList_L(LinkList &L, int a[ ], int n)

{
    Node *r;

    int i;

    L = (Node *)malloc(sizeof(Node));   /*申请头结点空间  */

    if(!L) return ERROR;

    L->next = NULL;                  /*初始化一个空链表  */

    r = L;                          /*r始终指向终端结点，开始时指向头结点*/

    i = 0;
    while(i < n)

    {  

        Node *p;  

       p = (Node *)malloc(sizeof(Node));   /*申请新的结点空间 */

       if(!p) return ERROR;

    p->data = a[i];
    r->next = p;r = p;

    i++;
    }
    r->next = NULL;
 
    return OK;
}



//===========================================

//  delete the kth element from the end

//===========================================

void Delete_K(LinkList &L,int k,int n)
{
int x;
x = n-k+1;
 Node *p,*q; /* q为前驱结点，p为查找的结点*/

       int j;

        p = L;j = 0;
        
        while (p->next && j < x-1) {p = p->next;++j;}
 

    q = p->next;p->next = q->next;free(q);
 

}





//======================================

// Print the elements in a list

//=======================================

void LinkedListPrint(LinkList L)

{
   Node *start;


    for(start = L->next; start != NULL; start = start->next)  

        printf("%d ",start->data);  

    printf("\n");

        free(start);


}





int main()   

{   
int length,i,K;
LinkList L;
scanf("%d",&length);
int a[length];
for(i=0;i<length;i++)
{
    scanf("%d",&a[i]);
}
CreateList_L(L,a,length);
scanf("%d",&K);
Delete_K(L,K,length);
LinkedListPrint(L);
} 