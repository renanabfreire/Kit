#include "LagrangianRelaxation.h"

// Function that calculates information for adding a new node to an existing subtour
std::vector<InsertionInfo> calcularCustoInsercao(Solution&, std::vector<int>&, Data&);
Solution startTour(Data&); // Function for initial subtour, with 3 nodes being added
std::vector<int> leftover(std::vector<int>, int); // Function that generates vector with remaining nodes
Solution inserirNaSolucao(Solution, InsertionInfo);// Inserts node, with information from calcularCustoInsercao() into the subtour
void BuscaLocal(Solution &, Data &);

// Upper Bound Constructor
double UBC(Data& data){
    Solution s = startTour(data); // function selects initial nodes
    std::vector<int> CL = leftover(s.sequence, data.getDimension()); // stores the missing nodes 
    
    // Loop for adding missing nodes to the initial subtour
    while(!CL.empty())
    {
        std::vector<InsertionInfo> valor = calcularCustoInsercao(s, CL, data);
        s = inserirNaSolucao(s, valor[0]); // Adds selected node to subtour
        // Removes the inserted node from the vector of missing nodes
        for(int i = 0; i< CL.size(); i++)
            if(CL[i] == valor[0].noInserido)
                CL.erase(CL.begin()+i);
    }
    BuscaLocal(s, data);

    return s.cost;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution& solucao, std::vector<int>& lista, Data &data)
{
    std::vector<InsertionInfo> custoInsercao((solucao.sequence.size() - 1) * lista.size());
    int l=0;
    // Loop that goes through each edge
    for(int a=0; a<(solucao.sequence.size() -1); a++)
    {
        // i and j correspond to the nodes that are connected by the given edge
        int i = solucao.sequence[a];
        int j = solucao.sequence[a+1];
        for (auto k : lista) // iterates through the elements of the missing nodes list
        {
            // Calculates cost for inserting each node from the list into the given edge
            custoInsercao[l].custo = data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j);
            custoInsercao[l].noInserido = k; // inserts the node into the vector of insertions
            custoInsercao[l].arestaRemovida = a; // inserts edge where the node should be inserted
            l++;
        }
    }
    return custoInsercao;
}

Solution startTour(Data &data)
{
    std::vector<int> inicial(5);
    int valorInicial = 0;
    Solution s;

    /* Considering that the tour will traverse all points and that by alternating positions without changing the
    order we get the same results, I will preset a point where the cycle will end and begin,
    then I will add three random and distinct nodes to the cycle to be traversed */

    inicial[0] = 1; // Starts at 1
    for(int i=1; i<4; i++)
    {
        bool repetido = false;
        int a = (2 + rand()%(data.getDimension() - 2)); // selects a random node between 2 and the maximum value
        for(int j=0; j<i; j++)
        {
            if(a == inicial[j])
            {
                repetido = true; // checks if the value is repeated
                i--; // in case of repetition, the operation is redone
            }
        }
        if(!repetido) inicial[i] = a; // if not repeated, the value is added to the vector
    }
    inicial[4] = 1; // Ending at 1

    for(int a=0; a<4; a++)
    {
        valorInicial += data.getDistance(inicial[a], inicial[a+1]); // Calculating the value of the initial subtour
    }

    s.sequence = inicial;
    s.cost = valorInicial;

    return s;
}

std::vector<int> leftover(std::vector<int> sequencia, int dimensao)
{
    std::vector<int> resto(dimensao - (sequencia.size() -1));
    int l=0;

    // Loop through all existing nodes
    for(int i=1; i<=dimensao; i++)
    {
        bool repetido = false;
        for(int j = 0; j<sequencia.size(); j++)
        {
            if(i == sequencia[j]) 
                repetido = true; // Checking if the node is in the initial subtour
        }
        if(!repetido)
        {
            resto[l] = i; // If the value is not in the subtour, it is added to the vector
            l++;
        }
    }

    return resto;
}

Solution inserirNaSolucao(Solution s, InsertionInfo k)
{
    s.sequence.insert(s.sequence.begin()+k.arestaRemovida+1, k.noInserido); // Updates the route
    s.cost += k.custo; // Updates the solution value

    return s;
}

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
            NL = {1, 2, 3, 4, 5}; // repeating process in case of improvement
        else
            NL.erase(NL.begin() + n); // eliminating operation that did not yield improvement
    }
}

