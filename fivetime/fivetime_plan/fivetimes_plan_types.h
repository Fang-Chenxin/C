/*
 * File: fivetimes_plan_types.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 22-Nov-2022 10:24:26
 */

#ifndef FIVETIMES_PLAN_TYPES_H
#define FIVETIMES_PLAN_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#endif
/*
 * File trailer for fivetimes_plan_types.h
 *
 * [EOF]
 */
