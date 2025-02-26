#include "BB.h"       

using namespace std;

int main(int argc, char** argv) {
    auto inicio = chrono::high_resolution_clock::now();
    // Opening instance
    Data* data = new Data(argc, argv[1]);
    data->readData();
    
    // Creating solution
    Solution s;
    if(argv[2][0] == 'D') s = BB_DFS(data); // Depth First Search
    else if(argv[2][0] == 'B') s = BB_BFS(data); // Breadth First Search
    else{
        cout << "Digite operação válida" << endl; // No First Search
        return 1;
    }
    cout << "Custo total da solucao: " << s.coust << endl;
    auto resultado = chrono::high_resolution_clock::now() -inicio;
    float seconds = chrono::duration_cast<chrono::milliseconds>(resultado).count();

    cout << "Tempo de execução: " << float(seconds/1000) << endl;
    delete data; // Cleaning data
	return 0;
}
