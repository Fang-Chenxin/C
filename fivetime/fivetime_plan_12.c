#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>



#define  N  6                //定义方阵的最大阶数为6
#define  T  1000             //定义间隔数为1000

/**
 * @brief 用结构体打包变量方便调用
 * 
 */
struct FTPLAN
{
	int l;
    double ts;
	double start_x;
	double start_v;
	double start_a;
    double te;
    double end_x;
    double end_v;
	double end_a;
};



//函数的声明部分  
double MatDet(double* p, int n);                   //求矩阵的行列式  
double Creat_M(double* p, int m, int n, int k);    //求矩阵元素A(m, n)的代数余之式  
void print(double* p, int n);                      //输出矩阵n*n  
int Gauss(double A[][N], double B[][N], int n);    //采用部分主元的高斯消去法求方阵A的逆矩阵B  

// 0 - 1
//double t0 = 0, x0 = 30, v0 = 30, a0 = 10;
//double t1 = 5, x1 = 60, v1 = 40, a1 = 13;
//[x01, v01, a01] = plan(t0, x0, v0, a0, t1, x1, v1, a1);
// 1 - 2
//double t2 = 13, x2 = 80, v2 = 10, a2 = 13;
//[x12, v12, a12] = plan(0, x1, v1, a1, t2 - t1, x2, v2, a2);
// 2 - 3
//double t3 = 20, x3 = 10, v3 = 0, a3= 23;
//[x23, v23, a23] = plan(0, x2, v2, a1, t3 - t2, x3, v3, a3);

//double  ts, start_x, start_v, start_a, te, end_x, end_v, end_a;
//int l;

struct Node
{
	double x;
	double v;
	double a;
	struct Node *next;
};
typedef struct Node List;


/**
 * @brief 求矩阵(n*n)的行列式
 * 
 * @param p 矩阵的首地址
 * @param n 矩阵的行数
 * @return double 矩阵的行列式值
 */
double MatDet(double* p, int n)
{
	int r, c, m;
	int lop = 0;
	double result = 0;
	double mid = 1;

	if (n != 1)
	{
		lop = (n == 2) ? 1 : n;            //控制求和循环次数,若为2阶，则循环1次，否则为n次  
		for (m = 0; m < lop; m++)
		{
			mid = 1;            //顺序求和, 主对角线元素相乘之和  
			for (r = 0, c = m; r < n; r++, c++)
			{
				mid = mid * (*(p + r * n + c % n));
			}
			result += mid;
		}
		for (m = 0; m < lop; m++)
		{
			mid = 1;            //逆序相减, 减去次对角线元素乘积  
			for (r = 0, c = n - 1 - m + n; r < n; r++, c--)
			{
				mid = mid * (*(p + r * n + c % n));
			}
			result -= mid;
		}
	}
	else
		result = *p;
	return result;
}

/**
 * @brief 求k*k矩阵中元素A(m, n)的代数余子式
 * 
 * @param p k*k矩阵中的首地址
 * @param m 矩阵元素A的下标m
 * @param n 矩阵元素A的下标n
 * @param k 矩阵行数
 * @return double k*k矩阵中元素A(m, n)的代数余子式
 */
double Creat_M(double* p, int m, int n, int k)
{
	int len;
	int i, j;
	double mid_result = 0;
	int sign = 1;
	double* p_creat, * p_mid;

	len = (k - 1) * (k - 1);            //k阶矩阵的代数余之式为k-1阶矩阵  
	p_creat = (double*)calloc(len, sizeof(double)); //分配内存单元  
	p_mid = p_creat;
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < k; j++)
		{
			if (i != m && j != n) //将除第i行和第j列外的所有元素存储到以p_mid为首地址的内存单元  
			{
				*p_mid++ = *(p + i * k + j);
			}
		}
	}
	sign = (m + n) % 2 == 0 ? 1 : -1;    //代数余之式前面的正、负号  
	mid_result = (double)sign * MatDet(p_creat, k - 1);
	free(p_creat);
	return mid_result;
}



/**
 * @brief 采用部分主元的高斯消去法求方阵A的逆矩阵B
 * 
 * @param A 输入方阵
 * @param B 输出方阵
 * @param n 方阵阶数
 * @return int 0:成功 1：失败
 */
