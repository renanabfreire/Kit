#include "Ils.h"

Solution ILS(int maxIter, int maxIterIls, Data &data)
{
    Solution bestOfAll;
    bestOfAll.value = INFINITY;
    for(int i=0; i<maxIter; i++)
    {
        Solution s = Construcao(data);
        Solution best = s;

        int iterIls = 0;

        while (iterIls <= maxIterIls)
        {
            BuscaLocal(s, data);
            if(s.value < best.value)
            {
                best = s;
                iterIls = 0;
            }
            //s = Perturbacao(best, data);
            iterIls++;
        }
        if(best.value < bestOfAll.value)
            bestOfAll = best;

        cout << bestOfAll.value << endl;
    }

    return bestOfAll;
}