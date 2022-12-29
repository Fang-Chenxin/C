#include <stdio.h>
#include <stdlib.h>
#define List_init_size 1000
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct
{
    ElemType *elem;   
    int length;
    int listsize;
}Sqlist;
 
//初始化顺序表
int Initlist(Sqlist &L) 
{
    L.elem=(ElemType *)malloc(List_init_size*sizeof(ElemType));
    if(!L.elem) return ERROR;
    L.length=0;
	L.listsize=List_init_size;
    return OK;
}


//创建顺序表，以输入-1结束
void Createlist(Sqlist &L)//输入函数
{
    int i=0,j;
	scanf("%d",&j);
    while(j!=-1)
    {
		L.elem[i] = j;
		i++;
        scanf("%d",&j);
    }
	L.length = i;
}

//将元素e插入到第k个元素之前
Status ListInsert(Sqlist &L, int k, int e)
{ 
    if(k<1||k>L.length+1) return ERROR; //判断插入位置的合法性
    int j;
    int pos=k;
 
    for(j=L.length-1;j>=pos-1;j--)
    {//从最后一个位置开始移位，将需要插入的位置空出
        L.elem[j+1]=L.elem[j];
    }
    L.elem[pos-1]=e;
    L.length++;//每插入一个元素，顺序表长度加一
    return OK;
}

//取顺序表的第i个元素
Status GetElem(Sqlist L,int i,ElemType &e)
{
   	//★★★请补全代码
    e = L.elem[i-1];
    return OK;
}

//打印顺序表的元素
void Display(Sqlist L) 
{
	int i;
	for(i=0;i<L.length;i++)
	{
		printf("%d ",L.elem[i]);
	}
}


//找到从表头开始第一个最小值，k保存最小值的位置，e保存最小值，如果表为空表则返回ERROR，不为空表则返回OK
Status FindMin(Sqlist L, int &k, int &e)
{
	//★★★请补全代码
    if (L.length == 0) return ERROR;
    e = L.elem[0];
    int i;
    k=1;
    for (i=1;i<L.length;i++)
    {
        if (e > L.elem[i])
        {
            e = L.elem[i];
            k = i+1;
        }
    }
	return OK;
}

//将第k个元素删除, 通过e获取删除的值
Status ListDelete(Sqlist &L, int k, int &e)
{
	if(k<1||k>L.length) return ERROR; //判断删除位置的合法性
    int i;
	e = L.elem[k-1];
 
	for(i=k-1;i<L.length-1;i++)
    {
        L.elem[i] = L.elem[i+1];
    }
    L.length--;
    return OK;
   
}

//删除所有偶数且在表尾插入所删除的偶数的个数
Status DeleteOuShu_and_InsertNumofOushu(Sqlist &L){
	//★★★请补全代码
	int i,j,e;
    j=0;
    for (i=0;i<L.length;i++)
    {
        if (L.elem[i]%2 == 0)
        {
            ListDelete(L,i+1,e);
            j++;
            i--;
        }
    }
    ListInsert(L,L.length+1,j);
    return OK;
}

 
int main()
{
    int k;
	ElemType e;
    Sqlist A;
	Status st;
	Initlist(A);
    printf("Please enter the elements of the table, with -1 indicating the end of input\n");
	Createlist(A);
    printf("The elements in the table are as follows\n");
	Display(A);
    st = FindMin(A,k,e);
	if(st == OK)
		printf("\nLocation of minimum value = %d minimum value=%d\n",k,e);
	else
		printf("\nnull table\n");
	ListDelete(A,k,e);
	printf("After deleting the minimum value, the elements in the table are as follows\n");
	Display(A);
	
	printf("\ndelete all even numbers and inserting the number of even numbers at the end of the table\n");
	DeleteOuShu_and_InsertNumofOushu(A);
	Display(A);
    return 0;
}
