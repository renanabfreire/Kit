#include "Ils.h"

bool bestImprovementSwap(Solution&, Data&);
bool bestImprovement2Opt(Solution&, Data&);
bool bestImprovementOrOpt(Solution&, Data&, int);

void BuscaLocal(Solution &s, Data &d)
{
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(!NL.empty())
    {
        int n = rand() % NL.size();
        switch(NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, d); // Swap
            break;
        case 2:
            improved = bestImprovement2Opt(s, d); // 2-opt
            break;
        case 3:
            improved = bestImprovementOrOpt(s, d, 1); // Reinsertion
            break;
        case 4:
            improved = bestImprovementOrOpt(s, d, 2); // Or-opt-2
            break;
        case 5:
            improved = bestImprovementOrOpt(s, d, 3); // Or-opt-3
            break;
        }

        if(improved)
            NL = {1, 2, 3, 4, 5}; //repetindo processo em caso de melhora
        else
            NL.erase(NL.begin() + n); // eliminando operação que não obteve melhora
    }
}

// Swap
bool bestImprovementSwap(Solution &s, Data &d)
{
    double bestDelta=0;
    int best_i, best_j;
    
    for(int i=1; i<s.sequence.size() - 2; i++)
    {
        int vi = s.sequence[i]; // Percorrendo primeiro nó para troca
        int vi_next = s.sequence[i+1];
        int vi_prev = s.sequence[i-1];
        
        for(int j=i+1; j<s.sequence.size() - 1; j++)
        {
            int vj = s.sequence[j]; // Segundo nó para troca
            int vj_next = s.sequence[j+1];
            int vj_prev = s.sequence[j-1];
            // Calculando variação de custo
            double delta = (-d.getDistance(vi_prev, vi)+d.getDistance(vi_prev, vj))*(s.sequence.size()-i) + (-d.getDistance(vi, vi_next) + d.getDistance(vj, vi_next))*(s.sequence.size()-(i+1))+ (-d.getDistance(vj_prev, vj)+d.getDistance(vj_prev, vi))*(s.sequence.size()-j) + (-d.getDistance(vj, vj_next) + d.getDistance(vi, vj_next))*(s.sequence.size()-(j+1));

            // Para o caso dos vertices pertencerem a uma mesma aresta, a aresta é eliminada 2 vezes, mas deve ser considerada
            if(vi_next == vj)
                delta += 2*d.getDistance(vi, vj)*(s.sequence.size() - (i+1));

            // Atualizando melhores valores
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    // Atualizando a solução para o melhor caso
    if(bestDelta < 0)
    {
        std::swap(s.sequence[best_i], s.sequence[best_j]);
        s.value += bestDelta;
        return true;
    }
    return false;
}

// 2-opt
bool bestImprovement2Opt(Solution &s, Data &d)
{
    int best_a, best_b;
    float bestDelta = 0;

    vector<vector<Subsequence>> SubsequenceMatriz(s.sequence.size(), vector<Subsequence>(s.sequence.size()));
    UpdateAllSubseq(s, SubsequenceMatriz, d);

    for(int a=1; a<s.sequence.size() - 2; a++)
    {
        for(int b=a+2; b<s.sequence.size() -2; b++)
        {
            // Calculando variação do custo
            Subsequence sigma_1 = Concatenate(SubsequenceMatriz[0][a-1], SubsequenceMatriz[b][a], d);
            Subsequence delta = Concatenate(sigma_1, SubsequenceMatriz[b+1][s.sequence.size()-1], d);
            // Atualizando melhores valores
            if(delta.C - s.value < bestDelta)
            {
                bestDelta = delta.C - s.value;
                best_a = a;
                best_b = b;
            }
        }
    }

    // Atualizando a solução
    if(bestDelta < 0)
    {
        int l=0;
    
        // invertendo trecho entre as arestas retiradas
        for(int i=best_a; i<float((best_a+best_b+1)/2); i++)
        {
            std::swap(s.sequence[i], s.sequence[best_b-l]);
            l++;
        }

        s.value += bestDelta;
        return true;
    }

    return false;
}

// Or-opt e Reinsertion
bool bestImprovementOrOpt(Solution &s, Data &d, int numeroDeNos)
{
    double bestDelta = 0;
    int best_a, best_b;
    bool aberturaAntes = false;

    vector<vector<Subsequence>> SubsequenceMatriz(s.sequence.size(), vector<Subsequence>(s.sequence.size()));
    UpdateAllSubseq(s, SubsequenceMatriz, d);

    for(int a=1; a<s.sequence.size() - 2 - numeroDeNos; a++)
    {
        for(int b=a+2+numeroDeNos; b<s.sequence.size() -1; b++)
        {
            // Calculando variação do custo
            Subsequence sigma_1 = Concatenate(SubsequenceMatriz[0][a-1], SubsequenceMatriz[a+numeroDeNos][b], d);
            Subsequence sigma_2 = Concatenate(sigma_1, SubsequenceMatriz[a+numeroDeNos-1][a], d);
            Subsequence delta = Concatenate(sigma_2, SubsequenceMatriz[b+1][s.sequence.size()-1], d);
            // Atualizando melhores valores
            if(delta.C - s.value < bestDelta)
            {
                bestDelta = delta.C - s.value;
                best_a = a;
                best_b = b;
                aberturaAntes = false;
            }
        }

        for(int b=1; b<a-2; b++)
        {
            // Calculando variação do custo
            Subsequence sigma_1 = Concatenate(SubsequenceMatriz[0][b-1], SubsequenceMatriz[a+numeroDeNos-1][a], d);
            Subsequence sigma_2 = Concatenate(sigma_1, SubsequenceMatriz[b][a-1], d);
            Subsequence delta = Concatenate(sigma_2, SubsequenceMatriz[a+numeroDeNos][s.sequence.size()-1], d);
            // Atualizando melhores valores
            if(delta.C - s.value < bestDelta)
            {
                bestDelta = delta.C - s.value;
                best_a = a;
                best_b = b;
                aberturaAntes = true;
            }
        }
    }

    // Atualizando solução
    if(bestDelta < 0)
    {
        std::vector<int> inversao(numeroDeNos);
        int l=0;

        // Isolando bloco
        for(int i=best_a; i<best_a+numeroDeNos; i++)
        {
            inversao[l] = s.sequence[best_a];
            s.sequence.erase(s.sequence.begin()+best_a);
            l++;
        }

        // Reinserindo o bloco de maneira invertida no lugar da aresta aberta
        l=numeroDeNos-1;
        if(aberturaAntes)
            for(int i=0; i<numeroDeNos; i++)
            {
                s.sequence.insert(s.sequence.begin()+best_b+i, inversao[l]);
                l--;
            }
        else
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