#include "LagrangianRelaxation.h"

void solve_node(Data& data, Node& no, double UB){
    //taking cost matrix
    double** cost = new double*[data.getDimension()];
    for (int i=0; i< data.getDimension(); i++){
        cost[i] = new double[data.getDimension()];
        for(int j=0; j<data.getDimension(); j++){
            cost[i][j] = data.getDistance(i+1, j+1);
        }
    }
    for(int i=0; i<no.forbidden_arcs.size(); i++){
        cost[no.forbidden_arcs[i].first][no.forbidden_arcs[i].second] = 99999;
        cost[no.forbidden_arcs[i].second][no.forbidden_arcs[i].first] = 99999;
    }

    // Solving node with Lagrangian Relaxation
    SolutionLambda x;
    no.feasible = subgradientMethod(x ,data.getDimension(), cost, 1, UB, 30, 0.00001, no.lambda);
    no.lower_bound = x.cost;
    no.edges = x.edges;

    // checking if it is feasible
    /*no.feasible = true;
    vector<int> cont(data.getDimension(), 0);
    for(const auto& edge : no.edges) {
        cont[edge.first]++;
        cont[edge.second]++;
    }
    for(int i=0; i< data.getDimension(); i++){
        if(cont[i] != 2) // if some node dont is subject the degree restriction the node isn't feasible
            no.feasible = false;
    }*/

    // chosing the forbidden node
    vector<int> cont(data.getDimension(), 0);
    for(const auto& edge: no.edges){
        cont[edge.first]++;
        cont[edge.second]++;
    }

    no.chosen = 0;
    for(int i=0; i<cont.size(); i++){
        if(cont[i] > cont[no.chosen]) no.chosen = i;
    }

    for (int i = 0; i < data.getDimension(); i++){
        delete [] cost[i];
    }
    delete [] cost;
}