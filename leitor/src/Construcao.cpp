#include "Ils.h"

// Funções que auxiliam a função construção
    // Função que calcula informações para adição de novo nó a subtour já existente
std::vector<InsertionInfo> calcularCustoInsercao(Solution, std::vector<int>&, double**);
Solution startTour(int, double **); // Função para subtour inicial, com 3 nós sendo adicionados
std::vector<int> leftover(std::vector<int>, int); // Função que gera vector com nós restantes
std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo>); // Ordena os custos em ordem crescente
Solution inserirNaSolucao(Solution, InsertionInfo);// Insere nó, com informações de calculaCustoInsercao() ao subtour

// Função construção com finalidade de obter soluções
Solution Construcao(int dimensao, double **distancia)
{
    Solution s = startTour(dimensao, distancia); // função seleciona nós iniciais
    std::vector<int> CL = leftover(s.sequence, dimensao); // guarda os nós faltantes 
    
    // Loop para adição de nós faltantes ao subtour inicial
    while(!CL.empty())
    {
        std::vector<InsertionInfo> custo = calcularCustoInsercao(s, CL, distancia);
        custo = ordemCrescente(custo);
        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custo.size())); // Seleciona um entre os (alpha*|ohmega|) primeiros
        s = inserirNaSolucao(s, custo[selecionado]); // Adiciona nó selecionado a subtour
        // Remove o nó inserido do vector de nós faltantes
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

    // Loop que percorre cada aresta
    for(int a=0; a<(solucao.sequence.size() -1); a++)
    {
        // i e j correspondem aos nós que são interligados pela determinada aresta
        int i = solucao.sequence[a];
        int j = solucao.sequence[a+1];
        for (int b=0; b<lista.size(); b++)
        {
            int k = lista[b]; // percorre elementos da lista de faltantes
            // Calcula custo para inserção de cada nó em lista para a determinada aresta
            custoInsercao[l].custo = distancia[i-1][k-1] + distancia[j-1][k-1] - distancia[i-1][j-1];
            custoInsercao[l].noInserido = k; //insere o nó ao vector das inserções
            custoInsercao[l].arestaRemovida = a; // insere aresta a qual o nó deve ser inserido
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

    /* Considerando-se que o tour percorrerá todos os pontos e que alternando a posição sem modificar a 
    ordem obtemos os mesmos resultados, logo predefinirei um ponto onde o ciclo terminará e começará,
    então adicionarei três nó aleatórios e distintos ao ciclo a ser percorrido*/

    inicial[0] = 1; // Inicia em 1
    for(int i=1; i<4; i++)
    {
        bool repetido = false;
        int a = (2 + rand()%(dimensao - 2)); // seleciona nó aleatório entre 2 e o valor máximo
        for(int j=0; j<i; j++)
        {
            if(a == inicial[j])
            {
                repetido = true; // verifica se o valor é repitido
                i--; // em caso de repetição, a operação é refeita
            }
        }
        if(!repetido) inicial[i] = a; // caso não seja repetido o valor é adicionado ao vector
    }
    inicial[4] = 1; // Finalizando em 1

    for(int a=0; a<4; a++)
    {
        valorInicial += distancia[inicial[a]-1][inicial[a+1]-1]; // Calculando valor do subtour inicial
    }

    s.sequence = inicial;
    s.value = valorInicial;

    return s;
}

std::vector<int> leftover(std::vector<int> sequencia, int dimensao)
{
    std::vector<int> resto(dimensao - (sequencia.size() -1));
    int l=0;

    // Loop por todos os nós exitentes
    for(int i=1; i<=dimensao; i++)
    {
        bool repetido = false;
        for(int j = 0; j<sequencia.size(); j++)
        {
            if(i == sequencia[j]) 
                repetido = true; // Verificando se o nó está no subtour inicial
        }
        if(!repetido)
        {
            resto[l] = i; // Caso valor não esteja no subtour, é adicionado no vector
            l++;
        }
    }

    return resto;
}

std::vector<InsertionInfo> ordemCrescente(std::vector<InsertionInfo> custo)
{
    // Para cada custo, verifica se há a frente algum com menor custo e substiui suas posições em caso positivo
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
    s.sequence.insert(s.sequence.begin()+k.arestaRemovida+1, k.noInserido); //Atualiza o percurso
    s.value += k.custo; // Atualiza valor da solução

    return s;
}
