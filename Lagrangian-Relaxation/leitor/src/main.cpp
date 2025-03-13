#include "LagrangianRelaxation.h"

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();
    SolutionLambda x;

    subgradientMethod(x ,data.getDimension(), data.getMatrixCost(), 1, 850, 30, 0.00001);
    
    cout << "\n" << x.cost << endl;
    for(int i=0; i<x.edges.size()-1; i++) cout << "(" << x.edges[i].first << ", " << x.edges[i].second << ") -> ";

    cout << "(" << x.edges.back().first << ", " << x.edges.back().second << ")" << endl;

    return 0;
}

int main2(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    std::vector<double> lambda(data.getDimension(), 0);
    std::vector<double> lambdaselect(data.getDimension(), 0);
    double epsilon=1;
    double UB = 26000;
    int k=0;
    SolutionLambda x, xselect;
    xselect.cost = 0;

    while(1)
    {
    //    solveLambda(data, x, lambda);
        cout << x.cost << endl;

        if(x.cost > xselect.cost){
            xselect = x;
            lambdaselect = lambda;
            k=0;
        }else{
            k++;
            epsilon /= 2;
            if(k >= 30)
                k=0;
        }
        for(int i=0; i<lambda.size(); i++){
            int cont = 0;
            for(const auto& edge : x.edges) {
                if(edge.first == i || edge.second == i)
                    cont++;
            }
            if(cont != 2)
                lambda[i] = lambdaselect[i] + epsilon * (UB - xselect.cost) / (2 - cont);
            else
                lambda[i] = lambdaselect[i];
        }

        if(x.cost > UB || epsilon < 0.00001){
            break;
        }
    }
    cout << "\n" << xselect.cost << endl;
    for(int i=0; i<xselect.edges.size()-1; i++) cout << "(" << xselect.edges[i].first << ", " << xselect.edges[i].second << ") -> ";

    cout << "(" << xselect.edges.back().first << ", " << xselect.edges.back().second << ")" << endl;

    return 0;
}

int main1(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    std::vector<std::vector<double>> vec;
    for(int i=1;i<=data.getDimension(); i++){
        std::vector<double> aux;
        for(int j=1; j<=data.getDimension(); j++){
            aux.push_back(data.getDistance(i, j));
        }
        vec.push_back(aux);
    }

    Kruskal teste = Kruskal(vec);
    cout << teste.MST(data.getDimension()) << endl;
    vii po = teste.getEdges();

    for(int i = 0; i<po.size(); i++){
        cout << po[i].first << " - " << po[i].second << endl; 
    }

    return 0;
}