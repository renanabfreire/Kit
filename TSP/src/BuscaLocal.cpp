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
            double delta = -d.getDistance(vi_prev, vi) - d.getDistance(vi, vi_next)+d.getDistance(vi_prev, vj) + d.getDistance(vj, vi_next)-d.getDistance(vj_prev, vj) - d.getDistance(vj, vj_next)+d.getDistance(vj_prev, vi) + d.getDistance(vi, vj_next);

            // Para o caso dos vertices pertencerem a uma mesma aresta, a aresta é eliminada 2 vezes, mas deve ser considerada
            if(vi_next == vj)
                delta += 2 * d.getDistance(vi, vj);

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
    double bestDelta = 0;
    int best_a, best_b;

    for(int a=1; a<s.sequence.size() - 2; a++)
    {
        int va = s.sequence[a]; // Percorrendo arestas
        int va_next = s.sequence[a+1];
        
        for(int b=a+2; b<s.sequence.size() -2; b++)
        {
            int vb = s.sequence[b]; // Percorrendo a outra aresta que será retirada
            int vb_next = s.sequence[b+1];
            // Calculando variação do custo
            double delta = -d.getDistance(va, va_next) - d.getDistance(vb, vb_next) + d.getDistance(va, vb) + d.getDistance(va_next, vb_next);
            
            // Atualizando melhores valores
            if(delta < bestDelta)
            {
                bestDelta = delta;
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

// Or-opt e Reinsertion
bool bestImprovementOrOpt(Solution &s, Data &d, int numeroDeNos)
{
    double bestDelta = 0;
    int best_a, best_b;
    bool aberturaAntes = false;

    for(int a=0; a<s.sequence.size() - 2 - numeroDeNos; a++)
    {
        int va1 = s.sequence[a]; // verificando arestas removidas, isolando o bloco de até 3 nós
        int va1_next = s.sequence[a+1];
        int va2 = s.sequence[a+numeroDeNos];
        int va2_next = s.sequence[a+1+numeroDeNos];
        
        for(int b=a+2+numeroDeNos; b<s.sequence.size() -1; b++)
        {
            int vb = s.sequence[b]; // verificando aresta que será aberta para reinserção do bloco isolado
            int vb_next = s.sequence[b+1];
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

            // Atualizando melhores valores
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
                aberturaAntes = false;
            }
        }

        for(int b=1; b<a-1; b++)
        {
            int vb = s.sequence[b]; // verificando aresta que será aberta para reinserção do bloco isolado
            int vb_next = s.sequence[b+1];
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

            // Atualizando melhores valores
            if(delta < bestDelta)
            {
                bestDelta = delta;
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
        for(int i=best_a+1; i<=best_a+numeroDeNos; i++)
        {
            inversao[l] = s.sequence[best_a+1];
            s.sequence.erase(s.sequence.begin()+best_a+1);
            l++;
        }

        // Reinserindo o bloco de maneira invertida no lugar da aresta aberta
        l=numeroDeNos-1;
        if(aberturaAntes)
            for(int i=best_b; i<best_b+numeroDeNos; i++)
            {
                s.sequence.insert(s.sequence.begin()+i+1, inversao[l]);
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
