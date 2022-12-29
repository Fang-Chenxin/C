#include "fivetimes_plan.h"
#include <math.h>
#include <string.h>


void fivetimes_plan(double ts, double start_x, double start_v, double start_a,
                    double te, double end_x, double end_v, double end_a,
                    emxArray_real_T *x, emxArray_real_T *v, emxArray_real_T *a)/*emxArray_real_T是自定义的类型名，可以存放数组*/
{
  /*定义双精度型，整型，字符型变量*/
  double b_x[36];
  double y[36];
  double C[6];
  double b_start_x[6];
  double b_x_tmp;
  double c3;
  double c4;
  double c5;
  double c_i;
  double c_x_tmp;
  double s;
  double smax;
  double x_tmp;
  double *x_data;
  int b_i;
  int b_tmp;
  int d_x_tmp;
  int i;
  int j;
  int jA;
  int jp1j;
  int k;
  int kAcol;
  int mmj_tmp;
  signed char ipiv[6];
  signed char p[6];
  signed char i1;
  /*为b_x[]数组赋值 1.0   1.0   0.0   0.0   0.0   0.0
                    ts    te   1.0   1.0   0.0   0.0
                   ts^2  te^2  2ts   2te   2.0   2.0
                   ts^3  te^3  3ts^2 3te^2 6ts   6te
                   ts^4  te^4  4ts^3 4te^3 12ts^2 12te^2
                   ts^5  te^5  5ts^4 5te^4 20ts^3 20ts^3*/
  b_x[0] = 1.0;
  b_x[6] = ts;
  x_tmp = ts * ts;
  b_x[12] = x_tmp;
  b_x_tmp = pow(ts, 3.0);
  b_x[18] = b_x_tmp;
  c_x_tmp = pow(ts, 4.0);
  b_x[24] = c_x_tmp;
  b_x[30] = pow(ts, 5.0);
  b_x[1] = 1.0;
  b_x[7] = te;
  smax = te * te;
  b_x[13] = smax;
  s = pow(te, 3.0);
  b_x[19] = s;
  c3 = pow(te, 4.0);
  b_x[25] = c3;
  b_x[31] = pow(te, 5.0);
  b_x[2] = 0.0;
  b_x[8] = 1.0;
  b_x[14] = 2.0 * ts;
  b_x[20] = 3.0 * x_tmp;/*x_tmp=ts^2*/
  b_x[26] = 4.0 * b_x_tmp;/*b_x_tmp=ts^3*/
  b_x[32] = 5.0 * c_x_tmp;/*c_x_tmp=ts^4*/
  b_x[3] = 0.0;
  b_x[9] = 1.0;
  b_x[15] = 2.0 * te;
  b_x[21] = 3.0 * smax;/*smax=te^2*/
  b_x[27] = 4.0 * s;/*s=te^3*/
  b_x[33] = 5.0 * c3;/*c3=te^4*/
  b_x[4] = 0.0;
  b_x[10] = 0.0;
  b_x[16] = 2.0;
  b_x[22] = 6.0 * ts;
  b_x[28] = 12.0 * x_tmp;/*x_tmp=ts^2*/
  b_x[34] = 20.0 * b_x_tmp;/*b_x_tmp=ts^3*/
  b_x[5] = 0.0;
  b_x[11] = 0.0;
  b_x[17] = 2.0;
  b_x[23] = 6.0 * te;
  b_x[29] = 12.0 * smax;/*smax=te^2*/
  b_x[35] = 20.0 * s;/*s=te^3*/
  memset(&y[0], 0, 36U * sizeof(double));/*memset是一个初始化函数，作用是将某一块内存中的全部设置为指定的值。
        void *memset(void *s, int ch, size_t n);
       函数解释：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s；*/
  for (i = 0; i < 6; i++) {
    ipiv[i] = (signed char)(i + 1);/*给字符数组ipiv[i]赋值1 2 3 4 5 6*/
  }
  for (j = 0; j < 5; j++) {
    mmj_tmp = 4 - j;/*mmj_tmp从4到0*/
    b_tmp = j * 7;/*b_tmp从0到28，间隔为7*/
    jp1j = b_tmp + 2;/*jp1j从2到30，间隔为7*/
    jA = 6 - j;/*jA从6到2*/
    kAcol = 0;
    smax = fabs(b_x[b_tmp]);/*fabs()为取绝对值*/
    for (k = 2; k <= jA; k++) {
      s = fabs(b_x[(b_tmp + k) - 1]);
      if (s > smax) {
        kAcol = k - 1;
        smax = s;
      }
    }
    if (b_x[b_tmp + kAcol] != 0.0) {
      if (kAcol != 0) {
        jA = j + kAcol;
        ipiv[j] = (signed char)(jA + 1);
        for (k = 0; k < 6; k++) {
          kAcol = j + k * 6;
          smax = b_x[kAcol];
          d_x_tmp = jA + k * 6;
          b_x[kAcol] =
           b_x[d_x_tmp];
          b_x[d_x_tmp] = smax;
        }
      }
      i = (b_tmp - j) + 6;
      for (b_i = jp1j; b_i <= i; b_i++) {
        b_x[b_i - 1] /= b_x[b_tmp];
      }
    }
    jA = b_tmp;
    for (kAcol = 0; kAcol <= mmj_tmp; kAcol++) {
      smax = b_x[(b_tmp + kAcol * 6) + 6];
      if (smax != 0.0) {
        i = jA + 8;
        jp1j = (jA - j) + 12;
        for (d_x_tmp = i; d_x_tmp <= jp1j; d_x_tmp++) {
          b_x[d_x_tmp - 1] += b_x[((b_tmp + d_x_tmp) - jA) - 7] * -smax;
        }
      }
      jA += 6;
    }
  }
  for (i = 0; i < 6; i++) {
    p[i] = (signed char)(i + 1);
  }
  for (k = 0; k < 5; k++) {
    i1 = ipiv[k];
    if (i1 > k + 1) {
      jA = p[i1 - 1];
      p[i1 - 1] = p[k];
      p[k] = (signed char)jA;
    }
  }
  for (k = 0; k < 6; k++) {
    d_x_tmp = 6 * (p[k] - 1);
    y[k + d_x_tmp] = 1.0;
    for (j = k + 1; j < 7; j++) {
      i = (j + d_x_tmp) - 1;
      if (y[i] != 0.0) {
        jp1j = j + 1;
        for (b_i = jp1j; b_i < 7; b_i++) {
          jA = (b_i + d_x_tmp) - 1;
          y[jA] -= y[i] * b_x[(b_i + 6 * (j - 1)) - 1];
        }
      }
    }
  }
  for (j = 0; j < 6; j++) {
    jA = 6 * j;
    for (k = 5; k >= 0; k--) {
      kAcol = 6 * k;
      i = k + jA;
      smax = y[i];
      if (smax != 0.0) {
        y[i] = smax / b_x[k + kAcol];
        for (b_i = 0; b_i < k; b_i++) {
          d_x_tmp = b_i + jA;
          y[d_x_tmp] -= y[i] * b_x[b_i + kAcol];
        }
      }
    }
  }
  b_start_x[0] = start_x;
  b_start_x[1] = end_x;
  b_start_x[2] = start_v;
  b_start_x[3] = end_v;
  b_start_x[4] = start_a;
  b_start_x[5] = end_a;
  for (i = 0; i < 6; i++) {
    smax = 0.0;
    for (jp1j = 0; jp1j < 6; jp1j++) {
      smax += y[i + 6 * jp1j] * b_start_x[jp1j];
    }
    C[i] = smax;
  }
  smax = C[1];
  s = C[2];
  c3 = C[3];
  c4 = C[4];
  c5 = C[5];
  x->size[0] = 1;
  x->size[1] = 0;
  v->size[0] = 1;
  v->size[1] = 0;
  a->size[0] = 1;
  a->size[1] = 0;
  i = (int)((te + (0.01 - ts)) / 0.01);
  for (b_i = 0; b_i < i; b_i++) {
    c_i = ts + (double)b_i * 0.01;
    jp1j = x->size[1];
    jA = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1]++;
    emxEnsureCapacity_real_T(x, jA);
    x_data = x->data;
    x_tmp = c_i * c_i;
    b_x_tmp = pow(c_i, 3.0);
    c_x_tmp = pow(c_i, 4.0);
    x_data[jp1j] =
        ((((C[0] + smax * c_i) + s * x_tmp) + c3 * b_x_tmp) + c4 * c_x_tmp) +
        c5 * pow(c_i, 5.0);
    jp1j = v->size[1];
    jA = v->size[0] * v->size[1];
    v->size[0] = 1;
    v->size[1]++;
    emxEnsureCapacity_real_T(v, jA);
    x_data = v->data;
    x_data[jp1j] =
        (((smax + 2.0 * s * c_i) + 3.0 * c3 * x_tmp) + 4.0 * c4 * b_x_tmp) +
        5.0 * c5 * c_x_tmp;
    jp1j = a->size[1];
    jA = a->size[0] * a->size[1];
    a->size[0] = 1;
    a->size[1]++;
    emxEnsureCapacity_real_T(a, jA);
    x_data = a->data;
    x_data[jp1j] =
        ((2.0 * s + 6.0 * c3 * c_i) + 12.0 * c4 * x_tmp) + 20.0 * c5 * b_x_tmp;
  }
}

