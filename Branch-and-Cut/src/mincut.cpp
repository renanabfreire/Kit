#include "separation.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <iomanip>
#include <limits>
#include <vector>

double maxback(vector<vector<double>>&, vector<int>&, vector<int>&, int);
void shrink(vector<vector<double>>&, vector<int>&, vector<int>&);

extern vector<vector<int>> MinCut(double **x, int n) {
     cout << "Entrando" << endl;
  double cut_val, min_cut;
  min_cut = numeric_limits<double>::max();
  vector<int> solution;
  vector<int> cut(n);
  vector<int> main_cut(n-1);
  vector<int> set;

  vector<vector<double>> x_cur(n, vector<double>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      x_cur[i][j] = x[i][j];
    }
  }
  x_cur.push_back(vector<double>(n, 0));
  for (size_t i = 0; i < x_cur.size(); i++) {
      x_cur[i].push_back(0);
  }

  solution = {0};
  iota(cut.begin(), cut.end(), 1);
  // cout << "não maxbackou" << endl;
  cut_val = maxback(x_cur, solution, cut, n+1);
  // cout << "Menti" << endl;
  min_cut = cut_val;
  main_cut = cut;
  set = solution;

  for (int i = 0; i < n-1; i++) {
      solution = {0};
      cut = vector<int>(n);
      iota(cut.begin(), cut.end(), 1);
      cut_val = maxback(x_cur, solution, cut, n+1);

      if (cut_val < min_cut) {
          min_cut = cut_val;
          set = solution;

          // main_cut.clear();
          cout << cut.size() << endl;
      }

      cout << "não shrinkei" << endl;
      shrink(x_cur, cut, solution);
      cout << "menti" << endl;
  }

  cout << "lascou" << endl;
  /* cout << main_cut.size() << " - " << set.size() << " - " << setprecision(18) << min_cut << endl;
  for (size_t i = 0; i < set.size(); i++) {
      cout << set[i] << " - ";
  }
  cout << endl; */
  
  if (min_cut >= 2){
      // cout << "aa" << endl;
     return {};      
  }
  return {main_cut};
}


double maxback(vector<vector<double>>& x, vector<int>& usados, vector<int>& vo, int n){
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
    while (vo.size() > 2) {
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

    return cut_val;
}

void shrink(vector<vector<double>>& x_new, vector<int>& st, vector<int>& So) {
    for (size_t i = 0; i < st.size(); i++) {
        for (size_t j = 0; j < So.size(); j++) {
            if(st[i] < So[j]) {
                x_new[j][x_new.size()-1] += x_new[st[i]][So[j]]; 
            } else {
                x_new[j][x_new.size()-1] += x_new[So[j]][st[i]]; 
            }
        }
    }

    x_new[st[1]] = vector<double>(x_new.size(), 0);
    x_new[st[0]] = vector<double>(x_new.size(), 0);

    for(size_t i = 0; i < x_new.size(); i++){
        x_new[i][st[1]] = 0;
        x_new[i][st[0]] = 0;
    }
}
