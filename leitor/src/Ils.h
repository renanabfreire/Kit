#ifndef ILS_H
#define ILS_H

#include "Data.h"
#include "Solution.h"
#include "InsertionInfo.h"

Solution Construcao(int dimensao, double **distancia);
void BuscaLocal(Solution*);
Solution Perturbacao(Solution);

Solution ILS(int,int);

#endif //ILS_H