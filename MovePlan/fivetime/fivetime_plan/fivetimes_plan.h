
#ifndef FIVETIMES_PLAN_H
#define FIVETIMES_PLAN_H

/* Include Files */
#include "fivetimes_plan_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>


/* Function Declarations */
 void fivetimes_plan(double ts, double start_x, double start_v,
                           double start_a, double te, double end_x,
                           double end_v, double end_a, emxArray_real_T *x,
                           emxArray_real_T *v, emxArray_real_T *a);

#endif // FIVETIMES_PLAN_H

