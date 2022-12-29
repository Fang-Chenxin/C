
/*
用带头结点的单链表存储一帧数据，计算该帧数据的累加值作为校验码，并将其附加在数据帧尾部 
**************************************************
Please input the length of frame:
5
Please input the element of frame one by one:
9 3 8 4 1
The frame is: 1 4 8 3 9
The length of the frame is: 5
The checksum added is: 25
The length of the frame with added checksum is: 6
The frame with added checksum is: 1 4 8 3 9 25
**************************************************
Please input the length of frame:
0
The frame is:
The length of the frame is: 0
*/

#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0

#define MAXSIZE 20

typedef int Status;
typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList;

//==========================
//打印单链表
//==========================
void ListTraverse(LinkList L)
{
    LinkList p=L->next;

    while(p)
    {
      printf("%d ", p->data);
        p=p->next;
    }
    printf("\n");
}
//=======================================
//初始化单链表
//=======================================
Status InitList(LinkList &L) 
{ 
/***补全函数***/
L = (Node *)malloc(sizeof(Node));
if(!L) return ERROR;
L->next = NULL;
return OK;
}

int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;

    while(p)                        
    {
        i++;
        p=p->next;
    }
    return i;
}

Status GetElem(LinkList L, int i, ElemType &e)
{
/***补全函数***/
    Node *p;
    p = L;
    p = p->next;
    if(i<1 || i>ListLength(L)) return ERROR;
    while (p->next && i>1)
    {
        p = p->next;
        i--;
    }
    e = p->data;
    return OK;
    
}

Status ListInsert(LinkList &L, int i, ElemType e)
{ 
	int j;
	LinkList p,s;
	p = L;   
	j = 1;

	while (p && j < i)
	{
		p = p->next;
		j=j+1;
	}

	if (!p || j > i) 
		return ERROR;

s = (LinkList)malloc(sizeof(Node));
    if(!(s))
        return ERROR;

	s->data = e;  
	s->next = p->next;
	p->next = s;
	return OK;
}
//=========================================================
//求单链表所有元素的累加和，并将该累加和作为一个新的结点插在单链表的尾部
//=========================================================
Status AddSumForChecking(LinkList &L)
{
/***补全函数***/
    LinkList p;
    int sum;
    p = L;
    p = p->next;
    sum = 0;
    while (p)
    {
        sum += p->data;
        p = p->next;
    }
    ListInsert(L,ListLength(L)+1,sum);
    return OK;
    

}

int main()
{        
    LinkList L;
    ElemType e;
    Status i;
    int j,k,l;

    i=InitList(L);
	if(i==ERROR)
    {
        return 0;
	}

	printf("Please input the length of frame:\n");
	scanf("%d", &k);

	if (k > 0)
        printf("Please input the element of frame one by one:\n");
    for(j=1;j<=k;j++)
	{
	    scanf("%d", &l);
        i=ListInsert(L,1,l);
	}
    printf("The frame is: ");
    ListTraverse(L); 

    printf("The length of the frame is: %d \n",ListLength(L));

	if(OK==AddSumForChecking(L))
	{
		GetElem(L, ListLength(L), e);
		printf("The checksum added is: %d\n", e); 
	    printf("The length of the frame added checksum is: %d \n",ListLength(L));
        printf("The frame added checksum is: ");
        ListTraverse(L);
	}

    return 0;
}
