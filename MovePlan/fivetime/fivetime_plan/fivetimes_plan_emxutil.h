/*
 * File: fivetimes_plan_emxutil.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 22-Nov-2022 10:24:26
 */

#ifndef FIVETIMES_PLAN_EMXUTIL_H
#define FIVETIMES_PLAN_EMXUTIL_H

/* Include Files */
#include "fivetimes_plan_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for fivetimes_plan_emxutil.h
 *
 * [EOF]
 */
