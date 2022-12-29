#include "stdio.h"
#include "stdlib.h"
#define ElemType int

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}Sqlist;

int main()
{
    Sqlist L;
    L.listsize=20;
    L.elem=(ElemType *)malloc(L.listsize*sizeof(ElemType));
    scanf("%d",&L.length);
    int i;
    for (i=0;i<L.length;i++)
    {
        scanf("%d",&L.elem[i]);
    }
    int m;
    int Max;
    Max = L.elem[0];
    for (i=0;i<L.length;i++)
    {
        if(L.elem[i] <= Max)
        {
            Max = L.elem[i];
            m = i;
        }
    }
    L.elem[m] = L.elem[0];
    L.elem[0] = Max;
    for (i=0;i<L.length;i++)
    {
        printf("%d ",L.elem[i]);
    }
    return 1;
}