/*=============================================================================================
 *   RM_GRADIENT_C
 *============================================================================================*/


/*----------------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the different types of gradient for solve the linear systeme Ax = b
 !*/
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
/*! 
 *C  headers
 !*/
/*----------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------------------------*/
/*! 
 *Local  headers
 !*/
/*----------------------------------------------------------------------------------------------*/
#include "rm_gradient.h"
#include "rm_operation.h"
#include "../base/rm_math.h"
/*----------------------------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------------------------*/
/* \brief gradient fixe step, x <- x -step*gradient.
 *  Here gradient = Ax - b */
/*!
 * [out]   Vector     x
 * [in]    Vector     b
 * [in]    Matrix     A
 !*/
void
gradientFix(double              x[],
	    const double        b[],
	    const rm_matrix_1D  *A)
{

  const double step = 0.33;
  const int n = A->nrows;
  double *x0 = malloc(n * sizeof(double));
  double *x1 = malloc(n * sizeof(double));
  double *mb = malloc(n * sizeof(double));
  double *gradient = malloc(n * sizeof(double));

  x0 = b; /* initialization */

  /* compute Ax0 - b */
  matrix1D_dot_vector(gradient, x0, A);
  scalVect(-1, b, n, mb);
  sum(gradient, mb, n, gradient);

  int itter = 0;
  bool continu = true;

  /* strart computing */
  while (continu) {
    scalVect(-step, gradient, n, gradient);
    sum(x0, gradient, n, x1);

    /* compute Ax1 - b */
    matrix1D_dot_vector(gradient, x1, A);
    sum(gradient, mb, n, gradient);
    x0 = x1;
    itter ++;

    if ((normL2(gradient, n) < rm_epzero) || (itter > 500000))
      continu = false;
  }
  
  for (int i = 0; i < n; i++) 
    x[i] = x0[i];
    
  free(x1);
  free(mb);
  free(gradient);
}


/*----------------------------------------------------------------------------------------------*/
/* \brief gradient optimal step, x <- x -stepk*gradient.
 *  Here gradient = Ax - b */
/*!
 * [out]   Vector     x
 * [in]    Vector     b
 * [in]    Matrix     A
 !*/
void
gradientOpti(double              x[],
	     const double        b[],
	     const rm_matrix_1D  *A)
{
  double stepk = 0.33;
  const int n = A->nrows;

  double *x0 = malloc(n * sizeof(double));
  double *x1 = malloc(n * sizeof(double));
  double *mb = malloc(n * sizeof(double));
  double *gradient = malloc(n * sizeof(double));
  double *Adk = malloc(n * sizeof(double));

  x0 = b; /* initialization */

  /* compute Ax0 - b */
  matrix1D_dot_vector(gradient, x0, A);
  scalVect(-1, b, n, mb);
  sum(gradient, mb, n, gradient);

  int itter = 0;
  bool continu = true;

  /* strart computing */
  while (continu) {
    scalVect(-stepk, gradient, n, gradient);
    sum(x0, gradient, n, x1);

    /* compute Ax1 - b */
    matrix1D_dot_vector(gradient, x1, A);
    sum(gradient, mb, n, gradient);

    /* compute the step */
    matrix1D_dot_vector(Adk, gradient, A);
    
    stepk = rm_pow2(normL2(gradient, n))/dot_prod(Adk, gradient, n);
    
    x0 = x1;
    itter ++;
   
    if ((normL2(gradient, n) < rm_epzero) || (itter > 2000000))
      continu = false;
  }
  
  
  for (int i = 0; i < n; i++) 
    x[i] = x0[i];
    
  free(x1);
  free(mb);
  free(Adk);
  free(gradient);
  
}


/*----------------------------------------------------------------------------------------------*/
/* \brief conjugate gradient */
/*!
 * [out]   Vector     x
 * [in]    Vector     b
 * [in]    Matrix     A
 !*/
void
gradientConju(double              x[],
	      const double        b[],
	      const rm_matrix_1D  *A)
{

  const int n = A->nrows;

  double *x0 = malloc(n * sizeof(double));
  double *x1 = malloc(n * sizeof(double));

  double *r0 = malloc(n * sizeof(double));
  double *r1 = malloc(n * sizeof(double));

  double *pk = malloc(n * sizeof(double));
  double *Apk = malloc(n * sizeof(double));
  double *alkpk = malloc(n * sizeof(double));
  double *alkApk = malloc(n * sizeof(double));
  double *bkpk = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) { 
    r0[i] = b[i];
    pk[i] = b[i];
  }
  double ak = 1;
  double bk = 1;
  bool continu = true;
  
  while (continu) {
    matrix1D_dot_vector(Apk, pk, A);
    ak = dot_prod(r0, r0, n)/dot_prod(pk, Apk, n);

    scalVect(ak, pk, n, alkpk);
    scalVect(-ak, Apk, n, alkApk);

    /* compute x_{k+1} and r_{k+1}*/
    sum(alkpk, x0, n, x1);
    sum(alkApk, r0, n, r1);
    
    if (normL2(r1, n) < rm_epzero) 
      continu = false;

    bk = dot_prod(r1, r1, n)/dot_prod(r0, r0, n);

    /* compute p_{k + 1} */
    scalVect(bk, pk, n, bkpk);
    sum(bkpk, r1, n, pk);
    
    for (int i = 0; i < n; i++) {
      x0[i] = x1[i];
      r0[i] = r1[i];
    }
  }
 
  for (int i = 0; i < n; i++) 
    x[i] = x0[i];
  
  free(r1);
  free(r0);
  free(pk);
  free(x0);
  free(x1);
  free(Apk);
  free(alkpk);
  free(alkApk);
  free(bkpk);
}

/*----------------------------------------------------------------------------------------------*/
