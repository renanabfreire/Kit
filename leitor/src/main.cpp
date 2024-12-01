#include "Data.h"
#include "Ils.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

double calcularCusto(Data& data, vector<int>& v);

//Comando para executar o codigo: ./tsp instances/"nome_da_instancia".tsp
//ex: ./tsp instances/teste.tsp
int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    int maxIls;

    if(data.getDimension() >= 150)
        maxIls = data.getDimension()/2;
    else
        maxIls = data.getDimension();

    Solution s = ILS(50, maxIls, data);

    cout << "Custo total da solucao: " << s.value << endl;
    return 0;
}
