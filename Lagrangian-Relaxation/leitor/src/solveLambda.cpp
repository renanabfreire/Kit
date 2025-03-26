#include "LagrangianRelaxation.h"

void solveLambda(int dimension, double** costMatrix, SolutionLambda& solution, vector<double>& lambda){
    // take the distance vector to MST
    std::vector<std::vector<double>> vec;
    vec.push_back({99999});
    for(int i=1;i<dimension-1; i++){
        std::vector<double> aux;
        for(int j=0; j<i; j++){
            aux.push_back(costMatrix[i][j] - lambda[i] - lambda[j]); // Apply Lagrangian penalizers
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

    // Getting closest nodes
    vector<int> xOj;
    xOj.push_back(0);
    for(int i = 0; i < dimension-1; i++){
        if((costMatrix[dimension-1][i] - lambda[i]) <= (costMatrix[dimension-1][xOj.back()] - lambda[xOj.back()])){
            xOj.push_back(i);
        }else if((costMatrix[dimension-1][i] - lambda[i]) <= (costMatrix[dimension-1][xOj[xOj.size() - 2]] - lambda[xOj[xOj.size() - 2]])){
            xOj.insert(xOj.end() - 1, i);
        }
    }
    // Updating last edges
    solution.edges.push_back({dimension-1, xOj[xOj.size() - 2]});
    solution.edges.push_back({dimension-1, xOj.back()});
    solution.cost += costMatrix[dimension-1][xOj[xOj.size() - 2]] - lambda[xOj[xOj.size()-2]];
    solution.cost += costMatrix[dimension-1][xOj.back()] - lambda[xOj.back()];
}