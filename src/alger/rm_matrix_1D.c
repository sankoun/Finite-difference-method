/*============================================================================
 *   RM_MATRIX_C
 *============================================================================*/


/*-------------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the sparse matrix 1D generate by the discretization of domain
 * with the boundary condition 
 !*/
/*-------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------*/
/*!
 * C headers
 !*/
/*------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------------------*/
/*! 
 *Loacal headers
 !*/
/*------------------------------------------------------------------------------------------*/
#include "rm_matrix_1D.h"
#include "../model/rm_boundary_conditions.h"

/*------------------------------------------------------------------------------------------*/



/* Initialize sparse matrix */
/*!
 * [in]  time      -----------------> pointer to structure time
 * [in]  mesh      -----------------> pointer to structure mesh
 * [in]  model     -----------------> pointer to structure model
 * [out] matrix    -----------------> pointer to structure matrix
 !*/
void
matrix_1D(const rm_time            *time,
	  const rm_mesh_1D         *mesh,
	  const rm_model_1D        *model,
	  const int                boundary,
	  rm_matrix_1D             *matrix)
{
  const double dt = time->dt;
  const double dx = mesh->dx;
  const double coef = model->coefc;

  
  matrix->name = model->name;
  matrix->nrows = model->n_elts;

  matrix->boundary = 0.; /* if Dirichlet */
  if (boundary == Neuman) 
    matrix->boundary = -coef*dt;

  if (strcmp(model->name,"heat") == 0) {
    matrix->diag0 = 2*coef*dt + dx*dx;
    matrix->diag1 = -coef*dt; /* superior and inferior diagonale */
    return;
  }

  if (strcmp(model->name,"transport") == 0) {
    matrix->diag0 = 2*dx;
    matrix->diag1 = coef*dt; /* superior diagonale */
    return;
  }
}
/*------------------------------------------------------------------------------------------*/


/* Return the product matrix vector A.x = y */
/*!
 * [out] vectory ------> corresponding at A.x
 * [in]  vectorx ------> corresponding at vector x
 * [in]  matrix  ------> pointer to structur of sparse matrix
 !*/
void
matrix1D_dot_vector(double              *vectory,
		    const double        *vectorx,
		    const rm_matrix_1D  *matrix)
{
  const int nrows = matrix->nrows;
  const double diag0 = matrix->diag0;
  const double diag1 = matrix->diag1;
  const double boundary = matrix->boundary;

  vectory[0] = (diag0 + boundary)*vectorx[0] + diag1*vectorx[1];
  vectory[nrows-1] = diag1*vectorx[nrows-2] + (diag0 - boundary)*vectorx[nrows-1];

  if (strcmp(matrix->name,"heat") == 0) {
    for (int i = 1; i < nrows - 1; i++) {
      const double cim1 = diag1*vectorx[i-1];
      const double ci = diag0*vectorx[i];
      const double cip1 = diag1*vectorx[i+1];
      
      const double sum = cim1 + ci + cip1;
      vectory[i] = sum;
    }
  }

  if (strcmp(matrix->name,"transport") == 0) {
    vectory[nrows-1] = -diag1*vectorx[nrows-2] + (diag0 - boundary)*vectorx[nrows-1];
    for (int i = 1; i < nrows - 1; i++) {
      const double cim1 = -matrix->diag1*vectorx[i-1];
      const double ci = matrix->diag0*vectorx[i];
      const double cip1 = matrix->diag1*vectorx[i+1];
      
      const double sum = cim1 + ci + cip1;
      vectory[i] = sum;
    }
  }
}
/*------------------------------------------------------------------------------------------*/
