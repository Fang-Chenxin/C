#include <stdio.h>
#include <math.h>

/*
start_x����ʼλ��
end_x������λ��
now_x:��ǰλ��
set_a���趨���ٶ�
Vm���趨����ٶ�
*/

double Trapezoidal_curve_speed(double start_x, double end_x, double now_x, double set_a, double Vm) {
	double s = now_x - start_x;//��ǰλ��
	if (now_x > end_x) {
		return 0;
	}
	if (end_x - start_x <= Vm * Vm / set_a ) { //�����ι���
		if (s <= (end_x - start_x) / 2) { //���ٹ���
			return sqrt(2 * s * set_a);
		} else { //���ٹ���
			return sqrt(2 * (end_x - now_x) * set_a);
		}
	} else {//��������
			if (s <= Vm * Vm / (2 * set_a)) {//���ٹ���
				return sqrt(2 * s * set_a);
			} else if (Vm * Vm / (2 * set_a) < s && s < end_x - Vm * Vm / (2 * set_a)) {//���ٹ��� 
				return Vm;
			} else 
			{
				return sqrt(2 * (end_x - s) * set_a);//���ٹ��� 
			}
	}
}

int main() 
{
	double x1[33]={} , v1[33]={} ;
	int i=0;
	for(i;i<33;i++)
	{
		x1[i]=i+1;
	}
	double start_x=1,end_x=31,Vm=5,set_a=1;
	for(i=0;i<33;i++)
	{
		v1[i]=Trapezoidal_curve_speed(start_x,end_x,x1[i],set_a,Vm); 
		printf("%d : %f\n",i+1,v1[i]);
	}
}

//int main() {
//	double set_a = 2, Vm = 10, start_x = 5, end_x = 35; //����������
//	double now_x[35], now_v[35];
//	for (int i = 0; i < 35; ++i) {
//		now_x[i] = i + 5;
//		printf("%d:%lf\n", i, now_x[i]);
//	}
//
//	printf("start_x:%lf\nend_x:%lf\n", start_x, end_x);
//	for (int i = 0; i < 35; ++i) {
//		now_v[i] = Trapezoidal_curve_speed(start_x, end_x, now_x[i], set_a, Vm);
//		printf("%d:%lf\n", i, now_v[i]);
//	}
//
//}
