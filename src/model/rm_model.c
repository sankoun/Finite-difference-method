/*============================================================================
 *   RM_MODEL_C
 *============================================================================*/

/*-----------------------------------------------------------------------------*/
/*! 
 * In this file we defines the model for the equations: 
 *                   partial_t(U(t,x)) + coefc*partial_x(U(t,x)),
 *                   partial_t(U(t,x)) + coefc*partial_xx(U(t,x))
 !*/
/*------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Local headers
 *----------------------------------------------------------------------------*/

#include "rm_model.h"

/*----------------------------------------------------------------------------*/

		  
/*----------------------------------------------------------------------------*/

/* Initialization model */
/*!
 * out model     -------> pointer to model structure
 * in time       -------> pointer to time structure
 * in mesh       -------> pointer to mesh structure
 !*/

void
Init_model_1D(rm_model_1D           *model,
	      const rm_time         *time,
	      const rm_mesh_1D      *mesh)
{
  model->coefc = 1.;
  model->n_elts = mesh->nx - 2; /* we know the boundary conditions */

  model->Uh = malloc((time->n)*sizeof(double*));

  for(int i = 0; i < time->n; i++)
    model->Uh[i] = malloc((model->n_elts)*sizeof(double));

  for(int i = 0; i < time->n; i++) {
    for(int j = 0; j < model->n_elts; j++) {
      model->Uh[i][j] = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/

/* Free model */
void
Free_model_1D(rm_model_1D         *model,
	      const rm_time       *time)
{
  for(int i = 0; i < time->n; i++)
    free(model->Uh[i]);

  free(model->Uh);
  free(model);
} 
  
  
/*----------------------------------------------------------------------------*/

