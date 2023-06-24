#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI 3.1415926
#define ERROR -1
#define OK 0

// /**
//  * @brief 七段正弦速度规划关键点结构体
//  * @param vv[7] 储存分界点速度的数组    
//  * @param t[7] 储存各个运动阶段所需时间的数组
//  * @param T[7] 储存各个运动阶段分界时间的数组
//  * @param x[7] 储存各个运动阶段分界位置的数组
//  * @note 以下是数组下标和运动阶段的对应关系
//  * @note 0 加加速阶段
//  * @note 1 匀加速阶段
//  * @note 2 减加速阶段
//  * @note 3 匀速阶段
//  * @note 4 加减速阶段
//  * @note 5 匀减速阶段
//  * @note 6 减减速阶段
//  */
// struct S7S_KeyPointType
// {
//     double vv[7] = { 0 };//储存分界点速度的数组
//     double t[7] = { 0 }; //储存各个运动阶段所需时间的数组
//     double T[7] = { 0 }; //储存各个运动阶段分界时间的数组
//     double x[7] = { 0 }; //储存各个运动阶段分界位置的数组
// }KeyPoint;

double vv[7] = { 0 };//储存分界点速度的数组
double t[7] = { 0 }; //储存各个运动阶段所需时间的数组
double T[7] = { 0 }; //储存各个运动阶段分界时间的数组
double x[7] = { 0 }; //储存各个运动阶段分界位置的数组

struct DynamicType
{
    double j; //加加速度
    double a; //加速度
    double v; //速度
    double s; //位移
}Dynamic;


void SpeedPlan_S(double s_target, double v_target, double a_max, double j_max);
double segment_rearrange(double v_act, double a_max, double j_max);
double calculate_accelration_distance(double a_act);
double lookup_t(double xx, double j_max);
void Init(double j_max);
int solve_move(double tt, double j_max);
double j(double tt, double j_max);
double a(double tt, double j_max);
double v(double tt, double j_max);
double s(double tt, double j_max);
double Anwser_Equation(double xx, double a, double b, double j_max);
void DebugPrint(double j_max,double s_target);

void DebugPrint(double j_max,double s_target)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        printf("t[%d] = %f\n", i, t[i]);
    }
    printf("\n");
    for (i = 0; i < 7; i++)
    {
        printf("x[%d] = %f\n", i, x[i]);
    }
    double tt = 0;
    double xx = 0;

    printf("\n");
    for (xx = 0.0; xx <= s_target; xx += 0.05)
    {
        tt = lookup_t(xx, j_max);
        solve_move(tt, j_max);
        printf("距离为%f时，时间为%f，加加速度为%f，加速度为%f，速度为%f，距离为%f\n", xx, tt,Dynamic.j, Dynamic.a, Dynamic.v, Dynamic.s);
    }
    printf("\n");
}
void test1(void)//有匀加减速，匀速
{
    int i;
    double s_target = 10;   //目标位移量
    double v_target = 2;  //目标最大速度
    double a_max = 1;   //最大加速度
    double j_max = 1;      //最大加加速度
    for (i = 0; i < 7; i++) //数组清零
    {
        T[i] = 0;
        vv[i] = 0;
        x[i] = 0;
        t[i] = 0;
    }
    SpeedPlan_S(s_target, v_target, a_max, j_max);
    printf("有匀加减速，有匀速\n");
    DebugPrint(j_max,s_target);
}
void test2(void) //无匀加减速，有匀速
{
    int i;
    double s_target = 10;   //目标位移量
    double v_target = 1;  //目标最大速度
    double a_max = 10;   //最大加速度
    double j_max = 1;      //最大加加速度
    for (i = 0; i < 7; i++) //数组清零
    {
        T[i] = 0;
        vv[i] = 0;
        x[i] = 0;
        t[i] = 0;
    }
    SpeedPlan_S(s_target, v_target, a_max, j_max);
    printf("无匀加减速，有匀速\n");
    DebugPrint(j_max,s_target);
}
void test3(void) //有匀加减速，无匀速
{
    int i;
    double s_target = 10;   //目标位移量
    double v_target = 5;  //目标最大速度
    double a_max = 1;   //最大加速度
    double j_max = 1;      //最大加加速度
    for (i = 0; i < 7; i++) //数组清零
    {
        T[i] = 0;
        vv[i] = 0;
        x[i] = 0;
        t[i] = 0;
    }
    SpeedPlan_S(s_target, v_target, a_max, j_max);
    printf("有匀加减速，无匀速\n");
    DebugPrint(j_max,s_target);
}
void test4(void) //无匀加减速，无匀速
{
    int i;
    double s_target = 1;   //目标位移量
    double v_target = 5;  //目标最大速度
    double a_max = 2;   //最大加速度
    double j_max = 1;      //最大加加速度
    for (i = 0; i < 7; i++) //数组清零
    {
        T[i] = 0;
        vv[i] = 0;
        x[i] = 0;
        t[i] = 0;
    }
    SpeedPlan_S(s_target, v_target, a_max, j_max);
    printf("无匀加减速，无匀速\n");
    DebugPrint(j_max,s_target);
}
int main(void)
{
    test1();            //有匀加减速，匀速
    test2();            //无匀加减速，有匀速
    test3();            //有匀加减速，无匀速
    test4();            //无匀加减速，无匀速
}

