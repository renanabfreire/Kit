#include "separation.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <iomanip>
#include <limits>
#include <vector>

int maxback(vector<vector<double>>, vector<int>&, vector<int>&, int, int, double&);
void shrink(vector<vector<double>>&, vector<int>&, int);

extern vector<vector<int>> MinCut(double **x, int n) {
  // cout << "Entrando" << endl;
  double cut_val, min_cut;
  min_cut = numeric_limits<double>::max();
  vector<int> solution;
  vector<int> cut(n-1);
  int new_cut;
  vector<int> main_cut;
  vector<vector<int>> vecMainCut(n, vector<int>(n));
  vector<vector<int>> pool_cut;

  vector<vector<double>> x_cur(n, vector<double>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      x_cur[i][j] = x[i][j];
    }
  }

  // solution = {0};
  // iota(cut.begin(),cut.end(), 1);
  // cout << "não maxbackou" << endl;
  min_cut = 2;
  // cout << "Menti" << endl;
  // main_cut.push_back(maxback(x, solution, cut, n, 1, min_cut));
  // cout << cut[0] << endl;
  // cout << main_cut.back() << endl;

  for (int i = 0; i < n; i++) {
      solution = {0};
      cut = vector<int>(n-1);
      iota(cut.begin(), cut.end(), 1);
      new_cut = maxback(x_cur, solution, cut, n, 1 + i, cut_val);
      main_cut.push_back(new_cut);
      // vecMainCut[0].push_back(new_cut);
      // cout << main_cut.back() << endl;
      // cout << "iterando" << endl;
      // for (size_t k = 0; k < cut.size(); k++) {
      //     cout << cut[k] << " - ";
      // }
      // cout << endl;

      if (cut_val < min_cut && i > 0) {
          min_cut = cut_val;

          pool_cut.push_back(main_cut);
          main_cut.clear();
          // pool_cut.push_back(vecMainCut[0]);
          // vecMainCut[0].clear();
          // cout << cut.size() << endl;
          // cout << cut_val << endl;
      }

      // cout << "não shrinkei" << endl;
      shrink(x_cur, solution, new_cut);
      // cout << "menti" << endl;
  }

  // cout << "lascou" << endl;
  // cout << main_cut.size() << " - " << set.size() << " - " << setprecision(18) << min_cut << endl;
  // for (size_t i = 0; i < main_cut.size(); i++) {
      // cout << main_cut[i] << " - ";
  // }
  // cout << endl;

  for(size_t j = 0; j < pool_cut.size(); j++) {
      for(size_t k = 0; k < pool_cut[j].size(); k++) {
          cout << pool_cut[j][k] << " - ";
      }
      cout << endl;
  }
  
  // if (pool_cut.size() < 1){
  //     // cout << "aa" << endl;
  //    return {};      
  // }
  // cout << "oia" << endl;
  return pool_cut;
}


int maxback(vector<vector<double>> x, vector<int>& usados, vector<int>& vo, int n, int stop, double &cut){
    vector<double> maxback_val(n-1, 0);
    double sum, cut_val;
 
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

    // valor de corte recebe o somatório de todas as arestas com j fora de So e i em So
    // cut_val = sum_{i in So} sum_{j in V\So} x*_{ij}
    cut_val = sum;

    // for (int i=0; i< |V|-|So|; i++)
    while (vo.size() > stop) {
        // i deve receber j em V que ainda não esteja em S com maior maxback_val[j]    
        // i deve ser adicionado à solução atual
        auto maxItr = max_element(maxback_val.begin(), maxback_val.end());
        int index = distance(maxback_val.begin(), maxItr);

        if (maxback_val[index] == 0) break;

        usados.push_back(vo[index]);

        vo.erase(vo.begin() + index);
        // valor de corte recebe ele somado a 2 subtraído por 2*maxback_val[i]
        cut_val += 2 - 2*maxback_val[index];
        if (cut_val == 0) break;

        maxback_val.erase(maxItr);

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
    auto maxItr = max_element(maxback_val.begin(), maxback_val.end());
    int index = distance(maxback_val.begin(), maxItr);

    cut = cut_val;
    return vo[index];
}

void shrink(vector<vector<double>>& x_new, vector<int>& So, int shirinkado) {
    for (size_t j = 0; j < So.size(); j++) {
        if (j < So.back()) {
            if(shirinkado < So[j]) {
                x_new[j][So.back()] += x_new[shirinkado][So[j]];
                x_new[shirinkado][So[j]] = 0;
            } else {
                x_new[j][So.back()] += x_new[So[j]][shirinkado]; 
                x_new[So[j]][shirinkado] = 0;
            }
        } else {
            if(shirinkado < So[j]) {
                x_new[So.back()][j] += x_new[shirinkado][So[j]];
                x_new[shirinkado][So[j]] = 0;
            } else {
                x_new[So.back()][j] += x_new[So[j]][shirinkado]; 
                x_new[So[j]][shirinkado] = 0;
            }
        }
    }
}
