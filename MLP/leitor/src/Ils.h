#ifndef ILS_H
#define ILS_H

#include "Data.h"
#include "Solution.h"
#include "Subsequence.h"
#include <algorithm>

void UpdateAllSubseq(Solution, vector<vector<Subsequence>>&, Data&);

Solution Construcao(Data&);
void BuscaLocal(Solution&, Data&, vector<vector<Subsequence>>&);
Solution Perturbacao(Solution,Data&, vector<vector<Subsequence>>&);

Solution ILS(int,int,Data&);

#endif //ILS_H