int Gauss(double A[][N], double B[][N], int n)
{
	int i, j, k;
	double max, temp;
	double t[N][N];                //临时矩阵  
	//将A矩阵存放在临时矩阵t[n][n]中  
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			t[i][j] = A[i][j];
		}
	}
	//初始化B矩阵为单位阵  
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			B[i][j] = (i == j) ? (double)1 : 0;
		}
	}
	for (i = 0; i < n; i++)
	{
		//寻找主元  
		max = t[i][i];
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (fabs(t[j][i]) > fabs(max))
			{
				max = t[j][i];
				k = j;
			}
		}
		//如果主元所在行不是第i行，进行行交换  
		if (k != i)
		{
			for (j = 0; j < n; j++)
			{
				temp = t[i][j];
				t[i][j] = t[k][j];
				t[k][j] = temp;
				//B伴随交换  
				temp = B[i][j];
				B[i][j] = B[k][j];
				B[k][j] = temp;
			}
		}
		//判断主元是否为0, 若是,则矩阵A不是满秩矩阵,不存在逆矩阵  
		if (t[i][i] == 0)
		{
			return 0;
		}
		//消去A的第i列除去i行以外的各行元素  
		temp = t[i][i];
		for (j = 0; j < n; j++)
		{
			t[i][j] = t[i][j] / temp;        //主对角线上的元素变为1  
			B[i][j] = B[i][j] / temp;        //伴随计算  
		}
		for (j = 0; j < n; j++)        //第0行->第n行  
		{
			if (j != i)                //不是第i行  
			{
				temp = t[j][i];
				for (k = 0; k < n; k++)        //第j行元素 - i行元素*j列i行元素  
				{
					t[j][k] = t[j][k] - t[i][k] * temp;
					B[j][k] = B[j][k] - B[i][k] * temp;
				}
			}
		}
	}
	return 1;
}




double x=0, v=0, a=0;
double  c0, c1, c2, c3, c4, c5;
double z[T][3];

/**
 * @brief 创建一个空白链表p
 * 
 * @param n 循环次数
 * @param zq 空白链表p的首地址
 * @return List* 空白链表p
 */
List* CreatList(int n, double *zq )
{
	List* pre, * cur, * p;
	p = NULL;
	for (int j = 0; j < n; j++)
	{
		cur = (List*)malloc(sizeof(List));
		cur->next = NULL;
		if (p == NULL)
			p = cur;
		else
			pre->next = cur;
		cur->x = *zq, cur->v = *zq+1, cur->a = *zq+2;
		pre = cur;
	}
	return p;
}
/**
 * @brief 求出x, v, a的输出数组
 * 
 * @param ts 开始时间
 * @param start_x 起始位置
 * @param start_v 起始速度
 * @param start_a 起始加速度
 * @param te 结束时间
 * @param end_x 终点位置
 * @param end_v 终点速度
 * @param end_a 终点加速度
 * @param c 系数数组
 * @return double* x, v, a的输出数组
 */
double* plan(double ts, double start_x, double start_v, double start_a, double te, double end_x, double end_v, double end_a ,double c[6][1])
{
	double* p;
	double i, t;
	int d;
	c0 = c[0][0];
	c1 = c[1][0];
	c2 = c[2][0];
	c3 = c[3][0];
	c4 = c[4][0];
	c5 = c[5][0];
	for ( i = ts,d = 0;i<= te; i = i + (te-ts)/T)
	{
		t = i;
		x =  (c0 + c1 * t + c2 * pow(t , 2) + c3 * pow(t , 3)+ c4 * pow(t , 4)+ c5 * pow(t , 5));
		v =  (c1 + 2 * c2 * t + 3 * c3 * pow(t , 2)+ 4 * c4 * pow(t , 3)+ 5 * c5 * pow(t , 4));
		a =  (2 * c2 + 6 * c3 * t+ 12 * c4 * pow(t , 2)+ 20 * c5 * pow(t , 3));
		z[d][0] = x, z[d][1] = v, z[d][2] = a;
		d++;
	}

	//printf("%.2f %.2f %.2f\n", x, v, a);

	p = *z;
	return p ;
}

