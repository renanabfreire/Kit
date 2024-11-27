#include "../include/Ils.h"

std::vector<InsertionInfo> calcularCustoInsercao(Solution,std::vector<int>&);
std::vector<int> startTour(int);
std::vector<int> leftover(std::vector<int>, int);
std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo>);
void inserirNaSolucao(Solution, int);

Solution Construcao(Data conjunto)
{
    Solution s;
    s.sequence = startTour(conjunto.getDimension()); // funcao seleciona nos iniciais
    std::vector<int> CL = leftover(s.sequence, conjunto.getDimension()); // guarda os nos faltantes 
    
    while(!CL.empty())
    {
        std::vector<InsertionInfo> custo = calcularCustoInsercao(s, CL);
        custo = ordemCrescente(custo);
        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custo.size()));
        inserirNaSolucao(s, custo[selecionado].k);
    }

    return s;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution,std::vector<int>&);
std::vector<int> startTour(int);
std::vector<int> leftover(std::vector<int>, int);
std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo>);
void inserirNaSolucao(Solution, int);

