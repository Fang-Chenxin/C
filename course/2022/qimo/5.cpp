#include <stdio.h>
#include <string.h>
#include<malloc.h>
#define OK 1
#define ERROR 0

typedef struct node         //二叉树结点类型的定义
{	
     char data;
	 struct node *lchild;	//结点的左孩子指针
	 struct node *rchild;	//结点的右孩子指针
} BinTNode, *Bitree;				

typedef int Status;

typedef struct Lnode {     //链队列结点结构定义
	BinTNode* data;     //数据域，存放二叉树结点指针 
	struct Lnode *next;   //指针域，
}LNode, *LinkList;

typedef struct{
	LinkList front;   //队头指针
	LinkList rear;    //队尾指针
	int length;      //队列长度
}LinkQueue;

//队列初始化，构造一个仅包含头结点的空队列.
//如果成功，返回OK，如果失败，返回ERROR
Status InitQueue(LinkQueue &Q)
{
	Q.front=(LinkList)malloc(sizeof(LNode));
	if(!Q.front)
		return ERROR;
	Q.front->next=NULL;
	Q.rear=Q.front;
	Q.length=0;
	return OK;
}

//队列判空，如果为空，返回true, 否则返回false
bool QueueEmpty(LinkQueue Q)
{
	return (Q.front==Q.rear);
}

//入队操作，
//将元素e插入队尾, 如果成功，返回OK，如果失败，返回ERROR
Status EnQueue(LinkQueue &Q, BinTNode* e)
{
    LinkList p;
	p=(LinkList)malloc(sizeof(LNode));
	if(!p)
		return ERROR;
	p->data=e;
	p->next=Q.rear->next;
	Q.rear->next=p;
	Q.rear=p;
	Q.length++;
	return OK;	
}

//出队列操作，
//删除队头元素并通过参数e返回队首元素值，如果成功，返回OK，如果失败，返回ERROR  
Status DeQueue(LinkQueue &Q, BinTNode* &e)
{
	if(Q.front==Q.rear)
		return ERROR;
	LinkList p;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(p==Q.rear)
		Q.rear=Q.front;
	free(p);
	Q.length--;
	return OK; 
}
 
BinTNode *CreateBinTree()  //输入二叉树的先序遍历的扩展序列，创建二叉链表
{   
	 BinTNode *t;
	 char ch;
	 ch=getchar();
	 if (ch=='0')             //如果读入0，创建空树
		t=NULL;
	 else
	 {	
		t=(BinTNode *)malloc(sizeof(BinTNode));	//申请根结点*t空间
		t->data=ch;                           //将结点数据ch放入根结点的数据域
		t->lchild=CreateBinTree();			    //建左子树
		t->rchild=CreateBinTree();			    //建右子树
	 } 
    return t;
}

//对二叉树进行后序遍历并打印。
void postorder(Bitree T) 
{
    //★★★请补全代码
    if(!T) return;
    postorder(T->lchild);
    postorder(T->rchild);
    printf("%c ",T->data);
    return;
} 

//计算二叉树的高度
int Height_of_tree(Bitree T)
{
    //★★★请补全代码
    if (!T) return 0;
    int h1,h2;
    h1 = Height_of_tree(T->lchild);
    h2 = Height_of_tree(T->rchild);
    if (h1 > h2)
        return h1+1;
    else
        return h2+1;
} 

//对二叉树进行层序遍历并输出每层度为1的结点(要求使用队列）。
void Calculate(Bitree T) 
{
   BinTNode *p;
   int count;
   if (T == NULL) 
	   return;
   LinkQueue Q;
   InitQueue(Q);
   EnQueue(Q, T);
   //当队头和队尾相等时，表示队列为空
   while(!QueueEmpty(Q)) 
   {	
       //★★★请补全代码
        DeQueue(Q,p);
        count = 0;
        if (p->lchild)
        {
            EnQueue(Q,p->lchild);
            count++;
        }
        if (p->rchild)
        {
            EnQueue(Q,p->rchild);
            count++;
        }
        if(count == 1)
            printf("%c ",p->data);
    }

} 
int main()
{    
	 BinTNode *t=NULL;
	 printf("输入先序序列的扩展序列,虚结点用0表示：\n");
	 t=CreateBinTree();
	 printf("\n二叉树的后序遍历结果为:\n");
	 postorder(t); 
     printf("\n二叉树的高度为:\n");
	 printf("%d\n",Height_of_tree(t));
	 printf("输出每层二叉树度为1的节点:\n");
	 Calculate(t);	 	                    
     printf("\n");
}
   
