
/*---------------------------------------------------------------------------------------------*/
/*! 
 * In this file we uses the sources files for compute some differential equation on the domain. 
 !*/
/*---------------------------------------------------------------------------------------------*/

/*=============================================================================================*/
/*! 
 * Local header
 !*/
/*=============================================================================================*/

#include "src/model/rm_source_terms.h"
#include "src/alger/rm_matrix_1D.h"
#include "src/alger/rm_operation.h"
#include "src/model/rm_boundary_conditions.h"
#include "src/alger/rm_gradient.h"
int
main(int argc,
     char *argv[])

{
  rm_time *time = malloc(sizeof(rm_time));
  rm_mesh_1D *mesh = malloc(sizeof(rm_mesh_1D));
  rm_domain_1D *domain = malloc(sizeof(rm_domain_1D));
  
  rm_model_1D  *model = malloc(sizeof(rm_model_1D));
  rm_matrix_1D *matrix = malloc(sizeof(rm_matrix_1D));
  rm_source_terms *source_terms = malloc(sizeof(rm_source_terms));
  
  
  const int nx = 20002; /* Number of interval */ 
  const double T[2] = {0.,1.}; /* interval time */
  
  domain->L_0 = 0.;
  domain->L_n = 1.;
  
  init_time(time, T);
  mesh = discretize_domain_1D(nx, domain);
  
  model->name = "heat"; /* transport for equation of transport */
  Init_model_1D(model,time, mesh);
  Init_source_terms(time,mesh,model,source_terms);
  
  double *a = malloc(model->n_elts*sizeof(double));
  double *b = malloc(model->n_elts*sizeof(double));
  double *c = malloc(model->n_elts*sizeof(double));
  
  matrix_1D(time,
	    mesh,
	    model,
	    Dirichlet,
	    matrix);

  for (int i = 0; i < model->n_elts; i++)
    a[i] = 1.*i;
  
  matrix1D_dot_vector(b, a, matrix);
 
  
  printf("domain %lf %lf \n", domain->L_0, domain->L_n);
  printf("mesh %d %lf \n", mesh->nx, mesh->dx);
  printf("time %d %lf %lf %lf\n", time->n, time->dt, time->T0, time->Tf);
  printf("model %d %lf %s\n", model->n_elts, model->coefc, model->name);
  printf("source terms %d %lf\n", source_terms->n_elts, source_terms->coef);
  printf("Matrix %d %le %le %le %s\n", matrix->nrows, matrix->diag0, matrix->diag1,matrix->boundary, matrix->name);
  printf("operation %lf %lf %lf \n", dot_prod(a,b,model->n_elts), normL2(a,model->n_elts), normL2(b,model->n_elts));

  gradientConju(c,b,matrix);
  //gradientOpti(c,b,matrix);
  
  for (int i = 0; i < model->n_elts; i++) {
    printf(" %le %le %le\n",a[i],b[i], c[i]);
  }
  
  
  /*for (int i = 0; i < mesh->nx; i++)
    printf("interval %lf %ld \n", mesh->X[i], i);
  
    for (int i = 0; i < time->n +1 ; i++)
    printf("interval time %lf %ld \n", time->t_step[i], i); */

  free_sources_term(time,
		    source_terms);
  Free_model_1D(model,
		time);
  free(domain);
  free(matrix);
  free_mesh(mesh);
  free_time(time);
  free(a);
  free(b);
  free(c);
}
