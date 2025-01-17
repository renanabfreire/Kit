#ifndef ILS_H
#define ILS_H

#include "Data.h"
#include "Solution.h"
#include "InsertionInfo.h"
#include "Subsequence.h"
#include <algorithm>

void UpdateAllSubseq(Solution, vector<vector<Subsequence>>&, Data&);

Solution Construcao(Data&);
void BuscaLocal(Solution&, Data&);
Solution Perturbacao(Solution,Data&);

Solution ILS(int,int,Data&);

#endif //ILS_H