/**
 * @brief 规划主函数
 * 
 * @param s_target 
 * @param v_target 
 * @param a_max 
 * @param j_max 
 */
void SpeedPlan_S(double s_target, double v_target, double a_max, double j_max)
{
    double v_act = 0;           //运动过程中可到达的最大速度
    double a_act = 0;           //运动过程中可到达的最大加速度
    double s_T = 0;             //加速与减速段总位移

    double v_s = (a_max * a_max * PI) / (2 * j_max);  //无匀加速、匀减速过程系统可达到的最大速度
    v_act = v_target;           //假设实际规划可达最大速度为v_target
    a_act = segment_rearrange(v_act, a_max, j_max);
    s_T = calculate_accelration_distance(a_act);  //计算加速与减速段总位移
    if (s_target >= s_T)        //运动过程中存在匀速段 或 运动过程中不存在匀速段，实际的最大速度v_act可以达到指定的最大速度v_target，
    {
        t[3] = (s_target - s_T) / v_target;   //保持速度为v_target的匀速运动时间
    }
    else                        //运动过程中不存在匀速段，实际的最大速度v_max达不到目标的最大速度v_target
    {
        v_act = v_s;        //重新规划最大速度v_max,假设此时不包含匀加速和匀减速，恰好达到a_max
        a_act = segment_rearrange(v_act, a_max, j_max);
        s_T = calculate_accelration_distance(a_act);  //计算加速与减速段总位移
        if (s_target == s_T){}         //则上述假设成立，v_s就是实际规划的最大速度，不包含匀加速和匀减速过程，曲线由加加速、减加速、加减速、匀减速、减减速五段组成
        else if (s_target > s_T)    //实际最大速度v_max比目标最大速度v_target小但大于目前规划的最大速度v_s，所以运动过程包含匀加速和匀减速，曲线由加加速、匀加速、减加速、加减速、匀减速、减减速六段组成
        {
            /*根据0.5*s_target=x[2]列出方程v_act^2+v_s*v_act-s=0*/
            v_act = (-v_s + sqrt(v_s * v_s + 4 * s_target)) / 2;
            segment_rearrange(v_act, a_max, j_max);
        }
        else if (s_target < s_T)            //不包含匀加速和匀减速，且实际最大速度比v_s还要小,所以曲线只由加加速、减加速、加减速、减减速四段组成
        {
            /*根据0.5*s_target=x[2]列出方程v_act^2+v_s*v_act-s=0*/
            v_act = pow((s_target * s_target * j_max)/(2 * PI), 1.0/3);
            segment_rearrange(v_act, a_max, j_max);
        }
    }
    Init(j_max);
}

/**
 * @brief 在限制条件下重新分段
 *
 * @param v_act 实际规划可达最大速度
 * @param a_max 限制的最大加速度
 * @param j_max 限制的最大加加速度
 * @return double
 * @note 会修改全局变量t[0]~t[6]
 */
double segment_rearrange(double v_act, double a_max, double j_max)
{
    double v_s = (a_max * a_max * PI) / (2 * j_max);  //无匀加速、匀减速过程系统可达到的最大速度
    double a_act = a_max;               //假设加速度可达到的最大值为a_act
    if (v_act >= v_s)                   //加速度达到了a_max
    {
        t[0] = t[2] = t[4] = t[6] = (a_act * PI) / (2 * j_max);      //由于对称所以这四段时间相等
        t[1] = t[5] = (v_act - v_s) / a_act;   //匀加速和匀减速过程所用时间
    }
    else                                //加速度达不到a_max，所以没有匀加速和匀减速过程
    {
        a_act = sqrt((2 * v_act * j_max) / PI);     //根据a_act=(2*j_max)/w=(2*j_max*t[0])/PI和t[0]=v_act/a_act可解得实际可到达的最大加速度
        t[0] = t[2] = t[4] = t[6] = v_act / a_act;  //根据v[2]=v_act可得v_act=a_act*t[0]                              
        t[1] = t[5] = 0;                            //加速过程中不存在匀加速段，即t[1]=0
    }
    return a_act;
}

