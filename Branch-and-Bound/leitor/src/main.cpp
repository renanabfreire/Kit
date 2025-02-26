#include "BB.h"       

using namespace std;

int main(int argc, char** argv) {
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
    cout << s.coust << ": ";
    for(int i=0; i<s.sequence.size()-1; i++){
        cout << s.sequence[i] << " -> ";
    }
    cout << s.sequence[s.sequence.size()-1] << endl;

    delete data; // Cleaning data
	return 0;
}
