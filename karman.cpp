#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    // 初始化状态量和协方差矩阵
    Vector2d x(0, 0); // 初始位置和速度
    Matrix2d P = Matrix2d::Identity(); // 初始协方差矩阵

    // 定义状态转移矩阵和观测矩阵
    double dt = 1; // 时间间隔
    Matrix2d F;
    F << 1, dt, 0, 1; // 状态转移矩阵
    Matrix<double, 1, 2> H;
    H << 1, 0; // 观测矩阵

    // 定义噪声协方差矩阵
    Matrix2d Q;
    Q << 0.1, 0, 0, 0.1; // 过程噪声协方差矩阵
    Matrix<double, 1, 1> R;
    R << 10; // 测量噪声协方差矩阵

    // 模拟传感器数据
    double measurements[] = {5.1, 4.9, 6.2, 5.8};

    for (int i = 0; i < sizeof(measurements)/sizeof(measurements[0]); i++) {
        // 预测
        x = F * x;
        P = F * P * F.transpose() + Q;

        // 更新
        Matrix<double, 1, 1> y;
        y << measurements[i] - H * x;
        Matrix<double, 1, 1> S = H * P * H.transpose() + R;
        Matrix<double, 2, 1> K = P * H.transpose() * S.inverse();
        x = x + K * y;
        P = (Matrix2d::Identity() - K * H) * P;
    }

    cout << "位置估计: " << x(0) << endl;
    cout << "速度估计: " << x(1) << endl;
    
    return 0;
}