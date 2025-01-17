#include "Ils.h"

Solution ILS(int maxIter, int maxIterIls, Data &data)
{
    Solution bestOfAll;
    bestOfAll.value = INFINITY;
    for(int i=0; i<maxIter; i++)
    {
        Solution s = Construcao(data); // Gerando palpites
        Solution best = s;

        int iterIls = 0;

        while (iterIls <= maxIterIls)
        {
            BuscaLocal(s, data); // Melhorando solução
            // Atualizando melhores valores
            if(s.value < best.value)
            {
                best = s;
                iterIls = 0;
            }
            s = Perturbacao(best, data); // Copia da melhor versão levemente modificada
            iterIls++;
        }
        // atualizando a melhor solução
        if(best.value < bestOfAll.value)
            bestOfAll = best;

    }

    return bestOfAll;
}