#include <stdio.h>
#include <iostream>

int main ()
{
    FILE * pFile;
    int n,i,j;
    long num1,num2;
    float all,temp;
    char *buffer,num[20];
    buffer = (char *)malloc(sizeof(char));
    pFile = fopen ("myfile.txt","r+");
    fseek(pFile,0,SEEK_SET);
    i = 0;j = 0;all = 0;
    while(1)//获取读入数据数量
    {
        fread(buffer, sizeof(char), 1,pFile);
        if (*buffer!='\n')
        {
            printf("%c", *buffer);
            num[j] = *buffer;
            j++;
        }
        else
        {
            printf("\n", *buffer);
            n = atoi(num);
            break;
        }
    }
    
    for(i=0;i<n;i++)
    {
        j = 0;
        fseek(pFile,28,SEEK_CUR);
        while(1)
        {
            fread(buffer, sizeof(char), 1,pFile);
            if (*buffer!='\n')
            {
                printf("%c", *buffer);
                num[j] = *buffer;
                j++;
            }
            else
            {
                printf("\n", *buffer);
                temp = atof(num);
                all += temp;
                break;
            }
        }
    }
    fseek(pFile,0,SEEK_END);
    fprintf (pFile, "客户逗留平均时间为 %d\n",n);
    fseek(pFile,0,SEEK_SET);
    fprintf (pFile, "%d\n",n+1);
    fclose (pFile);
    printf("平均时间%.4f",all/n);
    return 0;
}