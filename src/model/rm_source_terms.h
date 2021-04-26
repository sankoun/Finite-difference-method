#ifndef __RM_SOURCE_TERMS_H__
#define __RM_SOURCE_TERMS_H__


/*-----------------------------------------------------------------------------*/
/*! 
 * In this file we defines the source terms for the models: 
 *                   model = coef*F(t,x)
 !*/

/*------------------------------------------------------------------------------*/

/*========================================================================================*/

/*----------------------------------------------------------------------------
 * C headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>



/*----------------------------------------------------------------------------
 * Local headers
 *----------------------------------------------------------------------------*/

#include "rm_model.h"

/*----------------------------------------------------------------------------*/


/* Structure representation of source terms */

typedef struct {
  int n_elts;        /* number of elements */
  double **Fni;      /* implicit source terms F(t,x) */
  double coef;       /* coef of function second member */
} rm_source_terms;


/*-------------------------------------------------------------------------------------------*/

/* Function second member F(t,x) */
/*!
 * [in] t ------------> time
 * [in] x -------------> space
 * Return the second member of equation */

double Ftx(const double t,
	   const double x);
/*-------------------------------------------------------------------------------------------*/


/* Initialization model source term for transport equation */
/*!
 * [in]  time       ----------> pointer to time
 * [in]  mesh       ----------> pointer to mesh
 * [out] stm_trans  ----------> pointer to source term of transport equation
 !*/ 

void
Init_source_terms_transport(const rm_time         *time,
			    const rm_mesh_1D      *mesh,
			    rm_source_terms       *stm_trans);

/*-------------------------------------------------------------------------------------------*/

/* Initialization source term for eat equation */
/*!
 * [in]  time       ----------> pointer to time
 * [in]  mesh       ----------> pointer to mesh
 * [out] stm_chal   ----------> pointer to source term of eat equation
 !*/

void
Init_source_terms_chaleur(const rm_time       *time,
			  const rm_mesh_1D    *mesh,
			  rm_source_terms     *stm_chal);

/*-------------------------------------------------------------------------------------------*/

/* Initialization source term */
/*!
 * [in]  time           ----------> pointer to time
 * [in]  mesh           ----------> pointer to mesh
 * [in]  model          ----------> pointer to model 
 * [out] source_terms   ----------> pointer to source term
 !*/

void
Init_source_terms(const rm_time       *time,
		  const rm_mesh_1D    *mesh,
		  const rm_model_1D   *model,
		  rm_source_terms     *source_terms);

/*-------------------------------------------------------------------------------------------*/

/* Free the structure of terms source */
/*!
 * [in]  time           ----------> pointer to time
 * [out] source_terms   ----------> pointer to source term
!*/

void
free_sources_term(const rm_time    *time,
		 rm_source_terms   *source_terms);

/*-------------------------------------------------------------------------------------------*/

#endif /* __RM_SOURCE_TERMS_H__ */
