#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct STUDENT_STRU
{
	char name[10];
	unsigned int Math_score;
	unsigned int English_score; 
	unsigned int total_score;
};

//计算每个学生总成绩，放在total_score变量里
void Totalscore(struct STUDENT_STRU a[], int stunum)
{
	for(int i = 0; i <= stunum; i++)
	{
		a[i].total_score=a[i].English_score + a[i].Math_score;
	}
}

//使用简单选择排序法对学生总成绩进行排序
//参数low和high为待排序数组的下标范围
void SelectSort(struct STUDENT_STRU a[], int low, int high)
{
//★★★请补全代码
int i,j,min;
STUDENT_STRU tmp;
for (i=low;i<=high;i++)
{
    min = i;
    for (j=i+1;j<=high;j++)
    {
        if (a[min].total_score > a[j].total_score)
            min = j;
    }
    if (min != i)
    {
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
}



}

int main()
{
	int  i;
	int stuNum;
	struct STUDENT_STRU StudentStru[10];
	
	printf("Please input the number of items to be sorted：\n");
	scanf("%d", &stuNum);
	
	printf("Please input the name and score of the students：\n");
	for(i = 0; i < stuNum; i++)
	{
		scanf("%s %d %d",StudentStru[i].name,
&StudentStru[i].Math_score, &StudentStru[i].English_score);
	}

	Totalscore(StudentStru, stuNum-1);

	printf("\n");

SelectSort(StudentStru, 0, stuNum-1);
	printf("\n");

	printf("The items sorted by total score are as follows：\n");
	//打印排序结果
	for (i = 0; i < stuNum; i++)
	{
		printf("%s %d\n", StudentStru[i].name, StudentStru[i].total_score);
	}
	
	return 0;
}
