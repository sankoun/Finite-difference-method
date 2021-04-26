/*============================================================================
 *   RM_MESH_1D_C
 *============================================================================*/

/*-----------------------------------------------------------------------------*/
/*! 
 *       In this file we defines domain 1D 
 !*/

/*------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------
 * Local headers
 *-------------------------------------------------------------------------------*/

#include "rm_mesh_1D.h"

/*----------------------------------------------------------------------------*/
/* Initialization of mesh */
/*!
 * out mesh      -------> pointer to mesh structure
 * int Nx        -------> number of interval for axes X
 * in domain     -------> pointer to domain structure 
 !*/

void
init_mesh(rm_mesh_1D  *mesh,
	  const int   Nx,
	  const double Lx[])
{
  /* init mesh */
  mesh->nx = Nx + 1;
  mesh->dx = (Lx[1]-Lx[0])/Nx;
  mesh->X = malloc((mesh->nx) *sizeof(double));
  mesh->X[0] = Lx[0];

  for (int i = 1; i < mesh->nx; i++)
    mesh->X[i] = mesh->X[i-1] + mesh->dx;

  const double err = mesh->X[Nx] - Lx[1];
  if (abs(err) > 1e-15) {
    printf("*******************************************\n");
    printf("Bad intialization of mesh_1D \n");
    printf("*******************************************\n");
    return;
  } 
}
/*----------------------------------------------------------------------------*/

/* Free Mesh */
/*!
 * out mesh -------> pointer to mesh structure
 !*/

void
free_mesh(rm_mesh_1D *mesh)

{
  free(mesh->X);
  free(mesh);  
}
/*----------------------------------------------------------------------------*/


