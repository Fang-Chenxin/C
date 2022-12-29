#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;

typedef struct{
	ElemType *elem;			//存储空间的基地址
	int length;				//当前长度
}SqList;

//初始化顺序表
Status InitList(SqList &L)
{
	L.elem=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));
	if(!L.elem)
		return ERROR;
	L.length=0;
	return OK;
}

//创建顺序表，从键盘输入若干非负整数值，以-1结尾，表示数据元素输入完毕
//如果成功，返回OK； 如果数据中出现了除-1以外的负整数值，打印错误，并返回ERROR
Status CreateList(SqList &L)
{
//★★★请补全代码
    int input;
    scanf("%d",&input);
    while(input != -1)
    {
        if (input < -1)
        {
            printf("Input error.");
            return ERROR;
        }
        L.elem[L.length]=input;
        L.length++;
        scanf("%d",&input);
    }
    return OK;


}

//在顺序表L中第i个位置之前插入新的元素e，i值的合法范围是1~L.length+1
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    if(!L.elem)
		return ERROR;
	if(i<1||i>L.length+1)
		return ERROR;	 //判断插入位置的合法性
	if(L.length==MAXSIZE)
		return ERROR;	 //当前存储空间已满
	int j;
	for(j=L.length-1; j>=i-1; j--)
	{
		L.elem[j+1]=L.elem[j];
	}
	L.elem[i-1]=e;
	L.length++;
	return OK;
}

//打印顺序表的元素
Status Display(SqList L) 
{
    if(!L.elem)
		return ERROR;
	if(L.length==0)
	{
		printf("The list is NULL.\n"); 
	}
	else
	{
		int i;
		for(i=0;i<L.length;i++)
		{
			printf("%d ",L.elem[i]);
		}
		printf("\n"); 
	}
    return OK;
}

//将一个顺序表中的数据元素根据其奇偶性分别插入到顺序表Odd和Even中。
//如果成功，返回OK，如果失败, 返回ERROR
Status ListGroup_Sq(SqList L, SqList &Odd, SqList &Even)
{
//★★★请补全代码
    int i;
    for (i=0;i<L.length;i++)
    {
        if (L.elem[i] % 2 == 1)
        {
            Odd.elem[Odd.length] = L.elem[i];
            Odd.length++;
        }
        else
        {
            Even.elem[Even.length] = L.elem[i];
            Even.length++;
        }
    }
    return OK;



}
int main()
{
	SqList L,Odd,Even;
	InitList(L);
	InitList(Odd);
	InitList(Even);
	printf("Please input the elements of the list, with -1 indicating the end of input:\n");
	if(CreateList(L)==ERROR)
		return -1;
	printf("The elements in the list are as follows:\n");
	Display(L);
	ListGroup_Sq(L, Odd, Even);
	printf("The elements in the odd list are as follows:\n");
	Display(Odd);
	printf("The elements in the even list are as follows:\n");
	Display(Even);
	return 0;
}