double calculate_accelration_distance(double a_act)
{
    double w = PI / t[0];       //角频率
    vv[0] = 0.5 * a_act * (t[0] - sin(w * t[0]) / w);//加加速结束时的速度
    vv[1] = a_act * t[1] + vv[0];//匀加速结束时的速度

    x[0] = 0.25 * a_act * (t[0] * t[0] + 2 * cos(w * t[0]) / (w * w)) - a_act / (2 * w * w);//加加速结束时的位移
    x[1] = 0.5 * a_act * t[1] * t[1] + vv[0] * t[1] + x[0];//匀加速结束时的位移
    x[2] = 0.25 * a_act * (t[2] * t[2] - 2 * cos(w * t[2]) / (w * w)) + vv[1] * t[2] + a_act / (2 * w * w) + x[1];//减加速结束时的位移

    return x[2]*2;
}

/**
 * @brief 根据当前位置查找对应的时间
 *
 * @param xx 当前位置
 * @param j_max 最大加加速度
 * @return double 对应的时间
 */
double lookup_t(double xx, double j_max)
{
    double tt;
    double a, b, c;             //定义二次方程的二次项系数a、一次项系数b、常数项系数c
    double w = PI / t[0];       //角频率
    double a_act = j_max / w;//可到达的最大加速度
    if (xx >= 0 && xx < x[0])
    {
        return Anwser_Equation(xx, 0, T[0], j_max);
    }
    else if (xx > x[0] && xx <= x[1])
    {
        /*列出一元二次方程：0.5*a_act*(tt-T[0])^2+vv[0]*(tt-T[0])+x[0]-xx=0*/
        a = 0.5 * a_act;
        b = vv[0];
        c = x[0] - xx;
        tt = (-b + sqrt(b * b - 4 * a * c)) / (2 * a) + T[0];
        return tt;
    }
    else if (xx > x[1] && xx <= x[2])
    {
        return Anwser_Equation(xx, T[1], T[2], j_max);
    }
    else if (xx > x[2] && xx <= x[3])
        return (xx - x[2]) / vv[3] + T[2];
    else if (xx > x[3] && xx <= x[4])
    {
        return Anwser_Equation(xx, T[3], T[4], j_max);
    }
    else if (xx > x[4] && xx <= x[5])
    {
        /*列出一元二次方程：-0.5*a_act*(tt-T[4])^2+vv[4]*(tt-T[4])+x[4]-xx=0*/
        a = -0.5 * a_act;
        b = vv[4];
        c = x[4] - xx;
        tt = (-b + sqrt(b * b - 4 * a * c)) / (2 * a) + T[4];
        return tt;
    }
    else if (xx > x[5] && xx <= x[6])
    {
        return Anwser_Equation(xx, T[5], T[6], j_max);
    }
    else return ERROR;
}

/**
 * @brief 给分界点位置赋值
 * 
 * @param j_max 最大加加速度
 */
void Init(double j_max) 
{
    int i;
    T[0] = t[0];
    for (i = 1; i < 7; i++)
    {
        T[i] = T[i - 1] + t[i];
    }

    double w = PI / t[0];       //角频率
    double a_act = (2 * j_max) / w;//可到达的最大加速度
    vv[0] = 0.5 * a_act * (t[0] - sin(w * t[0]) / w);
    vv[1] = a_act * t[1] + vv[0];
    vv[2] = 0.5 * a_act * (t[2] + sin(w * t[2]) / w) + vv[1];
    vv[3] = vv[2];
    vv[4] = -0.5 * a_act * (t[4] - sin(w * t[4]) / w) + vv[3];
    vv[5] = -a_act * t[5] + vv[4];
    vv[6] = -0.5 * a_act * (t[6] + sin(w * t[6]) / w) + vv[5];
    x[0] = 0.25 * a_act * (t[0] * t[0] + 2 * cos(w * t[0]) / (w * w)) - a_act / (2 * w * w);
    x[1] = 0.5 * a_act * t[1] * t[1] + vv[0] * t[1] + x[0];
    x[2] = 0.25 * a_act * (t[2] * t[2] - 2 * cos(w * t[2]) / (w * w)) + vv[1] * t[2] + a_act / (2 * w * w) + x[1];
    x[3] = vv[2] * t[3] + x[2];
    x[4] = -0.25 * a_act * (t[4] * t[4] + 2 * cos(w * t[4]) / (w * w)) + vv[3] * t[4] + a_act / (2 * w * w) + x[3];
    x[5] = -0.5 * a_act * t[5] * t[5] + vv[4] * t[5] + x[4];
    x[6] = -0.25 * a_act * (t[6] * t[6] - 2 * cos(w * t[6]) / (w * w)) + vv[5] * t[6] - a_act / (2 * w * w) + x[5];
}

