//编写一个将数组元素逆序打印的递归函数。

/* Example:
从键盘读入：5，7，1，4，6
输出为：6，4，1，7，5
 */
#include <stdio.h>
#include <stdlib.h>

void InversePrint(int a[], int n)
{
if(n>0) 
{
    if(n>1)
		printf("%d,",a[n-1]);
	else
		printf("%d",a[n-1]);
    InversePrint(a,n-1);
}


}

int main()
{
	int i;
    int a[5];

	for(i=0;i<5;i++){
		scanf("%d", &a[i]);
	
	}

	InversePrint(a,5);
      
}
