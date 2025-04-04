#include "BnC.h"

std::vector<int> Max_Back(Data& data,std::vector<int> so, std::vector<vector<double>> x){
    std::vector<double> maxback_val(data.getDimension(), 0);
    std::vector<int> vo(data.getDimension());
    std::vector<int> usados = so;
    double sum, cut_val, mincut_val;

    sort(usados.front(), usados.back());
    for (int i=0; i<data.getDimension(); i++)
        vo[i] = i+1;

    for(int i=so.size()-1; i>=0; i--){
        vo.erase(vo.begin() + usados[i]-1);       
    }

    // valor associado a cada nó recebe o somatório de todas as arestas envolvendo um nó i no subconjunto So e um j em V, para cada j individualmente
    // maxback_val[j] = sum_{i in So} x*_{ij} for all j in V
    for(int j=0; j<data.getDimension(); j++){
        sum = 0;

        for(int i=0; i<so.size(); i++){
            sum += x[i][j];
        }

        maxback_val[j] = sum;
    }

    // valor de corte recebe o somatório de todas as arestas com j fora de So e i em So
    // cut_val = sum_{i in So} sum_{j in V\So} x*_{ij}
    sum = 0;
    for (int i=0; i<so.size(); i++){
        int a = so[i];
        for(int j=0; j<vo.size(); j++){
            int b = vo[j];
            sum += x[a][b];
        }
    }
    cut_val = sum;

    // valor inicial do mincut deve receber o valor de corte
    mincut_val = cut_val

    // Resposta inicia com subsequência inicial
    // S = So

    // for (int i=0; i< |V|-|So|; i++)
        // i deve receber j em V que ainda não esteja em S, a maximizar maxback_val[j]
        
        // i deve ser adicionado à solução atual

        // valor de corte recebe ele somado a 2 subtraído por 2*maxback_val[i]

        // for j fora da solução atual
            // maxback_val[j] = maxback_val[j] + x*_{ij}

        // caso cut_val < mincut_val
            // mincut_val = cut_val
            // S = Sk

    // retorna min_cut, S e Vertices faltantes
}