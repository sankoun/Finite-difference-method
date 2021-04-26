#ifndef __RM_BOUNDARY_CONDITIONS_H__
#define __RM_BOUNDARY_CONDITIONS_H__


/*===============================================================================*/
/*!
 * In this file we defines somes boundary conditions
 !*/
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------
 * C headers
 *-------------------------------------------------------------------------------*/

#include <stdio.h>

/*-------------------------------------------------------------------------------
 * Local headers
 *------------------------------------------------------------------------------*/

#include "../domain/rm_mesh_1D.h"
#include "../time/rm_time.h"
#include "rm_model.h"
/*-------------------------------------------------------------------------------*/




/* Structure representation bondary conditions */

typedef enum {
  Neuman,
  Dirichlet
} rm_boundary_condition;
/*--------------------------------------------------------------------------------*/

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
			const double           alpha);

/*---------------------------------------------------------------------------------*/

#endif /* __RM_BOUNDARY_CONDITIONS__H__ */
