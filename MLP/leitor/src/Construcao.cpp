#include "Ils.h"

// Funções que auxiliam a função construção
    // Função que calcula informações para adição de novo nó a subtour já existente

void OrdenaCL(vector<int>&, Data&);
float CalculaCusto(Solution s, Data&);

// Função construção com finalidade de obter soluções
Solution Construcao(Data &data)
{
    Solution s;
    s.sequence = {1};
    std::vector<int> CL(data.getDimension() - 1); // guarda os nós faltantes
    for(int i=0; i < data.getDimension()-1; i++)
    {
        CL[i] = i+2;
    } 

    // Loop para adição de nós faltantes ao subtour inicial
    while(!CL.empty())
    {
        // Ordenando valores dos Custos de Inserção
        OrdenaCL(CL, data);
        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * CL.size())); // Seleciona um entre os (alpha*|ohmega|) primeiros
        s.sequence.push_back(CL[selecionado]); // Adiciona nó selecionado a subtour
        // Remove o nó inserido do vector de nós faltantes
        CL.erase(CL.begin()+selecionado);
    }
    s.sequence.push_back(1);
    s.value = CalculaCusto(s, data);

    return s;
}

void OrdenaCL(vector<int> &A, Data &c)
{
    int pivo;
    for(int i=1; i<A.size(); i++)
    {
        pivo = A[i];
        int j = i-1;
        while (j>=0 && c.getDistance(A[j], 1)>c.getDistance(pivo, 1))
        {
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = pivo;
    }
}

float CalculaCusto(Solution s, Data &c)
{
    int valor = 0;
    float Latency = 0;
    
    for (int i=1; i<s.sequence.size(); i++)
    {
        Latency += c.getDistance(s.sequence[i], s.sequence[i-1]);
        valor += Latency;
    }

    return valor;
}
