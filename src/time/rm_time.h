#ifndef __RM_TIME_H__
#define __RM_TIME_H__


/*---------------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the time structure  
 !*/

/*---------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
/*=============================================================================================*/

/*---------------------------------------------------------------------------------------------*/

/* Structure representation of time */
typedef struct {
  double Tf;       /* Final time */
  double T0;       /* Initial time */
  int n;           /* Number of itérations */
  double *t_step;  /* discretization of interval time [T0, Tf] */
  double dt;       /* Time step is constante for begining */
  
} rm_time;

/*---------------------------------------------------------------------------------------------*/
/* this function return the time in second */
double now();

/*---------------------------------------------------------------------------------------------*/

/* Initialization of time structure */
/*!
 * out time      -------> pointer to time structure
 * in T_init     -------> time initialization and time final
 !*/
void
init_time(rm_time        *time,
	  const double    T_init[2]);

/* Free Mesh */
void
free_time(rm_time *time);

/*---------------------------------------------------------------------------------------------*/
/*=============================================================================================*/


#endif /* __RM_TIME_H__ */
