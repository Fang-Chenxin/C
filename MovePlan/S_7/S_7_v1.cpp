#include<stdio.h>
#include<math.h>

#define F17   double 

/*
		完整七段：
		t1=am/j;
		t2=(vtar-vs)/am-t1;
		t3=t1;
		t4=0;
		t5=am/j;
		t6=(vtar-ve)/am-t5;
		t7=t5;

		a1=j*t1;
		a2=am;
		a3=am-j*t3;
		a4=0;
		a5=-j*t5;
		a6=-dam;
		a7=-dam+j*t7;

		v1 = vs + j * t1 * t1 / 2;
		v2 = v1 + am*t2;
		v3 = v2 + j * t1 * t1/2;
		v4 = v3;
		v5 = v4 - j * t5 * t5/2;
		v6 = v5 - am*t6;
		v7 = v6 - j*t5*t5/2;

		s1=vs*t1+j*t1*t1*t1/6;
		s2=s1+v1*t2+j*t1*t2*t2/2;
		s3=s2+v2*t1-j*t1*t1*t1/6;
		s4=s3+v3*t4;
		s5=s4+v4*t5-j*t5*t5*t5/6;
		s6=s5+vs*t6-j*t5*t6*t6/2;
		s7=s6+v6*t5-j*t5*t5*t5/3;*/

F17 j = 0.5;//给定加加速度
F17 am, vm, dam;//最大加速段加速度，最大速度，最大减速段加速度 
F17 vtar=5, atar=2, datar=2;//给定最大目标参数 
F17 L;//目标位移，实际加速和减速的位移之和 
F17 S=40;//总位移量，待输入值
F17 ds;
F17 vs=0, ve=0;//初速度,末速度 
F17 t1, t2, t3, t4, t5, t6, t7;//各段时间长度 
F17 v1, v2, v3, v4, v5, v6, v7;//各段速度末端值 
F17 s1, s2, s3, s4, s5, s6, s7;//距离长度 
F17 T1, T2, T3, T4, T5, T6, T7;//各段时间总和 
F17 S1, S2, S3, S4, S5, S6, S7;//各段距离之和 

