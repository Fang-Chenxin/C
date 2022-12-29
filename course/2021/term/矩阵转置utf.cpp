#include<stdio.h>
using namespace std;

struct Matrix{
	int r,c;
	int a[100][100]; 
}A;

int main(){
	printf("输入矩阵的行数和列数:");
	scanf("%d%d",&A.r,&A.c);
	printf("\n输入矩阵\n"); 
	for(int i=1;i<=A.r;i++){
		for(int j=1;j<=A.c;j++){
			scanf("%d",&A.a[i][j]);
		}
	}
	printf("\n转置结果：\n");
		for(int j=1;j<=A.c;j++){
		for(int i=1;i<=A.r;i++){
			printf("%d ",A.a[i][j]);
		}
		printf("\n");
	}
	return 0;
} 
