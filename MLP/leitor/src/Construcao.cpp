#include "Ils.h"

// Funções que auxiliam a função construção
float CalculaCusto(Solution &s, Data&);

// Função construção com finalidade de obter soluções
Solution Construcao(Data &data)
{
    Solution s;
    s.sequence = {1}; // Inicia sequência com valor 1
    std::vector<int> CL(data.getDimension() - 1); // guarda os nós faltantes
    for(int i=0; i < data.getDimension()-1; i++)
    {
        CL[i] = i+2;
    } 
    int last = 1;

    // Loop para adição de nós faltantes ao subtour inicial
    while(!CL.empty())
    {
        // Ordenando valores dos Custos em relação a 1
        sort(CL.begin(), CL.end(), [&](int a, int b) {return data.getDistance(a, last) < data.getDistance(b, last);});
        double alpha = (double)rand()*0.25/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * CL.size())); // Seleciona um entre os (alpha*|ohmega|) primeiros
        s.sequence.push_back(CL[selecionado]); // Adiciona nó selecionado a subtour
        last = CL[selecionado];
        // Remove o nó inserido do vector de nós faltantes
        CL.erase(CL.begin()+selecionado);
    }
    s.sequence.push_back(1); // finaliza sequência com valor 1
    s.value = CalculaCusto(s, data); // Atualiza o custo da solução

    return s;
}

// Calcula custo de uma solução
float CalculaCusto(Solution &s, Data &c)
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
