#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#ifdef __cplusplus
extern "C" {
#endif
  
#define HUNGARIAN_NOT_ASSIGNED 0 
#define HUNGARIAN_ASSIGNED 1

#define HUNGARIAN_MODE_MINIMIZE_COST   0
#define HUNGARIAN_MODE_MAXIMIZE_UTIL 1

typedef struct {
  int num_rows;
  int num_cols;
  int** cost;
  int** assignment;  
} hungarian_problem_t;

/** This method initialize the hungarian_problem structure and init 
 *  the  cost matrices (missing lines or columns are filled with 0).
 *  It returns the size of the quadratic(!) assignment matrix. **/
int hungarian_init(hungarian_problem_t* p, 
		   double** cost_matrix, 
		   int rows, 
		   int cols, 
		   int mode);
  
/** Free the memory allocated by init. **/
void hungarian_free(hungarian_problem_t* p);

/** This method computes the optimal assignment. **/
int hungarian_solve(hungarian_problem_t* p);

/** Print the computed optimal assignment. **/
void hungarian_print_assignment(hungarian_problem_t* p);

/** Print the cost matrix. **/
void hungarian_print_costmatrix(hungarian_problem_t* p);

/** Print cost matrix and assignment matrix. **/
void hungarian_print_status(hungarian_problem_t* p);

#ifdef __cplusplus
}
#endif

#endif



