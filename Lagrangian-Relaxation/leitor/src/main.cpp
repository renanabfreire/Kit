#include "LagrangianRelaxation.h"

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();
    SolutionLambda x;

    subgradientMethod(x ,data.getDimension(), data.getMatrixCost(), 1, 26000, 30, 0.00001);
    
    cout << "\n" << x.cost << endl;
    for(int i=0; i<x.edges.size()-1; i++) cout << "(" << x.edges[i].first << ", " << x.edges[i].second << ") -> ";

    cout << "(" << x.edges.back().first << ", " << x.edges.back().second << ")" << endl;

    return 0;
}