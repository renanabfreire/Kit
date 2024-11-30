#include "Ils.h"

bool bestImprovementSwap(Solution&, double**);
bool bestImprovement2Opt(Solution&, double**);
bool bestImprovementOrOpt(Solution&, double**, int);

void BuscaLocal(Solution &s, double** distancias)
{
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(!NL.empty())
    {
        int n = 1+rand() % 5;
        switch(NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, distancias);
            break;
        case 2:
            improved = bestImprovement2Opt(s, distancias);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, distancias, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, distancias, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, distancias, 3);
            break;
        }

        if(improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}

bool bestImprovementSwap(Solution &s, double **c)
{
    double bestDelta=0;
    int best_i, best_j;

    for(int i=1; i<s.sequence.size() - 1; i++)
    {
        int vi = s.sequence[i];
        int vi_next = s.sequence[i+1];
        int vi_prev = s.sequence[i-1];
        
        for(int j=i+1; j<s.sequence.size() - 1; j++)
        {
            int vj = s.sequence[j];
            int vj_next = s.sequence[j+1];
            int vj_prev = s.sequence[j-1];
            double delta = -c[vi_prev-1][vi-1] - c[vi-1][vi_next-1] + c[vi_prev-1][vj-1] + c[vj-1][vi_next-1] - c[vj_prev-1][vj-1] - c[vj-1][vj_next-1] + c[vj_prev-1][vi-1] + c[vi-1][vj_next-1];

            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0)
    {
        std::swap(s.sequence[best_i], s.sequence[best_j]);
        s.value += bestDelta;
        return true;
    }

    return false;
}

bool bestImprovement2Opt(Solution &s, double **c)
{
    double bestDelta = 0;
    int best_a, best_b;

    for(int a=1; a<s.sequence.size() - 1; a++)
    {
        int va = s.sequence[a];
        int va_next = s.sequence[a+1];
        
        for(int b=a+2; b<s.sequence.size() -1; b++)
        {
            int vb = s.sequence[b];
            int vb_next = s.sequence[b+1];
            double delta = -c[va-1][va_next-1] - c[vb-1][vb_next-1] + c[va-1][vb-1] + c[va_next-1][vb_next-1];

            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
            }
        }
    }

    if(bestDelta < 0)
    {
        int l=0;
    
        for(int i=best_a+1; i<=float((best_a+best_b)/2); i++)
        {
            std::swap(s.sequence[i], s.sequence[best_b-l]);
            l++;
        }

        s.value += bestDelta;
        return true;
    }

    return false;
}

bool bestImprovementOrOpt(Solution &s, double **c, int numeroDeNos)
{
    double bestDelta = 0;
    int best_a, best_b;

    for(int a=1; a<s.sequence.size() - 1 - numeroDeNos; a++)
    {
        int va1 = s.sequence[a];
        int va1_next = s.sequence[a+1];
        int va2 = s.sequence[a+numeroDeNos];
        int va2_next = s.sequence[a+1+numeroDeNos];
        
        for(int b=a+2+numeroDeNos; b<s.sequence.size() -1; b++)
        {
            int vb = s.sequence[b];
            int vb_next = s.sequence[b+1];
            double delta = -c[va1-1][va1_next-1] - c[va2-1][va2_next-1] + c[va1-1][va2_next-1] - c[vb-1][vb_next-1] + c[vb-1][va2-1] + c[va1_next-1][vb_next-1];

            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
            }
        }

        for(int b=a-2; b>=0; b--)
        {
            int vb = s.sequence[b];
            int vb_next = s.sequence[b+1];
            double delta = -c[va1-1][va1_next-1] - c[va2-1][va2_next-1] + c[va1-1][va2_next-1] - c[vb-1][vb_next-1] + c[vb-1][va2-1] + c[va1_next-1][vb_next-1];

            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
            }
        }
    }

    if(bestDelta < 0)
    {
        std::vector<int> inversao(numeroDeNos);
        int l=0;

        for(int i=best_a+1; i<=best_a+numeroDeNos; i++)
        {
            inversao[l] = s.sequence[best_a+1];
            s.sequence.erase(s.sequence.begin()+best_a+1);
            l++;
        }

        l=numeroDeNos-1;
        for(int i=best_b; i<best_b+numeroDeNos; i++)
        {
            s.sequence.insert(s.sequence.begin()+i+1-numeroDeNos, inversao[l]);
            l--;
        }

        s.value += bestDelta;
        return true;
    }

    return false;
}
