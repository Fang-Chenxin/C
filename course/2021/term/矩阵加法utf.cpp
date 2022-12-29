#include<stdio.h>
using namespace std;

struct Matrix{
	int r,c;
	int a[100][100]; 
}A,B;

void add(Matrix A,Matrix B){
	if(A.c!=B.c||A.r!=B.r){
		printf("维度不同不能做加法");
		return; 
	}
	for(int i=1;i<=A.r;i++){
		for(int j=1;j<=A.c;j++){
			printf("%d ",A.a[i][j]+B.a[i][j]);
		}
		printf("\n");
	}
}

int main(){
	printf("输入矩阵A的行数和列数:");
	scanf("%d%d",&A.r,&A.c);
	printf("\n输入矩阵A\n"); 
	for(int i=1;i<=A.r;i++){
		for(int j=1;j<=A.c;j++){
			scanf("%d",&A.a[i][j]);
		}
	}
	printf("\n矩阵A输入完毕\n");
	
	printf("输入矩阵B的行数和列数:");
	scanf("%d%d",&B.r,&B.c);
	printf("\n输入矩阵B\n"); 
	for(int i=1;i<=B.r;i++){
		for(int j=1;j<=B.c;j++){
			scanf("%d",&B.a[i][j]);
		}
	}
	printf("\n矩阵B输入完毕\n");
	add(A,B);
	return 0;
} 
