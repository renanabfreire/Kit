#include "Ils.h"

Solution ILS(int maxIter, int maxIterIls, Data &data)
{
    Solution bestOfAll;
    bestOfAll.value = INFINITY;
    vector<vector<Subsequence>> SubsequenceMatriz(data.getDimension()+1, vector<Subsequence>(data.getDimension()+1));
        
    for(int i=0; i<maxIter; i++)
    {
        Solution s = Construcao(data); // Gerando palpites
        Solution best = s;

        //Atualizando subsequências para a solução gerada
        UpdateAllSubseq(s, SubsequenceMatriz, data);

        int iterIls = 0;

        while (iterIls <= maxIterIls)
        {
            BuscaLocal(s, data, SubsequenceMatriz); // Melhorando solução
            // Atualizando melhores valores
            if(s.value < best.value)
            {
                best = s;
                iterIls = 0;
            }
            UpdateAllSubseq(best, SubsequenceMatriz, data); // Atualizando subsequências da melhor versão
            s = Perturbacao(best, data, SubsequenceMatriz); // Copia da melhor versão levemente modificada

            iterIls++;
        }
        // atualizando a melhor solução
        if(best.value < bestOfAll.value)
            bestOfAll = best;

    }

    return bestOfAll;
}