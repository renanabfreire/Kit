#include "separation.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>

extern vector<vector<int>> MaxBack(double** x, int n){
    vector<double> maxback_val(n-1, 0);
    vector<int> vo(n-1);
    double sum, cut_val, mincut_val;
 
    // valor associado a cada nó recebe o somatório de todas as arestas envolvendo um nó i no subconjunto So e um j em V, para cada j individualmente
    // maxback_val[j] = sum_{i in So} x*_{ij} for all j in V
    sum = 0;
    for(int j=1; j<n; j++) {
        if(x[0][j] > 0) {
            maxback_val[j-1] = x[0][j];
            sum += x[0][j];
        } else {
            maxback_val[j-1] = -x[0][j];
            sum -= x[0][j];
        }
    }

    iota(vo.begin(), vo.end(), 1);
    // valor de corte recebe o somatório de todas as arestas com j fora de So e i em So
    // cut_val = sum_{i in So} sum_{j in V\So} x*_{ij}
    cut_val = sum;

    // valor inicial do mincut deve receber o valor de corte
    mincut_val = cut_val;

    // Resposta inicia com subsequência inicial
    vector<int> usados = {0};
  
    vector<vector<int>> pool_set;
    pool_set.push_back(usados);
    // for (int i=0; i< |V|-|So|; i++)
    while (!vo.empty()) {
        // i deve receber j em V que ainda não esteja em S com maior maxback_val[j]    
        // i deve ser adicionado à solução atual
        auto maxItr = max_element(maxback_val.begin(), maxback_val.end());
        int index = distance(maxback_val.begin(), maxItr);

        usados.push_back(vo[index]);

        vo.erase(vo.begin() + index);
        // valor de corte recebe ele somado a 2 subtraído por 2*maxback_val[i]
        cut_val += 2 - 2*maxback_val[index];

        maxback_val.erase(maxItr);

        // caso cut_val < mincut_val
        if(cut_val < mincut_val){
            // mincut_val = cut_val
            mincut_val = cut_val;
            // S <= Sk
            pool_set.push_back(usados);

            if(cut_val == 0) {
                usados.clear();
                usados.push_back(vo[0]);

                if (maxback_val.empty()) {
                    break;
                }

                sum = 0;
                maxback_val.erase(maxback_val.begin());
                for(size_t j=1; j<vo.size(); j++) {
                    if(x[vo[0]][vo[j]] > 0) {
                        maxback_val[j-1] = x[vo[0]][vo[j]];
                        sum += x[vo[0]][vo[j]];
                    } else {
                        maxback_val[j-1] = -x[vo[0]][vo[j]];
                        sum -= x[vo[0]][vo[j]];
                    }
                }

                vo.erase(vo.begin());

                // valor de corte recebe o somatório de todas as arestas com j fora de So e i em So
                // cut_val = sum_{i in So} sum_{j in V\So} x*_{ij}
                cut_val = sum;
                mincut_val = cut_val;

                continue;
            }
        }

        // for j fora da solução atual
        // maxback_val[j] = maxback_val[j] + x*_{ij}
        for(int i=0; i<vo.size(); i++){
            if(usados.back() < vo[i]){
                if(x[usados.back()][vo[i]] > 0){
                    maxback_val[i] += x[usados.back()][vo[i]];
                } else {
                    maxback_val[i] -= x[usados.back()][vo[i]];
                }
            } else {
                if(x[vo[i]][usados.back()] > 0) {
                    maxback_val[i] += x[vo[i]][usados.back()];
                } else {
                    maxback_val[i] -= x[vo[i]][usados.back()];
                }
            }
        }
    }

    cout << "starting" << endl;
    for(size_t k = 0; k < pool_set.size(); k++) {
        for (size_t i = 0; i < pool_set[k].size() ; i++) {
            cout << pool_set[k][i] << " - ";
        }

        cout << endl;
    }

    return pool_set;
}
