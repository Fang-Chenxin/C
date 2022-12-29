#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    FILE *fp;                  	/* 定义文件指针*/
    if( ( fp = fopen("score.txt", "r") ) == NULL){	/* 打开文件 */
   	    printf("File open error!\n");
   	    exit(0);
    }
    int i,n=0,a[30],min=100,max=0;
    float sum=0,average;
    while(!feof(fp)){
    fscanf(fp,"%d",&a[i++]);
    n++;
    }
    for(i=0;i<n;i++){
        sum+=a[i];
        if (a[i]>max) max=a[i];
        if (a[i]<min) min=a[i];
    }
    if(fclose(fp)){
    {  printf("can not close the file!\n");   exit(0);  }
    }
    if( ( fp = fopen("result.txt", "w") ) == NULL){	/* 打开文件 */
   	    printf("File open error!\n");
   	    exit(0);
    }
    average=sum/n;
    fprintf(fp,"%.2f %d %d",average,max,min);
    if(fclose(fp))
    {  printf("can not close the file!\n");   exit(0);  }
    return 0;
}