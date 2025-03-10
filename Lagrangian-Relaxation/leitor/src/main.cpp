#include "Kruskal.h"
#include "Data.h"

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    std::vector<std::vector<double>> vec;
    for(int i=1;i<=data.getDimension(); i++){
        std::vector<double> aux;
        for(int j=1; j<=data.getDimension(); j++){
            aux.push_back(data.getDistance(i, j));
            cout << data.getDistance(i, j) << "   ";
        }
        cout << "\n";
        vec.push_back(aux);
    }

    Kruskal teste = Kruskal(vec);
    cout << teste.MST(data.getDimension()) << endl;
    vii po = teste.getEdges();

    cout << teste.getEdges().size() << endl;
    
    for(int i = 0; i<po.size(); i++){
        cout << po[i].first << " - " << po[i].second << endl; 
    }

    return 0;
}