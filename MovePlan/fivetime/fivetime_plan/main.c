/*
 * File: main.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 22-Nov-2022 12:18:24
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "fivetimes_plan.h"
#include "fivetimes_plan_emxAPI.h"
#include "fivetimes_plan_terminate.h"
#include "fivetimes_plan_types.h"
#include "rt_nonfinite.h"
#include <stdio.h>

/* Function Declarations */
static double argInit_real_T(void);

static void main_fivetimes_plan(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_fivetimes_plan(void)
{
  emxArray_real_T *a01;
//emxArray_real_T *a12;
//emxArray_real_T *a23;
//emxArray_real_T *a;
  emxArray_real_T *v01;
//emxArray_real_T *v12;
//emxArray_real_T *v23;
//emxArray_real_T *v;
  emxArray_real_T *x01;
//emxArray_real_T *x12;
//emxArray_real_T *x23;
//emxArray_real_T *x;
 
  emxInitArray_real_T(&x01, 2);
//emxInitArray_real_T(&x12, 2);
//emxInitArray_real_T(&x23, 2);
//emxInitArray_real_T(&x, 2);
  emxInitArray_real_T(&v01, 2);
//emxInitArray_real_T(&v12, 2);
//emxInitArray_real_T(&v23, 2);
//emxInitArray_real_T(&v, 2);
  emxInitArray_real_T(&a01, 2);
//emxInitArray_real_T(&a12, 2);
//emxInitArray_real_T(&a23, 2);
//emxInitArray_real_T(&a, 2);
  /* Initialize function 'fivetimes_plan' input arguments. */
  double t0=0,x0=30,v0=30,a0=10,t1=5,x1=60,v1=40,a1=13;
  //double t2=13,x2=80,v2=10,a2=13;
  //double t3=20,x3=10,v3=0,a3=23;

  /* Call the entry-point 'fivetimes_plan'. */
  fivetimes_plan(t0, x0, v0, a0, t1, x1, v1, a1, x01, v01, a01);
  //fivetimes_plan(0, x1, v1, a1, t2-t1, x2, v2, a, x12, v12, a12);
  //fivetimes_plan(0, x2, v2, a2, t3-t2, x3, v3, a3, x23, v23, a23);

  emxDestroyArray_real_T(a01);
  //emxDestroyArray_real_T(a12);
  //emxDestroyArray_real_T(a23);
  //emxDestroyArray_real_T(a);
  emxDestroyArray_real_T(v01);
  //emxDestroyArray_real_T(v12);
  //emxDestroyArray_real_T(v23);
  //emxDestroyArray_real_T(v);
  emxDestroyArray_real_T(x01);
  //emxDestroyArray_real_T(x12);
  //emxDestroyArray_real_T(x23);
  //emxDestroyArray_real_T(x);
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_fivetimes_plan();
  /* Terminate the application.
You do not need to do this more than one time. */
  fivetimes_plan_terminate(); 
  system("pause");
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