/**
 * @brief 求解运动学参数
 * 
 * @param tt 时间
 * @param j_max 最大加加速度
 * @return int 
 */
int solve_move(double tt, double j_max)
{
    double w = PI / t[0];      //角频率
    double a_act = (2 * j_max) / w;
    if (tt >= 0 && tt < T[0])
    {
        Dynamic.j = j_max * sin(w * tt);
        Dynamic.a = 0.5 * a_act * (1 - cos(w * tt));
        Dynamic.v = 0.5 * a_act * (tt - sin(w * tt) / (w));
        Dynamic.s = 0.25 * a_act * (tt * tt + 2 * cos(w * tt) / (w * w)) - a_act / (2 * w * w);
    }
    else if (tt > T[0] && tt <= T[1])
    {
        Dynamic.j = 0;
        Dynamic.a = a_act;
        Dynamic.v = a_act * (tt - T[0]) + vv[0];
        Dynamic.s = 0.5 * a_act * (tt - T[0]) * (tt - T[0]) + vv[0] * (tt - T[0]) + x[0];
    }
    else if (tt > T[1] && tt <= T[2])
    {
        Dynamic.j = -j_max * sin(w * (tt - T[1]));
        Dynamic.a = 0.5 * a_act * (1 + cos(w * (tt - T[1])));
        Dynamic.v = 0.5 * a_act * ((tt - T[1]) + sin(w * (tt - T[1])) / w) + vv[1];
        Dynamic.s = 0.25 * a_act * ((tt - T[1]) * (tt - T[1]) - 2 * cos(w * (tt - T[1])) / (w * w)) + vv[1] * (tt - T[1]) + a_act / (2 * w * w) + x[1];
    }
    else if (tt > T[2] && tt <= T[3])
    {
        Dynamic.j = 0;
        Dynamic.a = 0;
        Dynamic.v = vv[3];
        Dynamic.s = vv[3] * (tt - T[2]) + x[2];
    }
    else if (tt > T[3] && tt <= T[4])
    {
        Dynamic.j = -j_max * sin(w * (tt - T[3]));
        Dynamic.a = -0.5 * a_act * (1 - cos(w * (tt - T[3])));
        Dynamic.v = -0.5 * a_act * ((tt - T[3]) - sin(w * (tt - T[3])) / w) + vv[3];
        Dynamic.s = -0.25 * a_act * ((tt - T[3]) * (tt - T[3]) + 2 * cos(w * (tt - T[3])) / (w * w)) + vv[3] * (tt - T[3]) + a_act / (2 * w * w) + x[3];
    }
    else if (tt > T[4] && tt <= T[5])
    {
        Dynamic.j = 0;
        Dynamic.a = -a_act;
        Dynamic.v = -a_act * (tt - T[4]) + vv[4];
        Dynamic.s = -0.5 * a_act * (tt - T[4]) * (tt - T[4]) + vv[4] * (tt - T[4]) + x[4];
    }
    else if (tt > T[5] && tt <= T[6])
    {
        Dynamic.j = j_max * sin(w * (tt - T[5]));
        Dynamic.a = -0.5 * a_act * (1 + cos(w * (tt - T[5])));
        Dynamic.v = -0.5 * a_act * ((tt - T[5]) + sin(w * (tt - T[5])) / w) + vv[5];
        Dynamic.s = -0.25 * a_act * ((tt - T[5]) * (tt - T[5]) - 2 * cos(w * (tt - T[5])) / (w * w)) + vv[5] * (tt - T[5]) - a_act / (2 * w * w) + x[5];
    }
    else return ERROR;
    return OK;
}

