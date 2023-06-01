#include "fivetimes_plan.h"
#include <math.h>
#include <string.h>


void fivetimes_plan(double ts, double start_x, double start_v, double start_a,
                    double te, double end_x, double end_v, double end_a,
                    emxArray_real_T *x, emxArray_real_T *v, emxArray_real_T *a)
{
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
  b_x[20] = 3.0 * x_tmp;
  b_x[26] = 4.0 * b_x_tmp;
  b_x[32] = 5.0 * c_x_tmp;
  b_x[3] = 0.0;
  b_x[9] = 1.0;
  b_x[15] = 2.0 * te;
  b_x[21] = 3.0 * smax;
  b_x[27] = 4.0 * s;
  b_x[33] = 5.0 * c3;
  b_x[4] = 0.0;
  b_x[10] = 0.0;
  b_x[16] = 2.0;
  b_x[22] = 6.0 * ts;
  b_x[28] = 12.0 * x_tmp;
  b_x[34] = 20.0 * b_x_tmp;
  b_x[5] = 0.0;
  b_x[11] = 0.0;
  b_x[17] = 2.0;
  b_x[23] = 6.0 * te;
  b_x[29] = 12.0 * smax;
  b_x[35] = 20.0 * s;
  memset(&y[0], 0, 36U * sizeof(double));
  for (i = 0; i < 6; i++) {
    ipiv[i] = (signed char)(i + 1);
  }
  for (j = 0; j < 5; j++) {
    mmj_tmp = 4 - j;
    b_tmp = j * 7;
    jp1j = b_tmp + 2;
    jA = 6 - j;
    kAcol = 0;
    smax = fabs(b_x[b_tmp]);
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
          b_x[kAcol] = b_x[d_x_tmp];
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

void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel)
{
  int i;
  int newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = calloc((unsigned int)i, sizeof(double));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(double) * oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }
    emxArray->data = (double *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxInit_real_T(pEmxArray, numDimensions);
}

void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  double t0=0,x0=30,v0=30,a0=10,t1=5,x1=60,v1=40,a1=13;
  emxArray_real_T *x;
  emxArray_real_T *v;
  emxArray_real_T *a;
  emxInitArray_real_T(&x, 2);
  emxInitArray_real_T(&v, 2);
  emxInitArray_real_T(&a, 2);
  fivetimes_plan(t0, x0, v0, a0, t1, x1, v1, a1, x, v, a);
  system("pause");
  return 0;
}
