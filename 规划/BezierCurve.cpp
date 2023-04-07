#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//用类来创建点的坐标，便于赋值和取值 
class vector2d {
	public:
		double x,y;
		vector2d(double P1,double P2) {
			x = P1;
			y = P2;
		}	
};


//递归求 n! 
double factorial(int n) {
    if(n<=1)return 1;
    return factorial(n-1)*n;
}

//贝塞尔曲线表达式 
vector2d BezierCommon(vector<vector2d> Ps,double t){
	int n = Ps.size()-1;//连线 
	if(n == 0){//一个点的时候返回自身 
		return Ps[0];
	}
	vector2d P_t(0,0); 
	for(int i=0;i<Ps.size();++i){
		double C_n_i = factorial(n)/ (factorial(i)* factorial(n-i));//组合数，二项式展开定理的系数
		P_t.x += C_n_i*pow((1-t),(n-i))*pow(t,i)*Ps[i].x;
		P_t.y += C_n_i*pow((1-t),(n-i))*pow(t,i)*Ps[i].y;	
	}
	return P_t;
}

int main(){
	vector<vector2d> Ps{vector2d(0,0),vector2d(3,0),vector2d(8,5),vector2d(13,5)};
	int t0 = 100;//间隔，类似间隔抽样 
	for(int t=0;t<t0;++t){
		vector2d pos = BezierCommon(Ps,(double)t/t0);//计算在t的时候的点的坐标 
		printf("点%d: (%.2lf,%.2lf)\n",t+1,pos.x,pos.y);//打印点的坐标 
	}
	return 0;
}




