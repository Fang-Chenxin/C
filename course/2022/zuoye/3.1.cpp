#include <stdio.h>  

#include <stdlib.h>  

#define ERROR 0

typedef int ElemType;  

 

 

/*定义结点类型*/

typedef struct  Node

{  

   ElemType       data;            /*单链表中的数据域 */

   struct Node  *next;        /*单链表的指针域*/

}Node,*LinkedList;

 

 

 

/*单链表的初始化*/

 

LinkedList LinkedListInit()  

{  

    Node *L;  

    L=(LinkedList) malloc(sizeof(Node));   /*申请结点空间*/

    if(L == NULL)                       /*判断是否有足够的内存空间*/

        printf("申请内存空间失败\n");

    L->next=NULL;          /*将next设置为NULL,初始长度为0的单链表*/

return L;

}  

 

 

/*单链表的建立，尾插法建立单链表*/

 

LinkedList LinkedListCreatT()  

{  

    Node *L,*r;

 int x;

    L = (Node *)malloc(sizeof(Node));   /*申请头结点空间  */

    L->next = NULL;                  /*初始化一个空链表  */

    r = L;                          /*r始终指向终端结点，开始时指向头结点*/

    while(scanf("%d",&x) != EOF)

    {  

        Node *p;  

       p = (Node *)malloc(sizeof(Node));   /*申请新的结点空间 */

    p->data = x;
    r->next = p;r = p;
    

    }  

    r->next = NULL;   

      

    return L;     

}  

 

 

/*单链表的插入，在链表的第i个位置插入x的元素*/

 

LinkedList LinkedListInsert(LinkedList L,int i,ElemType x)  

{  

    Node *pre;

    int tempi;                     /*pre为前驱结点*/

    Node *p;
    p = (LinkedList)malloc(sizeof(Node));        

    pre = L;  

    for (tempi = 1; tempi < i; tempi++)

        pre = pre->next;                 /*查找第i个位置的前驱结点*/

    p->data = x;
    p->next = pre->next;pre->next = p;                              /*插入的结点为p*/

    return L;                             

}   

 

 

/*单链表的删除，在链表中删除第x个元素*/

 

LinkedList LinkedListDelete(LinkedList L,ElemType x)  

{  

  

       Node *p,*q; /* q为前驱结点，p为查找的结点*/

       int j;

        p = L;j = 0;
        
        while (p->next && j < x-1) {p = p->next;++j;}
 

   if(!(p->next) || (j>x-1)) return ERROR;  //删除位置不合理

    q = p->next;p->next = q->next;free(q);

   return L;

}   

 

 

int GetElem_L(LinkedList L, int i, ElemType e) {

 /*L是带头结点的链表的头指针，以 e 返回第 i 个元素 */

    

    Node *p;

    int j;

p = L;j = 0;
while(p->next && j <i){p = p->next;j++;}

    if ( !p || j>i )  return 0;     /* 第 i 个元素不存在   */

 e = p->data;              /* 取得第 i 个元素   */

     return e;

 

}

 

 

 

void LinkedListPrint(LinkedList L)

 {

 

   Node *start;

 

    for(start = L->next; start != NULL; start = start->next)  

        printf("%d ",start->data);  

    printf("\n");

        free(start);

 

}

 

 

int main()  

{    int e1;

    ElemType e=0;

    LinkedList list;  

    list = LinkedListCreatT();

    LinkedListPrint(list);

    LinkedListInsert(list,4,67);  

    LinkedListPrint(list);

    LinkedListDelete(list,2);   

       LinkedListPrint(list);

    e1=GetElem_L(list, 5, e) ;

printf("第5个元素是 %d\n",e1);

free(list);

return 1;

} 