F17 Clat(F17 s);
void Cla();
F17 Clav(F17 x);
int main() {
	/*输入总位移量S，初速度vs，末速度ve，给定目标最大参数vtar，atar，datar*/
	Cla();
	/*printf("%f %f %f %f %f %f %f\n", t1, t2, t3, t4, t5, t6, t7);
	printf("%f %f %f %f %f %f %f\n", v1, v2, v3, v4, v5, v6, v7);
	printf("%f %f %f %f %f %f %f\n", s1, s2, s3, s4, s5, s6, s7);
	printf("%f %f %f %f %f %f %f\n", S1, S2, S3, S4, S5, S6, S7);
	printf("%f %f %f %f %f %f %f\n", T1, T2, T3, T4, T5, T6, T7);
	for (F17 x = 0; x <= S; x+=1) {
		printf("%f\n", Clav(x));
	}
	Clav(25);*/
	F17 x;//输入距离信息 
	F17 v=Clav(x);//获取速度信息 
	return 0;
}
F17 Clat(F17 s) {//根据位移量反映时间
	if (s >= 0 && s < S1) {
		for (F17 t = 0; t <= t1; t += 0.01) {
			if (abs(s - (vs * t + j * t * t * t / 6))<=0.5) return t;
		}
	}
	else if (s >= S1 && s < S2) {
		for (F17 t = 0; t <= t2; t += 0.01) {
			if (abs(s -(S1 + v1 * t + j * t1 * t * t / 2))<=0.5) return t+T1;
		}
	}
	else if (s >= S2 && s < S3) {
		for (F17 t = 0; t <= t3; t += 0.01) {
			if (abs(s - (S2 + v2 * t + j * t * t * t1 / 2 - j * t * t * t / 6))<=0.5) return t+T2;
		}
	}
	else if (s >= S3 && s < S4) {
		for (F17 t = 0; t <= t4; t += 0.01) {
			if (abs(s - (S3 + v3 * t))<=0.5) return t+T3;
		}
	}
	else if (s >= S4 && s < S5) {
		for (F17 t = 0; t <= t5; t += 0.01) {
			if (abs(s - (S4 + v4 * t - j * t * t * t / 6))<=0.5) return t+T4;
		}
	}
	else if (s >= S5 && s < S6) {
		for (F17 t = 0; t <= t6; t += 0.01) {
			if (abs(s- (S5 + v5 * t - j * t5 * t * t / 2))<=0.5) return t+T5;
		}
	}
	else if (s >= S6 && s < S7) {
		for (F17 t = 0; t <= t7; t += 0.01) {
			if (abs(s- (S6 + v6 * t - j * t5 * t * t/2 + j * t * t * t / 6))<=0.5) return t+T6;
		}
	}
	else if(s == S7){
		return T7;
	}
	else return 0;
}
void Cla() {
	if ((vtar - vs) > (atar * atar) / j)//存在匀加速段 
	{
		am = atar;
		t1 = am / j;
		v1 = vs + j * t1 * t1 / 2;
		s1 = vs * t1 + j * t1 * t1 * t1 / 6;

		t2 = (vtar - vs) / am - t1;
		v2 = v1 + am * t2;
		s2 = v1 * t2 + am * t1 * t2 * t2 / 2;

		t3 = t1;
		v3 = v2 + j * t1 * t1 / 2;
		s3 = v2 * t1 + j * t1 * t1 * t1 / 3;
	}
	else//不存在匀加速段 
	{
		am = sqrt((vtar - vs) * j);
		t1 = sqrt((vtar - vs) / j);
		s1 = vs * t1 + j * t1 * t1 * t1 / 6;
		v1 = vs + j * t1 * t1 / 2;

		t2 = 0;
		v2 = v1;
		s2 = 0;

		t3 = t1;
		s3 = v2 * t1 + j * t1 * t1 * t1 / 3;
		v3 = v2 + j * t1 * t1 / 2;
	}
	//减速段
	if ((vtar - ve) > (datar * datar) / j) //存在匀减速段 
	{
		dam = datar;
		t7 = dam / j;
		v6 = ve + 0.5 * j * t7 * t7;
		s7 = ve * t7 + j * t7 * t7 * t7 / 6;

		t6 = (vtar - ve) / dam - t7;
		s6 = v6 * t6 + 0.5 * j * t6 * t6 * t7;
		v5 = v6 + am * t6;

		t5 = t7;
		s5 = v5 * t5 + j * t5 * t5 * t5 / 3;
	}
	else//不存在匀减速段 
	{
		dam = sqrt((vtar - ve) * j);
		t7 = sqrt((vtar - ve) / j);
		v6 = ve + 0.5 * j * t7 * t7;
		s7 = ve * t7 + j * t7 * t7 * t7 / 6;

		v5 = v6;
		t6 = 0;
		s6 = 0;

		t5 = t7;
		s5 = v5 * t5 + j * t5 * t5 * t5 / 3;
	}

	//L = 0.5 * ((vs + vtar) * (t1 + t2 + t3) + (ve+ vtar) * (t5 + t6 + t7));
	L = s1 + s2 + s3 + s5 + s6 + s7;
	//能达到预期最大速度，即存在匀速段 
	if (L <= S) {
		s4 = S - L;
		v4=v3;
		t4 = s4 / v4;
		vm = vtar;

	}
	//达不到最大速度，重新规划速度，改为四段曲线
	else {
		F17 vl, aml, ta, daml, td, Ll;
		F17 dv = 0.1;//步减速度大小,可调
		vl = vtar - dv;
		aml = sqrt((vl - vs) * j);
		ta = sqrt((vl - vs) / j);
		daml = sqrt((vl - ve) * j);
		td = sqrt((vl - ve) / j);
		Ll = 2 * (j * ta * ta * ta / 6 + vs * ta + j * td * td * td / 6 + ve * td);
		while (Ll <= S && vl > vs && vl > ve) {
			vl = vl - dv;
			aml = sqrt((vl - vs) * j);
			ta = sqrt((vl - vs) / j);
			daml = sqrt((vl - ve) * j);
			td = sqrt((vl - ve) / j);
			Ll = 2 * (j * ta * ta * ta / 6 + vs * ta + j * td * td * td / 6 + ve * td);
		}

		am = aml;
		vm = vl;
		dam = daml;

		t1 = t3 = ta;
		t2 = t4 = t6 = 0;
		t5 = t7 = td;

		v1 = vs + j * t1 * t1 / 2;
		v2 = v1;
		v3 = v2 + j * t1 * t1 / 2;
		v4 = v3;
		v6 = ve + j * t7 * t7 / 2;
		v5 = v6;

		s1 = vs * t1 + j * t1 * t1 * t1 / 6;
		s2 = 0;
		s3 = v2 * t1 + j * t3 * t3 * t3 / 3;
		s4 = 0;
		s5 = v4 * t5 - j * t5 * t5 * t5 / 6;
		s6 = 0;
		s7 = v6 * t5 - j * t5 * t5 * t5 / 3;
	}

	T1 = t1;
	T2 = T1 + t2;
	T3 = T2 + t3;
	T4 = T3 + t4;
	T5 = T4 + t5;
	T6 = T5 + t6;
	T7 = T6 + t7;

	S1 = s1;
	S2 = S1 + s2;
	S3 = S2 + s3;
	S4 = S3 + s4;
	S5 = S4 + s5;
	S6 = S5 + s6;
	S7 = S6 + s7;
}
F17 Clav(F17 x) {//输出当前位移量可得到当前速度值
	F17 vcur, scur;//当前信息
	//根据位移获取时间信息 
	F17 t = Clat(x);
	//根据时间反馈速度
	F17 dt=0;
	if (t < T1 && t >= 0) {
		dt=t-0;
		vcur = vs + 0.5 * j * dt;
		//scur = vs * dt + j * dt * dt * dt / 6;//可用于检测误差值
		return vcur;
	}
	else if (t >= T1 && t < T2) {
		dt=t-T1;
		vcur = v1 + am * dt;
		//scur = S1 + v1 * dt + j * t1 * dt * dt / 2;//可用于检测误差值
		return vcur;
	}
	else if (t >= T2 && t < T3) {
		dt=t-T2;
		vcur = v2 + am * dt - j * dt * dt / 2;
		//scur = S2 + v2 * dt + j * t1 * dt * dt / 2 - j * dt * dt * dt / 6;//可用于检测误差值
		return vcur;
	}
	else if (t >= T3 && t < T4) {
		dt=t-T3;
		vcur = v3;
		//scur = S3 + v3 * dt;//可用于检测误差值
		return vcur;
	}
	else if (t >= T4 && t < T5) {
		dt=t-T4;
		vcur = v4 - j*dt*dt/2;
		//scur = S4 + v4 * dt - j * dt * dt * dt / 6;//可用于检测误差值
		return vcur;
	}
	else if (t >= T5 && t < T6) {
		dt=t-T5;
		vcur = v5 - am * dt;
		//scur = S5 + v5 * dt - j * t5 * dt * dt / 2;//可用于检测误差值
		return vcur;
	}
	else if (t >= T6 && t < T7) {
		dt=t-T6;
		vcur = v6 - am * dt + j * dt * dt / 2;
		//scur = S6 + v6 * dt - j * t5 * dt * dt / 2 + j * dt * dt * dt / 6;//可用于检测误差值
		return vcur;
	}
	else if(t==T7){
		vcur = ve;
		//scur = S;//可用于检测误差值
		return vcur;
	}
}
