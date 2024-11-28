#include "Ils.h"

std::vector<InsertionInfo> calcularCustoInsercao(Solution, std::vector<int>&, double**);
Solution startTour(int, double **);
std::vector<int> leftover(std::vector<int>, int);
std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo>);
Solution inserirNaSolucao(Solution, InsertionInfo);

Solution Construcao(int dimensao, double **distancia)
{
    Solution s = startTour(dimensao, distancia); // funcao seleciona nos iniciais
    std::vector<int> CL = leftover(s.sequence, dimensao); // guarda os nos faltantes 
    
    while(!CL.empty())
    {
        std::vector<InsertionInfo> custo = calcularCustoInsercao(s, CL, distancia);
        custo = ordemCrescente(custo);
        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custo.size()));
        s = inserirNaSolucao(s, custo[selecionado]);
        for(int i = 0; i< CL.size(); i++)
            if(CL[i] == custo[selecionado].noInserido)
                CL.erase(CL.begin()+i);

    }

    return s;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution solucao, std::vector<int>& lista, double **distancia)
{
    std::vector<InsertionInfo> custoInsercao((solucao.sequence.size() - 1) * lista.size());
    int l=0;

    for(int a=0; a<(solucao.sequence.size() -1); a++)
    {
        int i = solucao.sequence[a];
        int j = solucao.sequence[a+1];
        for (int b=0; b<lista.size(); b++)
        {
            int k = lista[b];
            custoInsercao[l].custo = distancia[i-1][k-1] + distancia[j-1][k-1] - distancia[i-1][j-1];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    
    return custoInsercao;
}

Solution startTour(int dimensao, double **distancia)
{
    std::vector<int> inicial(5);
    int valorInicial = 0;
    Solution s;

    inicial[0] = 1;
    for(int i=1; i<4; i++)
    {
        bool repetido = false;
        int a = (2 + rand()%(dimensao - 2));
        for(int j=0; j<i; j++)
        {
            if(a == inicial[j])
            {
                repetido = true;
                i--;
            }
        }
        if(!repetido) inicial[i] = a;
    }
    inicial[4] = 1;

    for(int a=0; a<4; a++)
    {
        valorInicial += distancia[inicial[a]-1][inicial[a+1]-1];
    }

    s.sequence = inicial;
    s.value = valorInicial;

    return s;
}

std::vector<int> leftover(std::vector<int> sequencia, int dimensao)
{
    std::vector<int> resto(dimensao - (sequencia.size() -1));
    int l=0;

    for(int i=1; i<=dimensao; i++)
    {
        bool repetido = false;
        for(int j = 0; j<sequencia.size(); j++)
        {
            if(i == sequencia[j]) 
                repetido = true;
        }
        if(!repetido)
        {
            resto[l] = i;
            l++;
        }
    }

    return resto;
}

std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo> custo)
{
    for(int i=0; i < custo.size(); i++)
        for(int j=i; j< custo.size(); j++)
            if(custo[j].custo < custo[i].custo) 
            {
                InsertionInfo a = custo[j];
                custo[j] = custo[i];
                custo[i] = a;
            }

    return custo;
}

Solution inserirNaSolucao(Solution s, InsertionInfo k)
{
    s.sequence.insert(s.sequence.begin()+k.arestaRemovida+1, k.noInserido);
    s.value += k.custo;

    return s;
}
