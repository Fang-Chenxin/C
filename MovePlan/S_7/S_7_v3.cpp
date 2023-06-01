#include<stdio.h>
#include<math.h>

#define F17   double 
#define INF   1000000;

typedef struct Cur_point_inf {
	F17 x;//距离信息，已知
	F17 t;//运动时间
	F17 a;//当前加速度
	F17 v;//当前速度
	F17 s;//当前距离，用于误差分析
}CUR_POINT_INF;
typedef struct prar_inf {
	F17 j;//给定加加速度
	F17 am;
	F17	vm;
	F17 dam;//最大加速段加速度 
	F17 vtar;//目标最大速度
	F17 atar;//目标最大加速段加速度
	F17 datar;//最大减速段加速度
	F17 SS;//总位移量，待输入值
	F17 vs;//初速度
	F17 ve;//末速度 

}PRAR_INF;


F17 t[7] = { 0 };//各段时间长度
F17 v[7] = { 0 };//各段速度末端值 
F17 a[7] = { 0 };//各段加速度末端值
F17 s[7] = { 0 };//距离长度 
F17 T[7] = { 0 };//各段时间总和 
F17 S[7] = { 0 };//各段距离之和

void ass(PRAR_INF* prarmeter);//给必要参数赋值
F17 Cal_t(F17 x, PRAR_INF* prarmeter);//根据当前距离获得当前时间信息
void Caltulate(F17* t, F17* a, F17* v, F17* s, F17* T, F17* S, PRAR_INF* prarmeter);//计算各段的t,a,v,s
void Cal_Cur_point(F17 x,CUR_POINT_INF *Cur_point, PRAR_INF* prarmeter);//根据当前距离计算当前速度信息

