#include "LagrangianRelaxation.h"
#include <time.h>
#include <chrono>

int main(int argc, char** argv){
    auto inicio = chrono::high_resolution_clock::now();
    auto data = Data(argc, argv[1]);
    data.read();
    
    // Creating solution
    Solution s;
    if(argv[2][0] == 'D') s = BB_DFS(data); // Depth First Search
    else if(argv[2][0] == 'B') s = BB_BFS(data); // Breadth First Search
    else{
        cout << "Digite operação válida" << endl; // No First Search
        return 1;
    }
    cout << "Custo total da solucao: " << s.cost << endl;
    auto resultado = chrono::high_resolution_clock::now() -inicio;
    float seconds = chrono::duration_cast<chrono::milliseconds>(resultado).count();

    cout << "Tempo de execução: " << float(seconds/1000) << endl;
    return 0;

    return 0;
}