#include "Ils.h"

std::vector<InsertionInfo> calcularCustoInsercao(Solution,std::vector<int>&,Data);
Solution startTour(Data);
std::vector<int> leftover(std::vector<int>, int);
std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo>);
Solution inserirNaSolucao(Solution, InsertionInfo);

Solution Construcao(Data conjunto)
{
    Solution s = startTour(conjunto); // funcao seleciona nos iniciais
    std::vector<int> CL = leftover(s.sequence, conjunto.getDimension()); // guarda os nos faltantes 
    
    while(!CL.empty())
    {
        std::vector<InsertionInfo> custo = calcularCustoInsercao(s, CL, conjunto);
        custo = ordemCrescente(custo);
        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custo.size()));
        s = inserirNaSolucao(s, custo[selecionado]);
    }

    return s;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution solucao, std::vector<int>& lista, Data banco)
{
    std::vector<InsertionInfo> custoInsercao((solucao.sequence.size() - 1) * lista.size());
    int l = 0;
    for(int a=0; a<solucao.sequence.size() -1; a++)
    {
        int i = solucao.sequence[a];
        int j = solucao.sequence[a+1];
        for (auto &k : lista)
        {
            custoInsercao[l].custo = banco.getDistance(i, k) + banco.getDistance(j, k) - banco.getDistance(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}

Solution startTour(Data d)
{
    std::vector<int> inicial(5);
    int valorInicial = 0;
    Solution s;

    inicial.push_back(1);
    for(int i; i<3; i++)
    {
        bool repetido = false;
        int a = (2 + rand()%(d.getDimension() - 2));
        for(int j; j<inicial.size(); j++)
        {
            if(a == inicial[j])
            {
                repetido = true;
                i--;
            }
        }
        if(!repetido) inicial.push_back(a);
    }
    inicial.push_back(1);

    for(int a=0; a<inicial.size() - 1; a++)
    {
        valorInicial += d.getDistance(inicial[a], inicial[a+1]);
    }

    s.sequence = inicial;
    s.value = valorInicial;

    return s;
}

std::vector<int> leftover(std::vector<int> sequencia, int dimensao)
{
    std::vector<int> resto(dimensao - 4);

    for(int i=1; i<=dimensao; i++)
    {
        bool repetido = false;
        for(int j = 0; j<sequencia.size(); j++)
        {
            if(i == sequencia[j]) repetido = true;
        }
        if(!repetido) resto.push_back(i);
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
