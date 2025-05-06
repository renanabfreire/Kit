#include "separation.h"

int maxInsertion(vector<double>, double**, vector<int>, vector<int>);

extern vector<vector<int>> MaxBack(double** x, int n){
    vector<double> maxback_val(n, 0);
    vector<int> vo(n-1);
    double sum, cut_val, mincut_val;

    // valor associado a cada nó recebe o somatório de todas as arestas envolvendo um nó i no subconjunto So e um j em V, para cada j individualmente
    // maxback_val[j] = sum_{i in So} x*_{ij} for all j in V
    
    for(int j=1; j<n; j++)
        maxback_val[j] = x[0][j];

    for(int i=0; i < n-1; i++){
        vo[i] = i+1;
    }

    // valor de corte recebe o somatório de todas as arestas com j fora de So e i em So
    // cut_val = sum_{i in So} sum_{j in V\So} x*_{ij}
    sum = 0;
    for(int j=1; j<n; j++){
        sum += x[0][j];
    }
    cut_val = sum;

    // valor inicial do mincut deve receber o valor de corte
    mincut_val = cut_val;

    // Resposta inicia com subsequência inicial
    vector<int> usados = {0};
    // for (int i=0; i< |V|-|So|; i++)
    for (int k=0; k<vo.size(); k++){
        // i deve receber j em V que ainda não esteja em S, a maximizar maxback_val[j]    
        // i deve ser adicionado à solução atual
        int u = maxInsertion(maxback_val, x, vo, usados);

        // for j fora da solução atual
            // maxback_val[j] = maxback_val[j] + x*_{ij}
        for (int i=0; i<usados.size(); i++)
            for(int j=0; j<vo.size(); j++){
                if(usados[i] < vo[j])
                    maxback_val[vo[j]] += x[usados[i]][vo[j]];
            }

        // valor de corte recebe ele somado a 2 subtraído por 2*maxback_val[i]
        cut_val += 2 - 2*maxback_val[vo[u]];

        // caso cut_val < mincut_val
        if(cut_val < mincut_val){
            // mincut_val = cut_val
            mincut_val = cut_val;
            // S = Sk
            usados.push_back(vo[u]);
            vo.erase(vo.begin() + u);
        }
    }

    return {usados, vo};
}

int maxInsertion(vector<double> M, double** x, vector<int> V, vector<int> S){
    double u, r, max=0;
    
    for(int i=0; i<V.size(); i++){
        double sum = 0;

        for(int j=0; j<S.size(); j++){
            if(S[j] < V[i])
                sum += x[S[j]][V[i]];
        }
        
        if(sum > max){
            u = i;
            max = sum;
        }
    }

    return u;
}