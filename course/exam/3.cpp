/*
将两个顺序表 Sqlist1 和 SqList2 交叉合并，得到顺序表 SqList3
*********************************
Please input the length of SqList1:
5
Please input the element of SqList1 one by one:
9 1 5 8 3
The SqList1 is: 3 8 5 1 9
The length of SqList1 is: 5
Please input the length of SqList2:
2
Please input the element of SqList2 one by one:
55
66
The SqList2 is: 66 55
The length of SqList2 is: 2
The SqList3 of interleaving L1&2 is: 3 66 8 55 5 1 9
The length of SqList3 is: 7
*********************************
Please input the length of SqList1:
3
Please input the element of SqList1 one by one:
11
33
66
The SqList1 is: 66 33 11
The length of SqList1 is: 3
Please input the length of SqList2:
6
Please input the element of SqList2 one by one:
9 1 5 8 3 7 4
The SqList2 is: 7 3 8 5 1 9
The length of SqList2 is: 6
The SqList3 of interleaving L1&2 is: 66 7 33 3 11 8 5 1 9
The length of SqList3 is: 9
*/

#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}SqList;

void ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
        printf("%d ",L.data[i]);
    printf("\n");
}

int ListLength(SqList L)
{
	return L.length;
}

Status GetElem(SqList L,int i,ElemType &e)
{
/***补全函数***/
if(i<1 || i>ListLength(L)) return ERROR;
e = L.data[i-1];
return OK;
}

Status ListInsert(SqList &L,int i,ElemType e)
{ 
	int k;
	if (L.length>=MAXSIZE || i<0 || i>L.length)
		return ERROR;

	for(k=L.length-1;k>=i;k--)
			L.data[k+1]=L.data[k];

	L.data[i]=e;
	L.length++;

	return OK;
}

void InterLeaving(SqList &L3, SqList L1, SqList L2)
{
/***补全函数***/
    int i,j,k;
    i=j=k=0;
    while (i<L1.length && j<L2.length)
    {
        ListInsert(L3,k,L1.data[i]);
        i++;k++;
        ListInsert(L3,k,L2.data[j]);
        j++;k++;
    }
    while (i<L1.length)
    {
        ListInsert(L3,k,L1.data[i]);
        i++;k++;
    }
    while (j<L2.length)
    {
        ListInsert(L3,k,L2.data[i]);
        j++;k++;
    }
    L3.length = k;
}
int main()
{
    SqList L1, L2, L3;
    Status i;
    int j,k,l;

	printf("Please input the length of SqList1:\n");
	scanf("%d", &k);

    L1.length = 0;
	if (k > 0)
        printf("Please input the element of SqList1 one by one:\n");
    for(j=1;j<=k;j++)
	{
	    scanf("%d", &l);
        i=ListInsert(L1,0,l);
	}
    printf("The SqList1 is: ");
    ListTraverse(L1); 
    printf("The length of SqList1 is: %d \n",ListLength(L1));
	printf("Please input the length of SqList2:\n");
	scanf("%d", &k);

    L2.length = 0;
	if (k > 0)
        printf("Please input the element of SqList2 one by one:\n");
    for(j=1;j<=k;j++)
	{
	    scanf("%d", &l);
        i=ListInsert(L2,0,l);
	}
    printf("The SqList2 is: ");
    ListTraverse(L2); 
    printf("The length of SqList1 is: %d \n",ListLength(L2));

    L3.length = 0;
	InterLeaving(L3, L1, L2);
    printf("The SqList3 of interleaving L1&2 is: ");
    ListTraverse(L3); 
    printf("The length of SqList1 is: %d \n",ListLength(L3));
    return 0;
}