/**
 * @brief 求出系数矩阵c
 * 
 * @param a 输入矩阵
 * @param b 输入矩阵
 * @param c 输出矩阵
 */
void Ci(double a[6][6], double b[6][1], double c[6][1])//6*1横行列式乘以6*6方阵
{
	int i, j;
	double sum = 0;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
			sum += a[i][j] * b[j][0];
		c[i][0] = sum;
		sum = 0;
	}
}

/**
 * @brief 运用高斯消去法求矩阵的逆矩阵
 * 
 * @param x 开始时间
 * @param y 结束时间
 * @param a 输出矩阵
 */
void calcu(double x, double y, double a[N][N])
{
		double Tran[6][6] =
		{ 1, x,  pow(x ,2), pow(x , 3), pow(x , 4), pow(x , 5),
		 1, y,  pow(y , 2), pow(y , 3), pow(y , 4), pow(y , 5),
		 0, 1,   2 * x,  3 * pow(x , 2), 4 * pow(x , 3), 5 * pow(x , 4), 
		 0, 1,   2 * y, 3 * pow(y , 2), 4 * pow(y , 3), 5 * pow(y , 4),
		 0, 0, 2, 6 * x, 12 * pow(x , 2), 20 * pow(x , 3),
		 0, 0, 2, 6 * y, 12 * pow(y , 2), 20 * pow(y , 3)} ;
		printf("逆矩阵：\n");
		int i,j;
		if (Gauss(Tran, a, 6))
		{
		for (i = 0; i < 6; i++)
			{
				//cout << setw(6);
				for (j = 0; j < 6; j++)
				{
					printf("%.2f ", a[i][j]);
				}
				printf("\n");
			}
		}
}

/**
 * @brief 五次路径规划求输出
 * 
 * @param ftplan 输入结构体
 */

void fivetime_plan(struct FTPLAN *ftplan)
{
	//int X[], V[], A[];
	//int fputc( int c, FILE *fp );
	
	List* p;
	double a[N][N], b[N][N],c[6][1];
	int i, m;

	//printf("请输入阶段数：\n");
	//scanf("%d",&l);
	//printf("请输入 ts, start_x, start_v, start_a：\n");
	//scanf("%lf%lf%lf%lf", &ts, &start_x, &start_v, &start_a); 
    for(m=0; m<ftplan->l; m++)
	{	
		//printf("请输入 te%d, end_x%d, end_v%d, end_a%d：\n",m+1,m+1,m+1,m+1);
		//scanf("%lf%lf%lf%lf", &te, &end_x, &end_v, &end_a);
	    double para[6][1] = { ftplan->start_x, ftplan->end_x, ftplan->start_v, ftplan->end_v, ftplan->start_a, ftplan->end_a};

		if (ftplan->te<=ftplan->ts){printf("Your input error.\n");break;}//程序报错
		ftplan->te = ftplan->te-ftplan->ts;ftplan->ts = 0;//将时间归零，与plan公式对应    
		calcu(ftplan->ts,ftplan->te,b);//计算逆矩阵                                          
		Ci(b, para, c);//计算系数

	    printf("系数:\n");
	    for (i = 0; i < 6; i++)
		   printf("%.2f \n", c[i][0]);
        plan(ftplan->ts, ftplan->start_x, ftplan->start_v, ftplan->start_a, ftplan->te, ftplan->end_x, ftplan->end_v, ftplan->end_a, c);

    	printf("输出x  v  a:\n");
    	for(i = 0; i < T; i++ )
    		printf("%.2f %.2f %.2f  \n", z[i][0], z[i][1], z[i][2]);
    	ftplan->ts = ftplan->te;ftplan->start_x = ftplan->end_x;ftplan->start_v = ftplan->end_v;ftplan->start_a = ftplan->end_a;//以前一次的末状态作为后一次的初状态
	}
}

int main()
{
	struct FTPLAN ftplan;
	
	ftplan.l = 1;
    ftplan.ts = 20;
	ftplan.start_x = 50;
	ftplan.start_v = 0;
	ftplan.start_a = 0;
    ftplan.te = 21;
    ftplan.end_x = 500;
    ftplan.end_v = 20;
	ftplan.end_a = 5;
	fivetime_plan(&ftplan);//五次路径规划
	return 0;
}
