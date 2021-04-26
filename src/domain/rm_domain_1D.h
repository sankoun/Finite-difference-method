#ifndef __RM_DOMAIN_1D_H__
#define __RM_DOMAIN_1D_H__


/*-----------------------------------------------------------------------------*/
/*! 
 * In this file we defines domain 1D 
 !*/

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
 /*!
  * Local headers
  !*/
/*------------------------------------------------------------------------------*/

#include "rm_mesh_1D.h"

/*=============================================================================*/



/* Structure representation of 1D domain [L_0, L_n] */

typedef struct {
  float L_0;
  float L_n;
} rm_domain_1D;

/*----------------------------------------------------------------------------*/
/* Discrétization of domain */
/*!
 * in domain -------> pointer to domain structure
 * out mesh  -------> pointer to mesh structure
 * in Nx     -------> number of intervals for axe X
 !*/

rm_mesh_1D *
discretize_domain_1D(const int  Nx,
		     const rm_domain_1D *domain);

  
/*----------------------------------------------------------------------------*/

#endif /* __RM_DOMAIN_1D_H__ */