void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel)/*动态扩展内存———— 考虑边界情况，主要获取数据指针变化和分配数据的大
小，原结构体中 emxArray->allocatedSize的数值不足以表示实际的数据大小，（个数）修改了维数和size，引起数据个数变化为newNumel，其中分配内存数据
的额大小emxArray->allocatedSize应大于或等于newNumel ，数据分配的空间也要重新分配，主要实现由于 size 的变化，导致数据指针分配内存的变化和设置
的数据内存量值的变化*/
{
  int i;
  int newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }// 如果原数据个数小于0，则设置为 0
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }// 如果实际新元素个数大于已分配内存数据的个数，则执行相关操作
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;// 实现倍增
      }
    }
    newData = calloc((unsigned int)i, sizeof(double));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(double) * oldNumel);// 原数据拷贝到新数据位置
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }// 释放原数据指针
    emxArray->data = (double *)newData;
    emxArray->allocatedSize = i;// 此时分配的数据内存个数i >= newNumel（实际数据个数）
    emxArray->canFreeData = true;
  }
}

void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxInit_real_T(pEmxArray, numDimensions);
}

void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)/*结构体的初始化（只有一个维数输入）*/
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;//该结构体数据指针赋初值为NULL
  emxArray->numDimensions = numDimensions;//该结构体的维数
  emxArray->size = (int *)malloc(sizeof(int) * numDimensions);//该结构体的大小内存分配
  emxArray->allocatedSize = 0;//该结构体数据的个数
  emxArray->canFreeData = true;//该结构体指针释放标志
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }//该结构体的大小赋初值为0
}

// ND 获取N维的数据 并且有数据的初始化，即包装函数Wrapper（data获取数据，numEl 为数据元素的个数，  此时emx->canFreeData = false;）
emxArray_real_T *emxCreateWrapperND_real_T(double *data, int numDimensions, int *size)/*结构体的初始化（有三个参数的输入：数据、维数和数据尺度）*/
{
  emxArray_real_T *emx;
  int numEl;
  int i;
  emxInit_real_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;// 给对应的数据指针赋值
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  double t0=0,x0=30,v0=30,a0=10,t1=5,x1=60,v1=40,a1=13;/*输入双精度参数*/
  emxArray_real_T *x;
  emxArray_real_T *v;
  emxArray_real_T *a;
  emxInitArray_real_T(&x, 2);
  emxInitArray_real_T(&v, 2);
  emxInitArray_real_T(&a, 2);
  fivetimes_plan(t0, x0, v0, a0, t1, x1, v1, a1, x, v, a);/*调用函数fivetimes_plan()*/
  system("pause");/*稳定输出框*/
  return 0;
}

