
#ifndef FIVETIMES_PLAN_H
#define FIVETIMES_PLAN_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
  struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif
typedef emxArray_real_T emxArray_real_T;/*定义结构体数组类型--变长度数组对应的结构体*/

/* Function Declarations */
 void fivetimes_plan(double ts, double start_x, double start_v,
                           double start_a, double te, double end_x,
                           double end_v, double end_a, emxArray_real_T *x,
                           emxArray_real_T *v, emxArray_real_T *a);

/* Type Definitions */
 /* struct_emxArray_real_T */



/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

extern void fivetimes_plan_terminate(void);

extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_real_T *

emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif // FIVETIMES_PLAN_H