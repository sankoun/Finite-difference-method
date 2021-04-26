
#ifndef __RM_OPERATION_H__
#define __RM_OPERATION_H__



/*-------------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the algebria operations
 !*/
/*-------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------*/

/*! 
 *C  headers
 !*/
/*-------------------------------------------------------------------------------------------*/
#include <stdio.h>



/*------------------------------------------------------------------------------------------*/
/* \brief Product of vector by scalar y = a.x */
/*!
 * [in]  Scalar a
 * [in]  Vector x
 * [in]  vector size   
 * [out] Vector y
 !*/
void
scalVect(const double a,
	 const double x[],
	 const int    size,
	 double       y[]);

/*------------------------------------------------------------------------------------------*/
/* Sum of two vectors z = x + y*/
/*!
 * [in]  Vector x
 * [in]  Vector y
 * [in]  vector size   
 * [out] Vector z
 !*/
void
sum(const double x[],
    const double y[],
    const int    size,
    double       z[]);


/*------------------------------------------------------------------------------------------*/
/* Return the dot product of two vectors a.b */
/*!
 * [in] vector a
 * [in] vector b
 * [in] size of vector n
 !*/
double
dot_prod(const double   a[],
	 const double   b[],
	 const int      size);
/*------------------------------------------------------------------------------------------*/

/* Return the norm L² of vector a */
/*!
 * [in] vector a
 * [in] size n
 !*/
double
normL2(const double   a[],
       const int      size);
/*------------------------------------------------------------------------------------------*/
#endif /* __RM_OPERATION_H__ */
