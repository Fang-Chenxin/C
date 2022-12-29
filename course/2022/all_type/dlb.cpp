#include <stdio.h>   
#include <stdlib.h>   
#define ERROR 0


#define OK 1

#define TRUE 1

#define FALSE 0

typedef int ElemType;   


/*定义结点类型*/
typedef struct  Node
{   
    ElemType data;            /*单链表中的数据域 */
    struct Node *next;         /*单链表的指针域*/
}Node,*LinkedList;
  

  
  
/*单链表的建立2，尾插法建立单链表*/
  int LinkedListCreatT(LinkedList &L, int a[ ], int n)   
{   
// 填写完整
    L = (LinkedList)malloc(sizeof(Node));
    if(!L) return ERROR;
    L->next=NULL;
    LinkedList p,q;
    p = L;
    for (int i=0;i<n;i++)
    {
        q = (Node *)malloc(sizeof(Node));
        if(!q) return ERROR;
        q->data = a[i];
        p->next = q;
        p = q;
    }
    p->next = NULL;
    return OK;

}   
  

/*单链表的插入，在链表的第i个位置插入x的元素*/
  
int LinkedListInsert(LinkedList &L,int i,ElemType x)   
{   
// 填写完整
    if(i<1) return ERROR;
    LinkedList p,q;
    p = L;
    for (int j=0;j<i-1;j++)
    {
        if(p->next == NULL) return ERROR;
        p = p->next;
    }
    q = (Node *)malloc(sizeof(Node));
    if(!q) return ERROR;
    q->data = x;
    q->next = p->next;
    p->next = q;
    return OK;
}    
  

/*单链表的删除，在链表中删除第x个元素*/
  
int LinkedListDelete(LinkedList &L,ElemType x)   
{   
   
// 填写完整
    if(x<1) return ERROR;
    LinkedList p,q;
    p = L;
    for (int j=0;j<x-1;j++)
    {
        if(p->next == NULL) return ERROR;
        p = p->next;
    } 
    q = p->next;
    p->next = q->next;
    free(q);
    return OK;
}    
  

int GetElem_L(LinkedList L, int i, ElemType e) {
 /*L是带头结点的链表的头指针，以 e 返回第 i 个元素 */
     
// 填写完整 
    if(i<1) return ERROR;
    LinkedList p;
    p = L;
    for (int j=0;j<i;j++)
    {
        if(p->next == NULL) return ERROR;
        p = p->next;
    }
    e = p->data;
    return e;
}

 

void LinkedListPrint(LinkedList L)
 {

// 填写完整 
    while (L->next)
    {
        L = L->next;
        printf("%d,",L->data);
    }
    
}


int main()   
{   int i,e1;
    int length;
    
    ElemType e=0;
    LinkedList list; 

    printf("输入元素个数\n");
    scanf("%d",&length);
    int a[length];
    printf("逐个输入元素\n");
	for(i=0;i<length;i++)
	{
    	scanf("%d",&a[i]);
	}
	LinkedListCreatT(list,a,length);
    LinkedListPrint(list);
 
     printf("\n在第2个位置插入67后顺序表为\n");
    LinkedListInsert(list,2,67);   
    LinkedListPrint(list);
  
    printf("\n删除第3个元素后顺序表为\n");
    LinkedListDelete(list,3);    
	LinkedListPrint(list);
	
	
    e1=GetElem_L(list, 2, e) ;
    printf("第2个元素是 %d\n",e1);
    free(list);
    return 1;

}