double j(double tt, double j_max)
{
    double w = PI / t[0];      //角频率

    if (tt >= 0 && tt < T[0])
        return j_max * sin(w * tt);
    else if (tt > T[0] && tt <= T[1])
        return 0;
    else if (tt > T[1] && tt <= T[2])
        return -j_max * sin(w * (tt - T[1]));
    else if (tt > T[2] && tt <= T[3])
        return 0;
    else if (tt > T[3] && tt <= T[4])
        return -j_max * sin(w * (tt - T[3]));
    else if (tt > T[4] && tt <= T[5])
        return 0;
    else if (tt > T[5] && tt <= T[6])
        return j_max * sin(w * (tt - T[5]));
    else return ERROR;
}
double a(double tt, double j_max)
{
    double w = PI / t[0];       //角频率

    double a_act = (2 * j_max) / w;
    if (tt >= 0 && tt < T[0])
        return 0.5 * a_act * (1 - cos(w * tt));
    else if (tt > T[0] && tt <= T[1])
        return a_act;
    else if (tt > T[1] && tt <= T[2])
        return 0.5 * a_act * (1 + cos(w * (tt - T[1])));
    else if (tt > T[2] && tt <= T[3])
        return 0;
    else if (tt > T[3] && tt <= T[4])
        return -0.5 * a_act * (1 - cos(w * (tt - T[3])));
    else if (tt > T[4] && tt <= T[5])
        return -a_act;
    else if (tt > T[5] && tt <= T[6])
        return -0.5 * a_act * (1 + cos(w * (tt - T[5])));
    else return ERROR;
}
double v(double tt, double j_max)
{
    double w = PI / t[0];       //角频率

    double a_act = (2 * j_max) / w;//可到达的最大加速度
    if (tt >= 0 && tt < T[0])
        return 0.5 * a_act * (tt - sin(w * tt) / (w));
    else if (tt > T[0] && tt <= T[1])
        return a_act * (tt - T[0]) + vv[0];
    else if (tt > T[1] && tt <= T[2])
        return 0.5 * a_act * ((tt - T[1]) + sin(w * (tt - T[1])) / w) + vv[1];
    else if (tt > T[2] && tt <= T[3])
        return vv[3];
    else if (tt > T[3] && tt <= T[4])
        return -0.5 * a_act * ((tt - T[3]) - sin(w * (tt - T[3])) / w) + vv[3];
    else if (tt > T[4] && tt <= T[5])
        return -a_act * (tt - T[4]) + vv[4];
    else if (tt > T[5] && tt <= T[6])
        return -0.5 * a_act * ((tt - T[5]) + sin(w * (tt - T[5])) / w) + vv[5];
    else return ERROR;
}
double s(double tt, double j_max)
{
    double w = PI / t[0];       //角频率

    double a_act = (2 * j_max) / w;//可到达的最大加速度

    if (tt >= 0 && tt < T[0])
        return 0.25 * a_act * (tt * tt + 2 * cos(w * tt) / (w * w)) - a_act / (2 * w * w);
    else if (tt > T[0] && tt <= T[1])
        return 0.5 * a_act * (tt - T[0]) * (tt - T[0]) + vv[0] * (tt - T[0]) + x[0];
    else if (tt > T[1] && tt <= T[2])
        return 0.25 * a_act * ((tt - T[1]) * (tt - T[1]) - 2 * cos(w * (tt - T[1])) / (w * w)) + vv[1] * (tt - T[1]) + a_act / (2 * w * w) + x[1];
    else if (tt > T[2] && tt <= T[3])
        return vv[3] * (tt - T[2]) + x[2];
    else if (tt > T[3] && tt <= T[4])
        return -0.25 * a_act * ((tt - T[3]) * (tt - T[3]) + 2 * cos(w * (tt - T[3])) / (w * w)) + vv[3] * (tt - T[3]) + a_act / (2 * w * w) + x[3];
    else if (tt > T[4] && tt <= T[5])
        return -0.5 * a_act * (tt - T[4]) * (tt - T[4]) + vv[4] * (tt - T[4]) + x[4];
    else if (tt > T[5] && tt <= T[6])
        return -0.25 * a_act * ((tt - T[5]) * (tt - T[5]) - 2 * cos(w * (tt - T[5])) / (w * w)) + vv[5] * (tt - T[5]) - a_act / (2 * w * w) + x[5];
    else return ERROR;
}
/**
 * @brief 二分法求解方程s(tt,j_max) = xx的解
 *
 * @param xx 等式右边的值
 * @param a 左区间值
 * @param b 右区间值
 * @param j_max 最大jerk
 * @return double 时间tt
 */
double Anwser_Equation(double xx, double a, double b, double j_max)
{
    double x0 = (a + b) / 2;                             // initial guess
    double x1 = x0 - (s(x0, j_max) - xx) / v(x0, j_max); // first iteration
    while (fabs(x1 - x0) > 0.0001)
    { // iterate until convergence
        x0 = x1;
        x1 = x0 - (s(x0, j_max) - xx) / v(x0, j_max);
    }
    return x1;
}