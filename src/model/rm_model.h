#ifndef __RM_MODEL_H__
#define __RM_MODEL_H__


/*--------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the model for the equations: 
 *                   partial_t(U(t,x)) + coefc*partial_x(U(t,x)),
 *                   partial_t(U(t,x)) + coefc*partial_xx(U(t,x))
 !*/
/*--------------------------------------------------------------------------------------*/

/*======================================================================================*/
/*! 
 * C header
 !*/
/*======================================================================================*/

#include <stdio.h>


/*--------------------------------------------------------------------------------------*/

/*! 
 *Loacal headers
 !*/

#include "../time/rm_time.h"
#include "../domain/rm_domain_1D.h"

/*--------------------------------------------------------------------------------------*/



/* Structure representation of model */
typedef struct {
  char *name;        /* Name of model */
  double coefc;      /* The coef of model */
  double **Uh;       /* Solution of model */
  int n_elts;        /* number of unknown elements on the mesh (node) */
} rm_model_1D;

/*--------------------------------------------------------------------------------------*/


/* Initialization model */
/*!
 * out model     -------> pointer to model structure
 * in time       -------> pointer to time structure
 * in mesh       -------> pointer to mesh structure
 !*/

void
Init_model_1D(rm_model_1D         *model,
	      const rm_time       *time,
	      const rm_mesh_1D    *mesh);

/*--------------------------------------------------------------------------------------*/

/* Free model */
void
Free_model_1D(rm_model_1D         *model,
	      const rm_time       *time);

/*--------------------------------------------------------------------------------------*/
#endif /* __RM_MODEL_H__ */
