#include "stdio.h"

#include "malloc.h"

#include "string.h"

 

struct STUDENT

{

       char STU_ID[8];

       char STU_NAME[10];

       int STU_AGE;

       int STU_SCORE;

};

 

int main(int argc, char* argv[])

{

       //建立一个学生的结构体: 年龄，学号，名字和分数

       int i,j;

       struct STUDENT stu[3];

       stu[0].STU_AGE=12;

       strcpy(stu[0].STU_ID,"04120084");

       strcpy(stu[0].STU_NAME,"张三");    

      

       stu[1].STU_AGE=12;

       strcpy(stu[1].STU_ID,"04120085");

       strcpy(stu[1].STU_NAME,"李四");    

 

       stu[2].STU_AGE=13;

       strcpy(stu[2].STU_ID,"04120086");

       strcpy(stu[2].STU_NAME,"赵五");    

 

       //选择排序法

 

       //输入学生的成绩信息

       printf("按顺序输入学生的成绩信息\n");   scanf("%d,%d,%d",&stu[0].STU_SCORE,&stu[1].STU_SCORE,&stu[2].STU_SCORE);

      

       //添加选择排序法程序至结束    

       int k;

       for(i=0;i<3;i++)

       {

              k=i; //k用来记录每一趟比较下来后，最大数的下标值*/

              for(j=i+1;j<3;j++)

              {                  

                     if(stu[j].STU_SCORE > stu[k].STU_SCORE)

                      k=j;

              }

              if(i!=k) /*如果k的值发生改变，则把i和k所指向的元素进行交换*/

              {

                     struct STUDENT st;//定义一个中间的结构体变量，进行交换

                     
                     strcpy(st.STU_NAME , stu[i].STU_NAME);
                     strcpy(stu[i].STU_NAME , stu[k].STU_NAME);
                     strcpy(stu[k].STU_NAME , st.STU_NAME);

                     
                     st.STU_SCORE = stu[i].STU_SCORE;
                     stu[i].STU_SCORE = stu[k].STU_SCORE;
                     stu[k].STU_SCORE = st.STU_SCORE;

              }
       }

 

       printf("%s,%d\n",stu[0].STU_NAME,stu[0].STU_SCORE);

       printf("%s,%d\n",stu[1].STU_NAME,stu[1].STU_SCORE);

       printf("%s,%d\n",stu[2].STU_NAME,stu[2].STU_SCORE);

}