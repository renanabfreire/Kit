#ifndef ILS_H
#define ILS_H

#include "Data.h"
#include "Solution.h"
#include "InsertionInfo.h"

Solution Construcao(int, double **);
void BuscaLocal(Solution&,double**);
Solution Perturbacao(Solution, double**);

Solution ILS(int,int);

#endif //ILS_H