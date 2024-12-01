#include "Ils.h"

bool bestImprovementSwap(Solution&, Data&);
bool bestImprovement2Opt(Solution&, Data&);
bool bestImprovementOrOpt(Solution&, Data&, int);

void BuscaLocal(Solution &s, Data &d)
{
    std::vector<int> NL = {1, 2};
    bool improved = false;

    while(!NL.empty())
    {
        int n = rand() % NL.size();
        switch(NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, d);
            break;
        case 2:
            improved = bestImprovement2Opt(s, d);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, d, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, d, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, d, 3);
            break;
        }

        if(improved)
            NL = {1, 2};
        else
            NL.erase(NL.begin() + n);
    }
}

bool bestImprovementSwap(Solution &s, Data &d)
{
    double bestDelta=0;
    int best_i, best_j;
    
    for(int i=1; i<s.sequence.size() - 2; i++)
    {
        int vi = s.sequence[i];
        int vi_next = s.sequence[i+1];
        int vi_prev = s.sequence[i-1];
        
        for(int j=i+1; j<s.sequence.size() - 1; j++)
        {
            int vj = s.sequence[j];
            int vj_next = s.sequence[j+1];
            int vj_prev = s.sequence[j-1];
            double delta = -d.getDistance(vi_prev, vi) - d.getDistance(vi, vi_next)+d.getDistance(vi_prev, vj) + d.getDistance(vj, vi_next)-d.getDistance(vj_prev, vj) - d.getDistance(vj, vj_next)+d.getDistance(vj_prev, vi) + d.getDistance(vi, vj_next);

            if(vi_next = vj)
            {
                delta += 2 * d.getDistance(vi, vj);
            }

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

bool bestImprovement2Opt(Solution &s, Data &d)
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
            double delta = -d.getDistance(va, va_next) - d.getDistance(vb, vb_next) + d.getDistance(va, vb) + d.getDistance(va_next, vb_next);

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

bool bestImprovementOrOpt(Solution &s, Data &d, int numeroDeNos)
{
    double bestDelta = 0;
    int best_a, best_b;

    for(int a=1; a<s.sequence.size() - 2 - numeroDeNos; a++)
    {
        int va1 = s.sequence[a];
        int va1_next = s.sequence[a+1];
        int va2 = s.sequence[a+numeroDeNos];
        int va2_next = s.sequence[a+1+numeroDeNos];
        
        for(int b=a+2+numeroDeNos; b<s.sequence.size() -1; b++)
        {
            int vb = s.sequence[b];
            int vb_next = s.sequence[b+1];
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

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
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

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
