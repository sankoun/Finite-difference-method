/*==============================================================================================
 *   RM_TIME_C
 *=============================================================================================*/

/*--------------------------------------------------------------------------------------------*/
/*! 
 * In this file we defines the time structure.
 * We have the implicit scheme so no need for CFL
 !*/

/*--------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------
 * C headers
 *---------------------------------------------------------------------------------------------*/
#include <sys/time.h>
#include <time.h>


/*---------------------------------------------------------------------------------------------
 * Local headers
 *---------------------------------------------------------------------------------------------*/

#include "rm_time.h"

/*---------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------*/
/* this function return the time in second */
double now()
{
  struct timeval t;
  double f_t;
  gettimeofday(&t, NULL);
  f_t=t.tv_usec;
  f_t=f_t/1000000.0;
  f_t+=t.tv_sec;
  return f_t;
}

/* Initialization of time structure */
/*!
 * out time     -------> pointer to time structure
 * in T_init    -------> time initialization and time final
 !*/
void
init_time(rm_time        *time,
	  const double    T_init[2])
{
  time->n = 100;
  time->T0 = T_init[0];
  time->Tf = T_init[1];
  time->dt = T_init[1] - T_init[0];
  time->dt /= 100;
  time->t_step = malloc((101) *sizeof(double));

  time->t_step[0] = T_init[0];
  for (int i = 1; i < 101; i++)
    time->t_step[i] = time->t_step[i-1] + time->dt;

  const double err = time->t_step[100] - T_init[1];
  if (abs(err) > 1e-15) {
    printf("*******************************************\n");
    printf("Bad intialization for time \n");
    printf(" %lf %lf %lf \n",time->t_step[100], T_init[1], err);
    printf("*******************************************\n");
    return;
  }
  
}
/*----------------------------------------------------------------------------*/

/* Free Mesh */
void
free_time(rm_time *time)

{
  free(time->t_step);
  free(time);  
}
/*----------------------------------------------------------------------------*/


