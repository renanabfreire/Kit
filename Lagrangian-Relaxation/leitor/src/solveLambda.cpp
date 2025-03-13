#include "LagrangianRelaxation.h"

void solveLambda(int dimension, double** costMatrix, SolutionLambda& solution, vector<double> lambda){
    std::vector<std::vector<double>> vec;
    for(int i=0;i<dimension-1; i++){
        std::vector<double> aux;
        for(int j=i+1; j<dimension; j++){
            aux.push_back(costMatrix[i][j] - lambda[i-1] - lambda[j-1]);
        }
        vec.push_back(aux);
    }
    double bcost = 0;
    for(int i=0; i<lambda.size(); i++)
        bcost += 2*lambda[i];

    Kruskal teste = Kruskal(vec);
    solution.cost = teste.MST(dimension);
    solution.cost += bcost;
    solution.edges = teste.getEdges();
    vector<int> xOj;
    xOj.push_back(999999);
    for(int i = 0; i < dimension-1; i++){
        if(costMatrix[dimension-1][i] < xOj.back()){
            xOj.push_back(i);
        }else if(costMatrix[dimension-1][i] < xOj[xOj.size() - 2]){
            xOj.insert(xOj.end() - 1, i);
        }
    }
    solution.edges.push_back({dimension-1, xOj[xOj.size() - 2]});
    solution.edges.push_back({dimension-1, xOj.back()});
    solution.cost += costMatrix[dimension-1][xOj[xOj.size() - 2]] - lambda[dimension-1] - lambda[xOj[xOj.size()-2]];
    solution.cost += costMatrix[dimension-1][xOj.back()] - lambda[dimension-1] - lambda[xOj.back()];
}