// Swap
bool bestImprovementSwap(Solution &s, Data &d)
{
    double bestDelta=0;
    int best_i, best_j;
    
    for(int i=1; i<s.sequence.size() - 2; i++)
    {
        int vi = s.sequence[i]; // Iterating first node for swapping
        int vi_next = s.sequence[i+1];
        int vi_prev = s.sequence[i-1];
        
        for(int j=i+1; j<s.sequence.size() - 1; j++)
        {
            int vj = s.sequence[j]; // Second node for swapping
            int vj_next = s.sequence[j+1];
            int vj_prev = s.sequence[j-1];
            // Calculating cost variation
            double delta = -d.getDistance(vi_prev, vi) - d.getDistance(vi, vi_next)+d.getDistance(vi_prev, vj) + d.getDistance(vj, vi_next)-d.getDistance(vj_prev, vj) - d.getDistance(vj, vj_next)+d.getDistance(vj_prev, vi) + d.getDistance(vi, vj_next);

            // For the case where the vertices belong to the same edge, the edge is removed twice, but it should be considered
            if(vi_next == vj)
                delta += 2 * d.getDistance(vi, vj);

            // Updating best values
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    // Updating the solution for the best case
    if(bestDelta < 0)
    {
        std::swap(s.sequence[best_i], s.sequence[best_j]);
        s.cost += bestDelta;
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
        int va = s.sequence[a]; // Iterating through edges
        int va_next = s.sequence[a+1];
        
        for(int b=a+2; b<s.sequence.size() -2; b++)
        {
            int vb = s.sequence[b]; // Iterating through the other edge that will be removed
            int vb_next = s.sequence[b+1];
            // Calculating cost variation
            double delta = -d.getDistance(va, va_next) - d.getDistance(vb, vb_next) + d.getDistance(va, vb) + d.getDistance(va_next, vb_next);
            
            // Updating best values
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
            }
        }
    }

    // Updating the solution
    if(bestDelta < 0)
    {
        int l=0;
    
        // inverting section between removed edges
        for(int i=best_a+1; i<=float((best_a+best_b)/2); i++)
        {
            std::swap(s.sequence[i], s.sequence[best_b-l]);
            l++;
        }

        s.cost += bestDelta;
        return true;
    }

    return false;
}

// Or-opt and Reinsertion
bool bestImprovementOrOpt(Solution &s, Data &d, int numeroDeNos)
{
    double bestDelta = 0;
    int best_a, best_b;
    bool aberturaAntes = false;

    for(int a=0; a<s.sequence.size() - 2 - numeroDeNos; a++)
    {
        int va1 = s.sequence[a]; // checking removed edges, isolating the block of up to 3 nodes
        int va1_next = s.sequence[a+1];
        int va2 = s.sequence[a+numeroDeNos];
        int va2_next = s.sequence[a+1+numeroDeNos];
        
        for(int b=a+2+numeroDeNos; b<s.sequence.size() -1; b++)
        {
            int vb = s.sequence[b]; // checking the edge that will be opened for reinserting the isolated block
            int vb_next = s.sequence[b+1];
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

            // Updating best values
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
            int vb = s.sequence[b]; // checking the edge that will be opened for reinserting the isolated block
            int vb_next = s.sequence[b+1];
            double delta = - d.getDistance(va1, va1_next) - d.getDistance(va2, va2_next) + d.getDistance(va1, va2_next) - d.getDistance(vb, vb_next) + d.getDistance(vb, va2) + d.getDistance(va1_next, vb_next);

            // Updating best values
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_a = a;
                best_b = b;
                aberturaAntes = true;
            }
        }
    }

    // Updating solution
    if(bestDelta < 0)
    {
        std::vector<int> inversao(numeroDeNos);
        int l=0;

        // Isolating block
        for(int i=best_a+1; i<=best_a+numeroDeNos; i++)
        {
            inversao[l] = s.sequence[best_a+1];
            s.sequence.erase(s.sequence.begin()+best_a+1);
            l++;
        }

        // Reinserting the block in inverted order in the place of the opened edge
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

        s.cost += bestDelta;
        return true;
    }

    return false;
}
