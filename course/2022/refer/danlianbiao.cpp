#include <stdio.h>   
#include <stdlib.h>   
#define ERROR 0


#define OK 1

#define TRUE 1

#define FALSE 0

typedef int ElemType;   


/*����������*/
typedef struct  Node
{   
    ElemType data;            /*�������е������� */
    struct Node *next;         /*�������ָ����*/
}Node,*LinkedList;
  

  
/*������Ľ���2��β�巨����������*/
int LinkedListCreatT(LinkedList &L, int a[ ], int n)   
{   
// ��д���� 
int i;

Node *r;

L=(Node *)malloc(sizeof(Node));
if(!L) return ERROR;
L->next=NULL;    // ��ʼ�����

r=L;

for(i=0;i<n;i++)
{

Node *p;
p=(Node *)malloc(sizeof(Node));  // ÿ������һ��node�ռ� 

p->data=a[i];   // ÿ�δ洢һ�� Ԫ�� 

r->next=p;   // ���������node�ռ䣬�ӵ���ǰ�������һ���ڵ�֮�� 

r=p;   // �ƶ�r����rʼ�ձ���ָ��ǰ��������һ���ڵ� 

}

r->next=NULL;

return OK; 

}   
  

/*������Ĳ��룬������ĵ�i��λ�ò���x��Ԫ��*/
  
int LinkedListInsert(LinkedList &L,int i,ElemType x)   
{   
// ��д���� 
Node *p;
int j;
Node *pre;
pre=L;


p=(Node *)malloc(sizeof(Node));  
p->data=x;



for(j=0;j<i-1;j++)
	pre=pre->next;  // forѭ��������preָ��� i-1���ڵ� 



p->next=pre->next; 
pre->next=p;

return 1;

}    
  

/*�������ɾ������������ɾ����x��Ԫ��*/
  
int LinkedListDelete(LinkedList &L,ElemType x)   
{   
   
// ��д���� 
Node *p;
int j;

p=L;   // pָ��ͷ�ڵ� 
j=0;   // ��Ӧ�أ�j��0��ʼ 

while(p->next&&j<x-1)    // pָ���x-1���ڵ� 
{
p=p->next;
++j;
}

if(!(p->next)||(j>x-1)) return ERROR;

p->next=p->next->next;
 
return 1;

}    
  

int GetElem_L(LinkedList L, int i, ElemType e) {
 /*L�Ǵ�ͷ���������ͷָ�룬�� e ���ص� i ��Ԫ�� */

Node *p;
int j;
p=L;
j=0;

while(p&&j<i)    // pָ���i���ڵ� 
{
p=p->next;
++j;
}

if(!(p)||(j>i)) return ERROR;

e=p->data;

return e;
// ��д���� 
}

 

void LinkedListPrint(LinkedList L)
 {

// ��д���� 
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
    	printf("����Ԫ�ظ���\n");
    	scanf("%d",&length);
    int a[length];
    ElemType e=0;
    LinkedList list;
	 

  
    printf("�������Ԫ��\n");
	for(i=0;i<length;i++)
	{
    	scanf("%d",&a[i]);
	}
	LinkedListCreatT(list,a,length);
    LinkedListPrint(list);
 
     printf("\n�ڵ�2��λ�ò���67������Ϊ\n");
    LinkedListInsert(list,2,67);   
    LinkedListPrint(list);
  
    printf("\nɾ����3��Ԫ�غ�����Ϊ\n");
    LinkedListDelete(list,3);    
	LinkedListPrint(list);
	
	
    e1=GetElem_L(list, 6, e) ;
    printf("��6��Ԫ���� %d\n",e1);
    free(list);
    return 1;

}

