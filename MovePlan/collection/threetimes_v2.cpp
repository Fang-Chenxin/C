#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


#define  N  4                //定义方阵的最大阶数为4
#define  T  50             //定义间隔数为50
#define  VMAX  50         //定义最大速度为50m/s
#define  AMAX  500        //定义最大加速度为50m/s^2
#define  VEXA  5         //定义参考速度为5m/s

/**
 * @brief 用结构体打包变量方便调用
 */
struct FTPLAN
{
	double te[20];
	double end_x[20];
	double end_v[20];
	double end_a[20];
	int l;
	double ts;
	double start_x;
	double start_v;
	double start_a;
	double v_max;//最大速度
	double a_max;//最大加速度
	double v_exa;//较低的参考速度
};

//函数的声明部分  
double MatDet(double* p, int n);                    //求矩阵的行列式  
double Creat_M(double* p, int m, int n, int k);    //求矩阵元素A(m, n)的代数余之式  
int Gauss(double A[][N], double B[][N], int n);    //采用部分主元的高斯消去法求方阵A的逆矩阵B  


double  x = 0, v = 0, a = 0;
double  c0, c1, c2, c3;
double z[T][3];



//-----------------------------------------------  
//功能: 求矩阵(n*n)的行列式  
//入口参数: 矩阵的首地址，矩阵的行数  
//返回值: 矩阵的行列式值  
//----------------------------------------------  
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


//----------------------------------------------------------------------------  
//功能: 求k*k矩阵中元素A(m, n)的代数余之式  
//入口参数: k*k矩阵的首地址，矩阵元素A的下标m,n,矩阵行数k  
//返回值: k*k矩阵中元素A(m, n)的代数余之式  
//----------------------------------------------------------------------------  
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


//------------------------------------------------------------------  
//功能: 采用部分主元的高斯消去法求方阵A的逆矩阵B  
//入口参数: 输入方阵，输出方阵，方阵阶数  
//返回值: true or false  
//-------------------------------------------------------------------  
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


void plan(double ts, double start_x, double start_v, double start_a,  double te, double end_x, double end_v, double end_a, double c[4][1])
{
	double i, t;
	int d;
	c0 = c[0][0];
	c1 = c[1][0];
	c2 = c[2][0];
	c3 = c[3][0];
	for (i = ts, d = 0; i <= te; i = i + (te - ts) / T)
	{
		t = i;

		x = c0 + c1 * t + c2 * pow(t, 2) + c3 * pow(t, 3);
		v = c1 + 2 * c2 * t + 3 * c3 * pow(t, 2);
		a = 2 * c2 + 6 * c3 * t;

		z[d][0] = x, z[d][1] = v, z[d][2] = a;
		d++;
	}
}

void Ci(double a[4][4], double b[4][1], double c[4][1]) //4*1横行列式乘以4*4方阵,确定Ci[]
{
	int i, j;
	double sum = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
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
void calcu(double ts, double te, double a[N][N])
{
	double Tran[4][4] =
	{ 1,  ts,  pow(ts,2), pow(ts , 3),
	  1,  te,  pow(te,2), pow(te , 3),
	  0,  1,   2 * ts,    3*pow(ts,2),
	  0,  1,   2 * te,    3*pow(te,2)  };
	//printf("逆矩阵：\n");
	int i, j;
	if (Gauss(Tran, a, 4))
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				//printf("%.2f ", a[i][j]);
			}
			//printf("\n");
		}
	}
}

/**
 * @brief 三次路径规划求输出
 *
 * @param ftplan 输入结构体
 */

void thirdtime_plan(struct FTPLAN* ftplan)
{
	//int X[], V[], A[];
	//int fputc( int c, FILE *fp );
	double a[N][N], b[N][N], c[4][1];
	double te, end_x, end_v, end_a;
	int i, m;
	 
	for (m = 0; m < ftplan->l; m++)
	{
		
		te = ftplan->te[m] / 5; 
		end_x = ftplan->end_x[m]; 
		end_v = ftplan->end_v[m];
		end_a = ftplan->end_a[m];

		double para[4][1] = { ftplan->start_x, end_x, ftplan->start_v, end_v };

		if (te <= ftplan->ts) { printf("Your input error.\n"); break; }//程序报错

		te = te - ftplan->ts; 
		ftplan->ts = 0;//将时间归零，与plan公式对应 

		calcu(ftplan->ts, te, b);//计算逆矩阵                                          
		Ci(b, para, c);//计算系数

		printf("\n系数: ");
		for (i = 0; i < 4; i++)
			printf("%.2f  ", c[i][0]);
		printf("\n");
		plan(ftplan->ts, ftplan->start_x, ftplan->start_v, ftplan->start_a, te, end_x, end_v, end_a, c);

		printf("输出x  v  a:\n");
		for (i = 0; i < T; i++)
			printf("%.2f %.2f %.2f  \n", z[i][0], z[i][1], z[i][2]);


		ftplan->ts = te; 
		ftplan->start_x = end_x; 
		ftplan->start_v = end_v;
		ftplan->start_a = end_a;//以前一次的末状态作为后一次的初状态
	}
}

int main()
{
	struct FTPLAN Thirdtplan;

	double te[20] = { 2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	double end_x[20] = { 3,20,30,40,50,60,70,80,90,100,90,80,70,60,50,40,30,20,10,0 };
	double end_v[20] = { 0,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1,0 };
	//double end_a[20] = { 1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1,0 };
	double end_a[20] = {};
	Thirdtplan.l = 1;//1<=l<=20
	// Thirdtplan.ts = 0;
	Thirdtplan.start_x = 0;
	Thirdtplan.start_v = 0;
	Thirdtplan.start_a = 0;
	Thirdtplan.v_max = VMAX;
	Thirdtplan.a_max = AMAX;
	Thirdtplan.v_exa = VEXA;
	int p;
	for (p = 0; p < Thirdtplan.l; p++)
	{
		Thirdtplan.te[p] = te[p];
		Thirdtplan.end_x[p] = end_x[p];
		Thirdtplan.end_v[p] = end_v[p];
		Thirdtplan.end_a[p] = end_a[p];
	}

	thirdtime_plan(&Thirdtplan);//三次路径规划

	// system("pause");//稳定输出框
	return 0;
}