/*==============================================================================
 *   RM_BOUNDARY_CONDITIONS_C
 *==============================================================================*/

/*------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the boundary conditions
 *
 !*/

/*------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
 * Local headers
 *------------------------------------------------------------------------------*/

#include "rm_boundary_conditions.h"

/*------------------------------------------------------------------------------*/

/*!
 * This functio return the boundary contions 
 *
 * [in] time      -----------------> pointer to structure time
 * [in] mesh      -----------------> pointer to structure mesh
 * [in] model     -----------------> pointer to structure model
 * [In] boundary  -----------------> types of boundary conditions
 * [In] alpha     -----------------> conditions at the left
 !*/ 

double
boundary_condition_left(const rm_time         *time,
			const rm_mesh_1D      *mesh,
			const rm_model_1D     *model,
			const int              boundary,
			const double           alpha)
{
  if (boundary == Neuman){
    const double bord =  model->coefc*mesh->dx*time->dt;
    return alpha*bord;
  }
  
  const double bord =  model->coefc*time->dt;
  return alpha*bord;
}
/*------------------------------------------------------------------------------*/



