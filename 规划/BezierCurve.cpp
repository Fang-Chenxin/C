#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//����������������꣬���ڸ�ֵ��ȡֵ 
class vector2d {
	public:
		double x,y;
		vector2d(double P1,double P2) {
			x = P1;
			y = P2;
		}	
};


//�ݹ��� n! 
double factorial(int n) {
    if(n<=1)return 1;
    return factorial(n-1)*n;
}

//���������߱��ʽ 
vector2d BezierCommon(vector<vector2d> Ps,double t){
	int n = Ps.size()-1;//���� 
	if(n == 0){//һ�����ʱ�򷵻����� 
		return Ps[0];
	}
	vector2d P_t(0,0); 
	for(int i=0;i<Ps.size();++i){
		double C_n_i = factorial(n)/ (factorial(i)* factorial(n-i));//�����������ʽչ�������ϵ��
		P_t.x += C_n_i*pow((1-t),(n-i))*pow(t,i)*Ps[i].x;
		P_t.y += C_n_i*pow((1-t),(n-i))*pow(t,i)*Ps[i].y;	
	}
	return P_t;
}

int main(){
	vector<vector2d> Ps{vector2d(0,0),vector2d(3,0),vector2d(8,5),vector2d(13,5)};
	int t0 = 100;//��������Ƽ������ 
	for(int t=0;t<t0;++t){
		vector2d pos = BezierCommon(Ps,(double)t/t0);//������t��ʱ��ĵ������ 
		printf("��%d: (%.2lf,%.2lf)\n",t+1,pos.x,pos.y);//��ӡ������� 
	}
	return 0;
}




