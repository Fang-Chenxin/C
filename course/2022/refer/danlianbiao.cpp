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
int i;

Node *r;

L=(Node *)malloc(sizeof(Node));
if(!L) return ERROR;
L->next=NULL;    // 初始化完成

r=L;

for(i=0;i<n;i++)
{

Node *p;
p=(Node *)malloc(sizeof(Node));  // 每次申请一个node空间 

p->data=a[i];   // 每次存储一个 元素 

r->next=p;   // 把新申请的node空间，接到当前链表最后一个节点之后 

r=p;   // 移动r，让r始终保持指向当前链表的最后一个节点 

}

r->next=NULL;

return OK; 

}   
  

/*单链表的插入，在链表的第i个位置插入x的元素*/
  
int LinkedListInsert(LinkedList &L,int i,ElemType x)   
{   
// 填写完整 
Node *p;
int j;
Node *pre;
pre=L;


p=(Node *)malloc(sizeof(Node));  
p->data=x;



for(j=0;j<i-1;j++)
	pre=pre->next;  // for循环结束，pre指向第 i-1个节点 



p->next=pre->next; 
pre->next=p;

return 1;

}    
  

/*单链表的删除，在链表中删除第x个元素*/
  
int LinkedListDelete(LinkedList &L,ElemType x)   
{   
   
// 填写完整 
Node *p;
int j;

p=L;   // p指向头节点 
j=0;   // 相应地，j从0开始 

while(p->next&&j<x-1)    // p指向第x-1个节点 
{
p=p->next;
++j;
}

if(!(p->next)||(j>x-1)) return ERROR;

p->next=p->next->next;
 
return 1;

}    
  

int GetElem_L(LinkedList L, int i, ElemType e) {
 /*L是带头结点的链表的头指针，以 e 返回第 i 个元素 */

Node *p;
int j;
p=L;
j=0;

while(p&&j<i)    // p指向第i个节点 
{
p=p->next;
++j;
}

if(!(p)||(j>i)) return ERROR;

e=p->data;

return e;
// 填写完整 
}

 

void LinkedListPrint(LinkedList L)
 {

// 填写完整 
Node *p;

for(p=L->next;p!=NULL;p=p->next)
{
    printf("%d ",p->data);
}
 printf("\n");
 
}


int main()   
{   int i,e1;
    int length;
    	printf("输入元素个数\n");
    	scanf("%d",&length);
    int a[length];
    ElemType e=0;
    LinkedList list;
	 

  
    printf("逐个输入元素\n");
	for(i=0;i<length;i++)
	{
    	scanf("%d",&a[i]);
	}
	LinkedListCreatT(list,a,length);
    LinkedListPrint(list);
 
     printf("\n在第2个位置插入67后单链表为\n");
    LinkedListInsert(list,2,67);   
    LinkedListPrint(list);
  
    printf("\n删除第3个元素后单链表为\n");
    LinkedListDelete(list,3);    
	LinkedListPrint(list);
	
	
    e1=GetElem_L(list, 6, e) ;
    printf("第6个元素是 %d\n",e1);
    free(list);
    return 1;

}

