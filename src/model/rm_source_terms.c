/*============================================================================
 *   RM_MODEL_C
 *============================================================================*/

/*-----------------------------------------------------------------------------*/
/*! 
 * In this file we defines the source for the models: 
 *                  model = coef*F(t,x)
 !*/

/*------------------------------------------------------------------------------*/

/*=================================================================================*/

/*----------------------------------------------------------------------------
 * C headers
 *----------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>



/*----------------------------------------------------------------------------
 * Local headers
 *----------------------------------------------------------------------------*/
#include "rm_source_terms.h"
#include "../base/rm_math.h"
/*----------------------------------------------------------------------------*/


/* Function second member F(t,x) */
/*!
 * [in] t ------------> time
 * [in] x -------------> space
 * Return the second member of equation */

double Ftx(const double t,
	   const double x)
{
  return 0;
}

/*-------------------------------------------------------------------------------------------*/
/* Initialization model source term for transport equation */
/*!
 * [in]  time       ----------> pointer to time
 * [in]  mesh       ----------> pointer to mesh
 * [out] stm_trans  ----------> pointer to source term of transport equation
 !*/ 

void
Init_source_terms_transport(const rm_time      *time,
			    const rm_mesh_1D   *mesh,
			    rm_source_terms    *stm_trans)
{
  const double h = mesh->dx;
  const double dt = time->dt;
  const double coef = 2*dt*h*stm_trans->coef;

  for (int n = 0; n < time->n; n++) {
    const double tn = time->t_step[n];
    for(int i = 0; i < stm_trans->n_elts; i++) {
      const double xi = mesh->X[i+1];
      stm_trans->Fni[n][i] = coef*Ftx(tn,xi);
    }
  }
}

/*------------------------------------------------------------------------------------------*/
/* Initialization source term for eat equation */
/*!
 * [in]  time       ----------> pointer to time
 * [in]  mesh       ----------> pointer to mesh
 * [out] stm_chal   ----------> pointer to source term of eat equation
 !*/

void
Init_source_terms_chaleur(const rm_time        *time,
			  const rm_mesh_1D     *mesh,
			  rm_source_terms      *stm_chal)
{
  const double dt = time->dt;
  const double h = rm_pow2(mesh->dx);
  const double coef = dt*h*stm_chal->coef;

  for (int n = 0; n < time->n; n++) {
    const double tn = time->t_step[n];
    for(int i = 0; i < stm_chal->n_elts; i++) {
      const double xi = mesh->X[i+1];
      stm_chal->Fni[n][i] = coef*Ftx(tn,xi);
    }
  }
  
}


/*------------------------------------------------------------------------------------------*/
/* Initialization source term for eat equation */
/*!
 * [in]  time       ----------> pointer to time
 * [in]  mesh       ----------> pointer to mesh
 * [out] stm_chal   ----------> pointer to source term of eat equation
 !*/

void
Init_source_terms(const rm_time        *time,
		  const rm_mesh_1D     *mesh,
		  const rm_model_1D    *model,
		  rm_source_terms      *source_terms)
{
  source_terms->coef = 1.;
  source_terms->n_elts = model->n_elts;
  
  source_terms->Fni = malloc((time->n)*sizeof(double*));
  for (int i = 0; i < time->n; i++)
    source_terms->Fni[i] = malloc((model->n_elts)*sizeof(double));

  if (strcmp(model->name,"heat") == 0) {
    Init_source_terms_chaleur(time,
			      mesh,
			      source_terms);
    return;
  }

  if (strcmp(model->name,"transport") == 0) {
    Init_source_terms_transport(time,
				mesh,
				source_terms);
    return;
  }
}

/*------------------------------------------------------------------------------------------*/

/* Free the structure of terms source */
/*!
 * [in]  time           ----------> pointer to time
 * [out] source_terms   ----------> pointer to source term
!*/

void
free_sources_term(const rm_time    *time,
		 rm_source_terms   *source_terms)
{
  for(int i = 0; i < time->n; i++)
    free(source_terms->Fni[i]);
  
  free(source_terms->Fni);
  free(source_terms);
} 

/*-------------------------------------------------------------------------------------------*/