int main() {
	/*输入总位移量S，初速度vs，末速度ve，给定目标最大参数vtar，atar，datar*/
	PRAR_INF p;
	ass(&p);
	Caltulate(t,a,v,s,T,S,&p);
	//Cal_Cur_point(Cur_point.x,&Cur_point);
	for (int i = 0; i < 7; i++) {
		printf("第%d段时间长度为%f\n", i + 1, t[i]);
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		printf("第%d段末端加速度值为%f\n", i + 1, a[i]);
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		printf("第%d段末端速度值为%f\n", i + 1, v[i]);
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		printf("第%d段距离长度为%f\n", i + 1, s[i]);
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		printf("前%d段总时间为%f\n", i + 1, T[i]);
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		printf("前%d段总距离为%f\n", i + 1, S[i]);
	}
	printf("\n");
	for (F17 i = 0; i <= p.SS; i+=0.1) {
		CUR_POINT_INF Cur_point;
		Cur_point.x = i;
		Cal_Cur_point(Cur_point.x, &Cur_point,&p);
		printf("当前距离为%.4f,当前时间为%.4f,当前加速度%.4f,当前速度%.4f,当前距离%.4f\n", Cur_point.x, Cur_point.t,Cur_point.a, Cur_point.v, Cur_point.s);
	}
	//printf("当前加速度%f\n当前速度%f\n当前距离%f\n", Cur_point.a, Cur_point.v, Cur_point.s);
	return 0;
}
F17 Cal_t(F17 x, PRAR_INF* prarmeter) {//根据距离得到相应的时间

	F17 vs = prarmeter->vs;
	F17 j = prarmeter->j;

	if (x >= 0 && x < S[0]) {
		for (F17 dt = 0; dt <= t[0]; dt += 0.0001) {
			if (fabs(x - (vs * dt + j * dt * dt * dt / 6)) <= 0.001) return dt;
		}
	}
	else if (x >= S[0] && x < S[1]) {
		for (F17 dt = 0; dt <= t[1]; dt += 0.0001) {
			if (fabs(x - (S[0] + v[0] * dt + j * t[0] * dt * dt / 2)) <= 0.001) return dt + T[0];
		}
	}
	else if (x >= S[1] && x < S[2]) {
		for (F17 dt = 0; dt <= t[2]; dt += 0.0001) {
			if (fabs(x - (S[1] + v[1] * dt + j * dt * dt * t[0] / 2 - j * dt * dt * dt / 6)) <= 0.001) return dt + T[1];
		}
	}
	else if (x >= S[2] && x < S[3]) {
		for (F17 dt = 0; dt <= t[3]; dt += 0.0001) {
			if (fabs(x - (S[2] + v[2] * dt)) <= 0.001) return dt + T[2];
		}
	}
	else if (x >= S[3] && x < S[4]) {
		for (F17 dt = 0; dt <= t[4]; dt += 0.0001) {
			if (fabs(x - (S[3] + v[3] * dt - j * dt * dt * dt / 6)) <= 0.001) return dt + T[3];
		}
	}
	else if (x >= S[4] && x < S[5]) {
		for (F17 dt = 0; dt <= t[5]; dt += 0.0001) {
			if (fabs(x - (S[4] + v[4] * dt - j * t[4] * dt * dt / 2)) <= 0.001) return dt + T[4];
		}
	}
	else if (x >= S[5] && x < S[6]) {
		for (F17 dt = 0; dt <= t[6]; dt += 0.0001) {
			if (fabs(x - (S[5] + v[5] * dt - j * t[4] * dt * dt / 2 + j * dt * dt * dt / 6)) <= 0.001) return dt + T[5];
		}
	}
	else if (x == S[6]) {
		return T[6];
	}
	else {
		return INF;
	}
	return INF;
}
void Caltulate(F17* t, F17* a, F17* v, F17* s, F17* T, F17* S, PRAR_INF* prarmeter) {

	F17 j = prarmeter->j;//给定加加速度
	F17 vtar = prarmeter->vtar;
	F17 atar = prarmeter->atar;
	F17 datar = prarmeter->datar;//给定最大目标参数 
	F17 SS = prarmeter->SS;//总位移量，待输入值
	F17 vs = prarmeter->vs;
	F17 ve = prarmeter->ve;//初速度,末速度 
	F17 L=0;
	F17 am;
	F17 dam;
	F17 vm;

	if ((vtar - vs) > (atar * atar) / j)//存在匀加速段 
	{
		am = atar;
		t[0] = am / j;		
		t[1] = (vtar - vs) / am - t[0];		
		t[2] = t[0];
	}
	else//不存在匀加速段 
	{
		am = sqrt((vtar - vs) * j);
		t[0] = sqrt((vtar - vs) / j);		
		t[1] = 0;
		t[2] = t[0];

	}
	//减速段
	if ((vtar - ve) > (datar * datar) / j) //存在匀减速段 
	{
		dam = datar;
		t[6] = dam / j;
		t[5] = (vtar - ve) / dam - t[6];
		t[4] = t[6];
	}
	else//不存在匀减速段 
	{
		dam = sqrt((vtar - ve) * j);
		t[6] = sqrt((vtar - ve) / j);
		t[5] = 0;
		t[4] = t[6];
	
	}

	L = 0.5 * ((vs + vtar) * (t[0] + t[1] + t[2]) + (ve+ vtar) * (t[4] + t[5] + t[6]));
	//L=2*(vs*(2*t[0]+t[1])+j*t[0]*t[0]*t[0]+j*t[0]*t[0]*t[1]/2);
	//L = s[0] + s[1] + s[2] + s[4] + s[5] + s[6];
	//能达到预期最大速度，即存在匀速段 
	if (L <= SS) {
		vm = vtar;
		s[3]=SS-L;
		t[3] = s[3]/vm;
	}
	//达不到最大速度，重新规划速度，改为四段曲线
	else {
		/*初、末速度不同是采用以下规划方法，规划效果差 
		F17 vl, aml, ta, daml, td, Ll;
		F17 dv = 0.001;//步减速度大小,可调
		vl = vtar - dv;
		ta = sqrt((vl - vs) / j);
		aml=j*ta;
		td = sqrt((vl - ve) / j);
		daml=j*td;
		Ll = vs*ta+j*ta*ta*ta/2+j*ta*ta+ve*td+j*td*td*td/2+j*td*td;
		while (Ll >= SS && vl > vs && vl > ve) {
			vl = vl - dv;
			ta = sqrt((vl - vs) / j);
			td = sqrt((vl - ve) / j);
			aml=j*ta;
			daml=j*td;
			Ll = vs*ta+j*ta*ta*ta/2+j*ta*ta+ve*td+j*td*td*td/2+j*td*td;
		}	
		*/
		//初、末速度相同且加速段加速度等于减速段减速度时，采用以下规划方法
		F17 t_ad,Ll;
		F17 dt=0;
		while(1){
			Ll=j*dt*dt*dt+2*j*dt*dt+2*vs*dt;
			if(fabs(Ll-SS)<=0.001){
				t_ad=dt;
				break;
			}
			else dt+=0.0001;
		} 
		
		vm=j*t_ad*t_ad+vs;
		am=dam=j*t_ad;	
		
		t[0] = t[2] = t_ad;
		t[1] = t[3] = t[5] = 0;
		t[4] = t[6] = t_ad;

	}
	
	a[0]=j*t[0];
	a[1]=am;
	a[2]=am-j*t[2];
	a[3]=0;
	a[4]=-j*t[4];
	a[5]=-am;
	a[6]=-am+j*t[6];
	
	v[0]=vs+j*t[0]*t[0]/2;
	v[1]=v[0]+am*t[1];
	v[2]=v[1]+j*t[0]*t[0]/2;
	v[3]=v[2];
	v[4]=v[3]-j*t[4]*t[4]/2;
	v[5]=v[4]-am*t[5];
	v[6]=v[5]-j*t[4]*t[4]/2;
	
	s[0]=vs*t[0]+j*t[0]*t[0]*t[0]/6;
	s[1]=v[0]*t[1]+j*t[0]*t[1]*t[1]/2;
	s[2]=v[1]*t[0]+j*t[0]*t[0]*t[0]/3;
	s[3]=v[2]*t[3];
	s[4]=v[3]*t[4]-j*t[4]*t[4]*t[4]/6;
	s[5]=v[4]*t[5]-j*t[4]*t[5]*t[5]/2;
	s[6]=v[5]*t[4]-j*t[4]*t[4]*t[4]/3;
	
	prarmeter->am = am;
	prarmeter->dam = dam;
	prarmeter->vm = vm;
	
	
	T[0] = t[0];
	T[1] = T[0] + t[1];
	T[2] = T[1] + t[2];
	T[3] = T[2] + t[3];
	T[4] = T[3] + t[4];
	T[5] = T[4] + t[5];
	T[6] = T[5] + t[6];

	S[0] = s[0];
	S[1] = S[0] + s[1];
	S[2] = S[1] + s[2];
	S[3] = S[2] + s[3];
	S[4] = S[3] + s[4];
	S[5] = S[4] + s[5];
	S[6] = S[5] + s[6];
}
void Cal_Cur_point(F17 x, CUR_POINT_INF *Cur_point, PRAR_INF* prarmeter) {//输出当前位移量可得到当前速度值

	F17 j = prarmeter->j;;//给定加加速度
	F17 am = prarmeter->am;
	F17 vm = prarmeter->vm;
	F17 dam = prarmeter->dam;//最大加速段加速度，最大速度，最大减速段加速度 
	F17 vtar = prarmeter->vtar;
	F17 atar = prarmeter->atar;
	F17 datar = prarmeter->datar;//给定最大目标参数 
	F17 SS = prarmeter->SS;//总位移量，待输入值
	F17 vs = prarmeter->vs;
	F17 ve = prarmeter->ve;//初速度,末速度 

	F17 t1 = Cal_t(x, prarmeter);//获得当前距离x所对应的时间t
	//根据时间反馈速度
	F17 dt = 0;
	if (t1 < T[0] && t1 >= 0) {
		dt = t1 - 0;
		Cur_point->t = t1;
		Cur_point->a = j * dt;
		Cur_point->v = vs + 0.5 * j * dt;
		Cur_point->s = vs * dt + j * dt * dt * dt / 6;//可用于检测误差值

	}
	else if (t1 >= T[0] && t1 < T[1]) {
		dt = t1 - T[0];
		Cur_point->t = t1;
		Cur_point->a = am;
		Cur_point->v = v[0] + am * dt;
		Cur_point->s = S[0] + v[0] * dt + j * t[0] * dt * dt / 2;//可用于检测误差值
	}
	else if (t1 >= T[1] && t1 < T[2]) {
		dt = t1 - T[1];
		Cur_point->t = t1;
		Cur_point->a= am - j * dt;
		Cur_point->v = v[1] + am * dt - j * dt * dt / 2;
		Cur_point->s = S[1] + v[1] * dt + j * t[0] * dt * dt / 2 - j * dt * dt * dt / 6;//可用于检测误差值
	}
	else if (t1 >= T[2] && t1 < T[3]) {
		dt = t1 - T[2];
		Cur_point->t = t1;
		Cur_point->a = 0;
		Cur_point->v = v[2];
		Cur_point->s = S[2] + v[2] * dt;//可用于检测误差值
	}
	else if (t1 >= T[3] && t1 < T[4]) {
		dt = t1 - T[3];
		Cur_point->t = t1;
		Cur_point->a = -j * dt;
		Cur_point->v = v[3] - j * dt * dt / 2;
		Cur_point->s = S[3] + v[3] * dt - j * dt * dt * dt / 6;//可用于检测误差值
	}
	else if (t1 >= T[4] && t1 < T[5]) {
		dt = t1 - T[4];
		Cur_point->t = t1;
		Cur_point->a = -am;
		Cur_point->v = v[4] - am * dt;
		Cur_point->s = S[4] + v[4] * dt - j * t[4] * dt * dt / 2;//可用于检测误差值
	}
	else if (t1 >= T[5] && t1 < T[6]) {
		dt = t1 - T[5];
		Cur_point->t = t1;
		Cur_point->a = -am + j * dt;
		Cur_point->v = v[5] - am * dt + j * dt * dt / 2;
		Cur_point->s = S[5] + v[5] * dt - j * t[4] * dt * dt / 2 + j * dt * dt * dt / 6;//可用于检测误差值
	}
	else if (t1 == T[6]) {
		Cur_point->t = t1;
		Cur_point->v = ve;
		Cur_point->a = 0;
		Cur_point->s = SS;//可用于检测误差值
	}
	else {//查询距离超过总距离SS
		Cur_point->t = INF;
		Cur_point->a = 0;
		Cur_point->v = ve;
		Cur_point->s = INF;
	}
}
void ass(PRAR_INF *prarmeter) {
	prarmeter->vtar = 10;
	prarmeter->atar = 5;
	prarmeter->datar = 5;//一般来说和加速段限定加速度相等
	prarmeter->SS = 10;
	prarmeter->ve = 0;
	prarmeter->vs = 0;
	prarmeter->j = 1;
}
