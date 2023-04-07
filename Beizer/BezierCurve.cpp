#include <stdio.h>
#include <math.h>

typedef struct {
	double x, y;
} vector2d;

void GetPoint(vector2d *Ps, double x, double y) {
	Ps->x = x;
	Ps->y = y;
}

//递归求 n!
double factorial(int n) {
	if (n <= 1)return 1;
	return factorial(n - 1) * n;
}

//贝塞尔曲线表达式
vector2d BezierCommon(vector2d Ps[], int cnt, double t) {
	int n = cnt - 1; //连线
	if (n == 0) { //一个点的时候返回自身
		return Ps[0];
	}
	vector2d P_t;
	P_t.x = P_t.y = 0;
	for (int i = 0; i < cnt; ++i) {
		double C_n_i = factorial(n) / (factorial(i) * factorial(n - i)); //组合数，二项式展开定理的系数
		P_t.x += C_n_i * pow((1 - t), (n - i)) * pow(t, i) * Ps[i].x;
		P_t.y += C_n_i * pow((1 - t), (n - i)) * pow(t, i) * Ps[i].y;
	}
	return P_t;
}

int main() {
	vector2d Ps[4];
	GetPoint(&Ps[0], 0, 0);
	GetPoint(&Ps[1], 5, 0);
	GetPoint(&Ps[2], 10, 5);
	GetPoint(&Ps[3], 15, 5);
	int t0 = 100;//间隔，类似间隔抽样

	FILE* fp1, *fp2; //写入txt文件
	fp1 = fopen("Pt.txt", "w");
	fp2 = fopen("line.txt", "w");
	if (fp1 == NULL || fp2 == NULL) {
		return 0;
	}
	for (int i = 0; i < 4; ++i) {
		fprintf(fp1, "%.3lf %.3lf\n", Ps[i].x, Ps[i].y);
	}

	for (int t = 0; t <= t0; ++t) {
		vector2d pos = BezierCommon(Ps, 4, (double)t / t0); //计算在t的时候的点的坐标
		printf("点%d: (%.3lf,%.3lf)\n", t + 1, pos.x, pos.y); //打印点的坐标
		fprintf(fp2, "%.3lf %.3lf\n", pos.x,  pos.y);
	}


	fclose(fp1);
	fclose(fp2);
	return 0;
}



