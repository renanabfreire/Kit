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
    }

    // Solving node with Lagrangian Relaxation
    SolutionLambda x;
    no.lambda = subgradientMethod(x ,data.getDimension(), cost, 1, UB, 30, 0.00001, no.lambda);
    no.lower_bound = x.cost;
    no.edges = x.edges;

    // checking if it is feasible
    no.feasible = true;
    vector<int> cont(no.edges.size(), 0);
    for(const auto& edge : no.edges) {
        cont[edge.first]++;
        cont[edge.second]++;
    }
    for(int i=0; i< data.getDimension(); i++){
        if(cont[i] != 2) // if some node dont is subject the degree restriction the node isn't feasible
        no.feasible = false;
    }

    // chosing the forbidden node
    int chosen = distance(cont.begin(), max_element(cont.begin(), cont.end()));
    no.chosen = {chosen, cont[chosen]};

    for (int i = 0; i < data.getDimension(); i++){
        delete [] cost[i];
    }
    delete [] cost;
}