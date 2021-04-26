#ifndef __RM_MESH_H__
#define __RM_MESH_H__


/*-----------------------------------------------------------------------------*/
/*! 
 * In this file we defines domain 1D 
 !*/

/*------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------
 * C headers
 *------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*=============================================================================================*/


/* Structure representation of mesh */

typedef struct {
  int nx;     /* Number of points on mesh */
  double *X;  /* discretization of interval [Lg, Ld] */
  double dx;  /* space step is constante for begining*/
} rm_mesh_1D;

/*------------------------------------------------------------------------------*/
/* Initialization of mesh */
/*!
 * out mesh      -------> pointer to mesh structure
 * int Nx        -------> number of interval for axes X
 * in domain     -------> pointer to domain structure 
 !*/

void
init_mesh(rm_mesh_1D *mesh,
	  const int   Nx,
	  const double Lx[]);
/*------------------------------------------------------------------------------*/

/* Free Mesh */
/*!
 * out mesh -------> pointer to mesh structure
 !*/
void
free_mesh(rm_mesh_1D *mesh);

/*------------------------------------------------------------------------------*/

/*=============================================================================================*/


#endif /* __RM_MESH_H__ */
