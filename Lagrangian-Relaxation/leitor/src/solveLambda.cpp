#include "LagrangianRelaxation.h"

void solveLambda(Data& data, SolutionLambda& solution, vector<double> lambda){
    std::vector<std::vector<double>> vec;
    for(int i=1;i<data.getDimension(); i++){
        std::vector<double> aux;
        for(int j=i+1; j<data.getDimension(); j++){
            aux.push_back(data.getDistance(i, j) - lambda[i] - lambda[j]);
        }
        vec.push_back(aux);
    }
    double bcost = 0;
    for(int i=0; i<lambda.size(); i++)
        bcost += 2*lambda[i];

    Kruskal teste = Kruskal(vec);
    solution.cost = teste.MST(data.getDimension());
    solution.cost += bcost;
    solution.edges = teste.getEdges();
    vector<int> xOj;
    xOj.push_back(99999);
    for(int i = 1; i <data.getDimension() - 1; i++){
        if(data.getDistance(data.getDimension(), i) < xOj.back()){
            xOj.push_back(i);
        }else if(data.getDistance(data.getDimension(), i) < xOj[xOj.size() - 2]){
            xOj.insert(xOj.end() - 1, i);
        }
    }
    solution.edges.push_back({data.getDimension()-1, xOj[xOj.size() - 2]});
    solution.edges.push_back({data.getDimension()-1, xOj.back()});
    solution.cost += data.getDistance(data.getDimension()-1, xOj[xOj.size() - 2]) - lambda[data.getDimension()-1] - lambda[xOj[xOj.size()-2]];
    solution.cost += data.getDistance(data.getDimension()-1, xOj.back()) - lambda[data.getDimension()-1] - lambda[xOj.back()];
}