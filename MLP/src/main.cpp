#include "Data.h"
#include "Ils.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

//Comando para executar o codigo: ./mlp instances/"nome_da_instancia".tsp
//ex: ./mlp instances/teste.tsp
int main(int argc, char** argv)
{
    auto inicio = chrono::high_resolution_clock::now();

    auto data = Data(argc, argv[1]);
    data.read();
    int maxIls;

    if(data.getDimension() > 100)
        maxIls = 100;
    else
        maxIls = data.getDimension();

    Solution s = ILS(10, maxIls, data);

    cout << "Custo total da solucao: " << s.value << endl;
    auto resultado = chrono::high_resolution_clock::now() -inicio;
    float seconds = chrono::duration_cast<chrono::milliseconds>(resultado).count();

    cout << "Tempo de execução: " << float(seconds/1000) << endl;
    return 0;
}
