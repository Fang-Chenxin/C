 

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

#define STUDENT_NUMBER 5//排序对象个数

 

#define NAME_ASCEND    0//按姓名递增(非递减）顺序排序

#define NUMBER_ASCEND  1//按学号递增(非递减）顺序排序

#define SCORE_ASCEND   2//按成绩递增(非递减）顺序排序

 

struct STUDENT_STRU

{

    char name[10];//姓名

    char num[6];  //学号

    int score;    //成绩

};

 

//完成两个结构体（中全部变量）的互换

void SwapStu(STUDENT_STRU *StucA, STUDENT_STRU *StucB)

{

    STUDENT_STRU *temp;
    temp = (STUDENT_STRU *)malloc(sizeof(STUDENT_STRU));
    *temp = *StucA;
    *StucA = *StucB;
    *StucB = *temp;

}

 

 

/**************************************************************************/

/*冒泡排序法，根据SortType的取值选择排序的关键字                            */

/**************************************************************************/

void BubbleSort(STUDENT_STRU a[], int n, int SortType)

{

    int i, j;

   

    switch (SortType)

    {

        case NAME_ASCEND:

        {

//请补充代码
            for (i=0;i<n;i++)
            {
                for (j=0;j<n-i-1;j++)
                {
                    if (strcmp(a[j].name,a[j+1].name)>0) SwapStu(&a[j],&a[j+1]);
                }
            }
            break;

 

        }

       

        case NUMBER_ASCEND:

        {

//请补充代码
            for (i=0;i<n;i++)
            {
                for (j=0;j<n-i-1;j++)
                {
                    if (strcmp(a[j].num,a[j+1].num)>0) SwapStu(&a[j],&a[j+1]);
                }
            }
            break;
        }       

       

        case SCORE_ASCEND:

        {

         //请补充代码
        for (i=0;i<n;i++)
        {
            for (j=0;j<n-i-1;j++)
            {
                if (a[j].score>a[j+1].score) SwapStu(&a[j],&a[j+1]);
            }
        }
        break;

        }

       

        default:

            break;

    }

 

}

 

 

//主函数中定义学生结构体数组信息，并调用排序算法进行排序，每次排序后打印结果进行比对

//注意每一次排序都是在上一次排序结果（而非原始数据）的基础上进行的

int main(void)

{

    int i;

 

    STUDENT_STRU StudentStru[STUDENT_NUMBER] =

    {

        {"James", "00007", 85},

        {"Amy",   "00010", 90},

        {"Zoe",   "00001", 60},

        {"Tom",   "00005", 85},

              {"Tom",   "00015", 70},

    };//学生信息的结构体数组，注意有学生的姓名/成绩是相同的，仔细体会排序算法的稳定性

 

    //打印排序对象

    printf("初始数据为：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

    //姓名非递减（递增）排序

    BubbleSort(StudentStru, STUDENT_NUMBER, NAME_ASCEND);

    //打印排序结果

    printf("姓名非递减（递增）排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

       //学号递增排序

    BubbleSort(StudentStru, STUDENT_NUMBER, NUMBER_ASCEND);

    //打印排序结果

    printf("学号递增排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

       //成绩非递减（递增）排序

       BubbleSort(StudentStru, STUDENT_NUMBER, SCORE_ASCEND);

    //打印排序结果

    printf("成绩非递减（递增）排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

       return 0;

}

 




